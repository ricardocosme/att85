#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/8x8/chars.hpp>

using namespace att85;
using namespace att85::ssd1306;

int main() {
    display_128x32<> disp;
    disp.out<font::_8x8>(0, 0, ATT85_SSD1306_STR("0"));
    disp.on();
    while(true);
}
