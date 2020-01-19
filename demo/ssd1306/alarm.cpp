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

    //It outputs a sequence of chars defined in compile-time at the
    //position page=0 and column=0 of the display. One font with
    //resolution 8x8 is used. Note, it's more efficient to use a
    //compile-time instead of a run-time sequence when the length of
    //the sequence isn't too much long.(You can consider a length less
    //than eleven(11) chars as a reference)
    disp.out<font::_8x8>(0, 0, ATT85_SSD1306_STR("alarm"));
    
    //Power the display
    disp.on();
    
    while(true);
}
