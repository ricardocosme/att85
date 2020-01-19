#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/16x32/chars.hpp>

using namespace att85::ssd1306;

int main() {
    //Represents a SSD1306 display with resolution of 128x32 connected
    //to a ATtiny85 through the pins SDA(PB0) and SCL(PB2). This
    //display has an I2C address of the value 0x78, the screen is
    //cleared on the initialization(which means the ctor execution)
    //and the Charge Pump Regulator is used. Take a look at the class
    //template `display` to know how to customize these properties to
    //use your SSD1306 device.
    display_128x32<> disp;
    
    uint8_t n{93};
    //It outputs the number `n` at the position page=0 and column=0 of
    //the display. One font with resolution 16x32 is used.
    disp.out<font::_16x32>(0, 0, n);

    //Power the display
    disp.on();
    
    while(true);
}
