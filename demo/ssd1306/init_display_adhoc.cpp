#include <att85/ssd1306/display.hpp>

using namespace att85;
using namespace att85::ssd1306;

static const uint8_t seq[] PROGMEM = {
    0x20, 0b00,	0xC8,	0xA1,	0xA8, 0x1F,	0xD5, 0xF0,	0xDA, 0x02,	0x8D, 0x14
};

int main() {
    DDRB |= (1 << sda::num);
    DDRB |= (1 << scl::num);
    high<scl>();
    high<sda>();
    //command start
    low<sda>();
    low<scl>();
    detail::send_byte<sda, scl>(0x78);
    detail::send_byte<sda, scl>(0x00);
    for (uint8_t i = 0; i < sizeof(seq); ++i)
        detail::send_command<sda, scl>(pgm_read_byte(&seq[i]));
    //stop condition
    low<sda>();
    high<scl>();
    high<sda>();
    //data start
    low<sda>();
    low<scl>();
    detail::send_byte<sda, scl>(0x78);
    detail::send_byte<sda, scl>(0x40);
    for(auto i{0}; i < 128 * 4; ++i)
        detail::send_byte<sda, scl>(0x00);
    //stop condition
    low<sda>();
    high<scl>();
    high<sda>();
}
