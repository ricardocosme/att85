#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/8x8/chars.hpp>

using namespace att85;
using namespace att85::ssd1306;

using Display = display_128x32<>;

inline void before_send(uint8_t row, uint8_t col) {
    {
        detail::scoped_commands<Display> b;
        detail::send_command<sda, scl>(0x22);
        detail::send_byte<sda, scl>(row);
        detail::send_byte<sda, scl>(3);
        detail::send_command<sda, scl>(0x21);
        detail::send_byte<sda, scl>(col);
        detail::send_byte<sda, scl>(7);
    }
    detail::data_start<sda, scl, 0x78>();
}

template<uint8_t N, const uint8_t seq[N]>
void send_0(uint8_t row, uint8_t col) {
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 0));
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 1));
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 2));
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 3));
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 4));
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 5));
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 6));
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 7));
}

int main() {
    Display disp;
    before_send(0, 0);
    send_0<16, font::_8x8::_0>(0, 0);
    detail::stop_cond<sda, scl>();                         
    disp.on();
    while(true);
}
