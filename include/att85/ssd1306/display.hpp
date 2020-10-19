
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/pin.hpp>
#include <att85/ssd1306/c_str.hpp>
#include <att85/ssd1306/detail/USI.hpp>
#include <att85/ssd1306/detail/clear.hpp>
#include <att85/ssd1306/detail/command.hpp>
#include <att85/ssd1306/detail/data.hpp>
#include <att85/ssd1306/detail/for_each_printable.hpp>
#include <att85/ssd1306/detail/inverse.hpp>
#include <att85/ssd1306/detail/on.hpp>
#include <att85/ssd1306/detail/reset.hpp>
#include <att85/ssd1306/detail/row_column.hpp>
#include <att85/ssd1306/detail/send_byte.hpp>
#include <att85/ssd1306/policy.hpp>

#include <avr/io.h>

namespace att85 { namespace ssd1306 {

//Take a look at display::commands() to understand the purpose of this
//abstraction.
template<typename Display>
struct scoped_display {
    Display& disp;
    using Sda = typename Display::Sda;
    using Scl = typename Display::Scl;
    using ChargePumpPolicy = typename Display::ChargePumpPolicy;
    using DisplayClockPolicy = typename Display::DisplayClockPolicy;
    constexpr static uint8_t Addr = Display::Addr;
    constexpr static uint8_t columns = Display::columns;
    constexpr static uint8_t rows = Display::rows;
    constexpr static uint8_t pages = Display::pages;
    
    constexpr void on(bool v = true) const
    { detail::on<Display>(v); }

    constexpr void inverse() const
    { detail::inverse<Display>(); }

    constexpr void contrast(uint8_t v) const {
        detail::send_byte<Sda, Scl>(commands::Contrast::cmd);
        detail::send_command<Sda, Scl>(v);
    }
};

//This abstraction represents a SSD1306 display that uses an i2c
//communication interface
//
//Columns: Number of columns of the display. For examplo, for a
//display with a 128x64 resolution, the Columns is equal to 128. The
//default value is 128.
//
//Rows: Number of rows of the display. For examplo, for a display with
//a 128x64 resolution, the Rows is equal to 64. This number should be
//divisible by eight and the default value is 64.
//
//Scl: The pin that represents the i2c clock signal SCL. The default
//is the pin att85::scl which is the pin pb2 in Attiny85. If possible,
//it's better to use the SCL pin provided by the microcontroller
//because the USI(Universal Serial Interface) hardware can be used to
//optimize the program.
//
//Sda: The pin that represents the line SDA which is the i2d data
//signal. The default is the pin att85::sda which is the pin pb0 in
//Attiny85. If possible, it's better to use the SDA pin provided by
//the microcontroller because the USI(Universal Serial Interface)
//hardware can be used to optimize the program.
//
//Addr: slave address of the display. The value should be 0x78 or
//0F0. The default is 0x78.
//
//COM_Pins_Hardware: COM pins hardware configuration. The default is
//0x12, which means that the layout of "Alternative COM pin
//configuration" is used without a COM left/right remap.
//
//ClearOnInitPolicy: ClearOnInit or NoClearOnInit
//  Policy to choose if the display will be clear on the
//  initialization. Take a look at policy.hpp.
//
//ChargePumpPolicy: commands::ChargePump or DisableChargePump
//  Policy to enable the Charge Pump Regulator to supply a voltage to
//  the display from a low voltage supply input. The default is the
//  regulator enabled but it can be disabled through the policy
//  DisableChargePump
//
//DisplayClock: DefDisplayClock or a custom struct
//
//  Policy to set the oscillator frequency and the display clock
//  divide ratio. The default is represented by the tag
//  DefDisplayClock which uses the divide ratio equal to 1 and the
//  frequency equal to 1000b, that is the defaut value of
//  SSD1306. Take a look at the datasheet for more information.
//
//  The ratio and frequency can be customized by a struct with a
//  constexpr and static data member 'uint8_t ratio_freq' to represent
//  the sequence of bits A[7:0]. The high sequence A7 A6 A5 A4
//  represents the frequency and the low sequence A3 A2 A1 A0
//  represents the divide ratio. Take a look at the datasheet for more
//  information about this. For example, we can determine the lowest
//  frequency throught the following struct:
//
//  struct lowest_clock {
//      //ratio=1111b and freq=0000b
//      constexpr static uint8_t ratio_freq{0x0F}; 
//  };
//
//  Take a look at the demo lowest_freq_display.cpp
//
template<uint8_t Columns = 128,
         uint8_t Rows = 64,
         typename Scl_ = scl,
         typename Sda_ = sda,
         uint8_t Addr_ = 0b1111000 /*0x78*/,
         uint8_t COM_Pins_Hardware_ = 0x12,
         typename ClearOnInitPolicy = ClearOnInit,
         typename ChargePumpPolicy_ = commands::ChargePump,
         typename DisplayClock_ = DefDisplayClock>
class display {
public:    
    using Scl = Scl_;
    using Sda = Sda_;
    using ChargePumpPolicy = ChargePumpPolicy_;
    using DisplayClockPolicy = DisplayClock_;
    constexpr static uint8_t Addr = Addr_;
    constexpr static uint8_t COM_Pins_Hardware = COM_Pins_Hardware_;
    constexpr static uint8_t columns = Columns;
    constexpr static uint8_t rows = Rows;
    constexpr static uint8_t pages = Rows / 8;
public:    
    static_assert(Rows % 8 == 0,
        "Rows must be divisible by eight.");

