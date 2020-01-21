#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/8x8/chars.hpp>

using namespace att85;
using namespace att85::ssd1306;

constexpr static uint8_t cmds[] [[gnu::__progmem__]] = {
    0x20, 0x01, /*Vertical Addressing Mode*/ \
    0x22, 0x00, 3, /*Set page address*/  \
    0xC8, /*COM Output Scan Direction*/ \
    0xDA, 0x02, /*COM Pins Hardware Configuration*/ \
    0xA1, /*Segment Re-map*/  \
    0xA8, 31, /*Multiplex ratio*/
    0x8D, 0x14, /*Enable Charge Pump*/
};

using Display = display_128x32<>;

int main() {
    using Sda = Display::Sda;
    using Scl = Display::Scl;

    //We're doing here what the default constructor of display is
    //doing when we don't pass any command or change any policy of the
    //class template display. This adhoc solution can verify if the
    //constructor's implementation is adding any possible overhead to
    //the code that is generated. We want to guarantee that the
    //decisions taken in compile-time aren't decreasing the
    //performance in space.
    DDRB |= (1 << Sda::num);
    DDRB |= (1 << Scl::num);
    {
        detail::scoped_commands<Display> b;
        for(uint8_t i{0}; i < sizeof(cmds); ++i)
            detail::send_command<Sda, Scl>(pgm_read_byte(&cmds[i]));
    }
    detail::clear<Display>();
}
