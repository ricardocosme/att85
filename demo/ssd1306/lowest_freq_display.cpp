#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/8x8/chars.hpp>

using namespace att85;
using namespace att85::ssd1306;
using namespace att85::ssd1306::commands;

struct lowest_clock {
    constexpr static uint8_t ratio_freq{0x0F};
};

using Display = display_128x32<scl,
                               sda,
                               0x78,
                               ClearOnInit,
                               ChargePump,
                               lowest_clock>;

int main() {
    Display disp{contrast, of<1>{}, inverse};
    disp.out<font::_8x8>(0, 0, ATT85_SSD1306_STR("12345"));
    disp.on();
    while(true);
}