    //The constructor(ctor) setup the ports that are related to Scl
    //and Sda, it also sends a set of required commands, it clears the
    //screen (optional) and it sends a sequence of optional commands
    //like inverse the screen, change the constrast or power on the
    //display.
    //
    //It is possible to pass commands here to achieve a small code
    //size when the programmer needs to setup the display in the
    //initialization phase. Take a look at commands.hpp to know what
    //commands are available. For example, imagine that we would like
    //a display with a inverse look and the possible lowest
    //contrast. We can instantiate our display with the following
    //line:
    //
    //display<....> disp{inverse, contrast, of<1>{}};
    //
    //Look, you can dispatch those commands after the construction of
    //the display, the question here is about performance because
    //dispatching the commands in the ctor avoids the code that is
    //required to send commands. Inside the execution of the ctor, the
    //commands can be dispatched reusing the context that is used to
    //send a set of required commands that are sent internally by the
    //implementation.
    template<typename... Cmds>
    constexpr display(Cmds...) {
        DDRB = DDRB | (1 << Sda::num);
        DDRB = DDRB | (1 << Scl::num);
        if constexpr(detail::USI<Sda, Scl>())
            USICR = (0<<USISIE)
                | (0<<USIOIE)
                | (1<<USIWM1)
                | (0<<USIWM0)
                | (1<<USICS1)
                | (0<<USICS0)
                | (1<<USICLK)
                | (0<<USITC);
        detail::reset<display, Cmds::cmd...>();
        if constexpr(is_same<ClearOnInitPolicy, ClearOnInit>::value)
            detail::clear<display>();
    }

