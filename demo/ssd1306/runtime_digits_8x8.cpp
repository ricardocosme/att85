#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/8x8/chars.hpp>

using namespace att85;
using namespace att85::ssd1306;
using namespace att85::ssd1306::commands;

int main() {
    display_128x32<> disp{inverse, contrast, of<1>{}};
    // Display disp;
    // disp.out<font::_8x8>(static_cast<uint8_t>(89));
    disp.out<font::_8x8>(2, 50, static_cast<uint8_t>(23));
    // disp.out<font::_8x8>(static_cast<uint8_t>(145), 3, 100);
    disp.on();
    // disp.commands([](auto&& disp) {
    //     disp.contrast(1);
    //     disp.on();
    // });
    while(true);
}
