#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/8x8/chars.hpp>

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

    using alpha = runtime::c_str<font::_8x8::alpha>;
    
    disp.out<font::_8x8>(0, 0, alpha{"abcdefghijklmno"});
    disp.out<font::_8x8>(2, 0, alpha{"pqrstuvwxyz"});

    //Power the display
    disp.on();
    
    while(true);
}
