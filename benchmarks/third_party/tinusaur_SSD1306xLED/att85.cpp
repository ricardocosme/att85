#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/8x8/chars.hpp>

using namespace att85::ssd1306;

int main() {
    display_128x32<> disp;
    disp.out<font::_8x8>(0, 0, ATT85_SSD1306_STR("alarm"));
    disp.on();
    while(true);
}

//Compilation using avr-gcc 8.2.0 with -Os and 128x32 display:
//   text	   data	    bss	    dec	    hex	filename
//    336	      0	      0	    336	    150	a.out