    //Outputs a sequence of Printables to the display
    //
    //This method outputs a sequence of Printables from the left to
    //the right beggining in the position defined by a page and a
    //column. The 'page' is a value between [0, display::pages - 1]
    //and the 'column' is a value between [0, display::columns -
    //1]. One page is equal to 8 rows. The page zero '0' is located at
    //the top of the screen and the column '0' is the first column
    //from the left to the right. For example, with we desire to print
    //in top left of the display, we should use page=0 and column=0. 
    //
    //One Font should be defined. Take a look at `att85/font`.
    //
    //A Printable can be an unsigned integer, a compile time sequence
    //of chars or a runtime sequence of chars. If possible, it's a
    //better choice to use compile time sequence of chars to have a
    //better performance in space and time when the sequence isn't too
    //long.(How much too long? A sequence with a length less than 11
    //chars. Take your measures between the compile time and run time
    //approaches.)
    //
    //Example of printing the integer 89 using the font 8x8 at
    //position defined by page=3(the last row of the display) and
    //column=0:
    //
    //  disp.out<font::_8x8>(3, 0, static_cast<uint8_t>(89));
    //
    //Example of printing the string "alarm" using the font 8x8 at the
    //position defined by page=0 and column=50:
    //
    //  disp.out<font::_8x8>(0, 50, ATT85_SSD1306_STR("alarm"));
    //
    //Example of printing a const char* that can only have values
    //between the range of chars ['0', '9']. We must define a charset
    //to be used when printing a sequence in run time because if we
    //load an entire charset like the ASCII table we can easily waste
    //space in memory with chars that aren't never be used one single
    //time.
    //
    //  disp.out<font::_8x8>(0, 0,
    //      runtime::c_str<font::_8x8::digits>{digits});
    //
    template<typename Font, typename... Printables>
    constexpr void out(uint8_t page, uint8_t column, Printables... ps) const {
        detail::row_column<display>(page, page + Font::height/8 - 1,
                                    column, static_cast<uint8_t>(columns - 1));
        detail::data_start<Sda, Scl, Addr>();
        detail::for_each_printable<display, Font>(ps...);
        detail::stop_cond<Sda, Scl>();
    }

    //Clear the entire display with a blank char
    constexpr void clear() const {
        detail::row_column<display>(0, pages - 1,
                                    0, static_cast<uint8_t>(columns - 1));
        detail::clear<display>();
    }

    //Power on or off the display
    constexpr void on(bool v = true) const {
        detail::scoped_commands<display> b;
        detail::on<display>(v);
    }

    //Invert the bits that represents an image
    //
    //The bit 1 is replaced by bit 0 and vice versa.
    constexpr void inverse() const {
        detail::scoped_commands<display> b;
        detail::inverse<display>();
    }

    //Define the contrast
    //
    //The value must be between [1, 255]
    constexpr void contrast(uint8_t v) const {
        detail::scoped_commands<display> b;
        detail::send_byte<Sda, Scl>(commands::Contrast::cmd);
        detail::send_byte<Sda, Scl>(v);
    }

    //Execute a sequence of commands using one single context
    //
    //We can use this methods when we have to send more than one
    //command at a single time. This approach can save space and time
    //using one single context to send a sequence of commands. When we
    //call each command by itself we are starting a new context for
    //each command. For example, instead of define the contrast and
    //power on the display through the below sequence:
    //
    //  disp.contrast(34);
    //  disp.on();
    //
    //Those commands can be sent in a more efficient way:
    //
    //  disp.commands([](auto&& disp) {
    //    disp.contrast(34);
    //    disp.on();
    //  });
    //
    //Take your measures using -Os
    //
    //The function `f`should accept one single parameter to get a
    //reference to the display and it should not return anything. The
    //display inside the function is a `scoped_display`. Take a look
    //above at this class template to see the interface.
    //
    template<typename Commands>
    constexpr void commands(Commands f) {
        detail::scoped_commands<display> b;
        f(scoped_display<display>{*this});
    }
};

//This is an alias to a display with a 128x32 resolution
template<typename Scl = scl,
         typename Sda = sda,
         char Addr = 0b1111000 /*0x78*/,
         typename ClearOnInitPolicy = ClearOnInit,
         typename ChargePumpPolicy = commands::ChargePump,
         typename DisplayClock = DefDisplayClock>
using display_128x32 = display<
    128,
    32,
    Scl,
    Sda,
    Addr,
    0x02,
    ClearOnInitPolicy,
    ChargePumpPolicy,
    DisplayClock>;

//This is an alias to a display with a 128x64 resolution
template<typename Scl = scl,
         typename Sda = sda,
         char Addr = 0b1111000 /*0x78*/,
         typename ClearOnInitPolicy = ClearOnInit,
         typename ChargePumpPolicy = commands::ChargePump,
         typename DisplayClock = DefDisplayClock>
using display_128x64 = display<
    128,
    64,
    Scl,
    Sda,
    Addr,
    0x12,
    ClearOnInitPolicy,
    ChargePumpPolicy,
    DisplayClock>;

}}

