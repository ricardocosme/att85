#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/8x8/chars.hpp>

using namespace att85::ssd1306;
using namespace att85::ssd1306::commands;

int main() {
    // display_128x32<scl, sda, 0x78, NoClearOnInit> disp{on};
    display_128x32<> disp;
    // disp.out<font::_8x8>(0, 0, ATT85_SSD1306_STR("01234567"), (uint8_t)10, "0123");
    disp.out<font::_8x8>(0, 0, ATT85_SSD1306_STR("0123456890"));
    // disp.out<font::_8x8>(0, 0, runtime::c_str<font::_8x8::digits>{"01234567890"});
    // disp.out<font::_8x8>(0, 0, "08");
    // disp.on();
    disp.contrast(34);
    disp.on();
    // disp.commands([](auto&& disp) {
    //   disp.contrast(1);
    //   disp.on();
    // });
    while(true);
}
