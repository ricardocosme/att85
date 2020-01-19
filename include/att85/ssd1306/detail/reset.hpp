
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/ssd1306/commands/commands.hpp>
#include <att85/ssd1306/detail/command.hpp>
#include <att85/ssd1306/policy.hpp>
#include <att85/type_traits.hpp>

#include <avr/pgmspace.h>

namespace att85 { namespace ssd1306 { namespace detail {

using namespace commands;

#define ATT85_SSD1306_FIXED_CMDS(Rows)  \
    0x20, 0x01, /*Vertical Addressing Mode*/ \
    0x22, 0x00, (Rows / 8) - 1, /*Set page address*/  \
    0xC8, /*COM Output Scan Direction*/ \
    0xDA, 0x02, /*COM Pins Hardware Configuration*/ \
    0xA1, /*Segment Re-map*/  \
    0xA8, Rows - 1, /*Multiplex ratio*/
        
#define ATT85_SSD1306_CHARGE_PUMP_CMD \
    0x8D, 0x14, /*Enable Charge Pump*/
    
#define ATT85_SSD1306_DISPLAY_CLOCK_CMD(Clock) \
    0xD5, Clock::ratio_freq, /*Display clock frequency and divide ratio*/

template<uint8_t... bytes>
struct setup { constexpr static uint8_t cmds[] [[gnu::__progmem__]] = {bytes...}; };

template<typename Display, typename DisplayClock, uint8_t... bytes>
inline auto handle_cmds(ChargePump, enable_if_t<!is_same<DisplayClock, DefDisplayClock>::value, DisplayClock>) {
    return setup<
        ATT85_SSD1306_FIXED_CMDS(Display::rows)
        ATT85_SSD1306_CHARGE_PUMP_CMD
        ATT85_SSD1306_DISPLAY_CLOCK_CMD(DisplayClock)
        bytes...>{};
}

template<typename Display, typename DisplayClock, uint8_t... bytes>
inline auto handle_cmds(DisableChargePump, enable_if_t<!is_same<DisplayClock, DefDisplayClock>::value, DisplayClock>) {
    return setup<
        ATT85_SSD1306_FIXED_CMDS(Display::rows)
        ATT85_SSD1306_DISPLAY_CLOCK_CMD(DisplayClock)
        bytes...>{};
}

template<typename Display, typename DisplayClock, uint8_t... bytes>
inline auto handle_cmds(ChargePump, enable_if_t<is_same<DisplayClock, DefDisplayClock>::value, DisplayClock>) {
    return setup<
        ATT85_SSD1306_FIXED_CMDS(Display::rows)
        ATT85_SSD1306_CHARGE_PUMP_CMD
        bytes...>{};
}

template<typename Display, typename DisplayClock, uint8_t... bytes>
inline auto handle_cmds(DisableChargePump, enable_if_t<is_same<DisplayClock, DefDisplayClock>::value, DisplayClock>) {
    return setup<
        ATT85_SSD1306_FIXED_CMDS(Display::rows)
        bytes...>{};
}

template<typename Display, uint8_t... bytes>
inline auto make_setup() {
    return handle_cmds<Display, typename Display::DisplayClockPolicy, bytes...>(
        typename Display::ChargePumpPolicy{},
        typename Display::DisplayClockPolicy{});
}

template<typename Display, uint8_t... Cmds>
inline void reset() {
    using Sda = typename Display::Sda;
    using Scl = typename Display::Scl;
    //Note:
    //0x20 0x00,
    //0x22, 0x00, (Rows / 8) - 1,
    //There isn't an option to configure the memory addressing
    //mode because the implementation assumes a vertical mode. Take
    //a look at display::out(), for example.
    //
    //0xC8 0xDA 0x02
    //There isn't an option to configure the COM Outuput Scan
    //Direction and COM Pins Hardware Configuration because the
    //implementation assumes a sequential COM pin configuration, a
    //scan from COM63 to COM0 and a disabled COM Left/Right remap.
    auto o = make_setup<Display, Cmds...>();
    scoped_commands<Display> b;
    for(uint8_t i{0}; i < sizeof(o.cmds); ++i)
        send_command<Sda, Scl>(pgm_read_byte(&o.cmds[i]));
}

}}}
