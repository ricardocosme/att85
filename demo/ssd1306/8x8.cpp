#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/8x8/chars.hpp>

using namespace att85;
using namespace att85::ssd1306;

int main() {
    display_128x32<> disp;
    disp.out<font::_8x8>(0, 0, ATT85_SSD1306_STR("alarm"));
    disp.out<font::_8x8>(1, 0, ATT85_SSD1306_STR("0123456789"));
    disp.out<font::_8x8>(2, 0, ATT85_SSD1306_STR(">< Done"));
    // disp.out<font::_8x8>(ATT85_SSD1306_STR("alarm"), 1, 0);
    disp.contrast(1);
    disp.on();
    while(true);
}
