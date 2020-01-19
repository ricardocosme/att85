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

inline void bottom(uint8_t row, uint8_t col) {
    detail::stop_cond<sda, scl>();                                     
    detail::command_start<sda, scl, 0x78>();                                 
    detail::send_byte<sda, scl>(0x22);                                 
    detail::send_byte<sda, scl>(row);                              
    detail::send_byte<sda, scl>(3);                                    
    detail::send_byte<sda, scl>(0x21);                                 
    detail::send_byte<sda, scl>(col);                                  
    detail::send_byte<sda, scl>(col + 7);                                  
    detail::stop_cond<sda, scl>();                                     
    detail::data_start<sda, scl, 0x78>();                                     
}

template<uint8_t N, const uint8_t seq[N]>
struct send_ {
static void exec(uint8_t row, uint8_t col) {
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 0));
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 1));
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 2));
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 3));
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 4));
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 5));
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 6));
    detail::send_byte<sda, scl>(detail::toGDDRAM(seq, 0, 7));
 }
};

int main() {
    Display disp;
    before_send(0, 0);
    send_<16, font::_8x8::_0>::exec(0, 0);
    bottom(0, 8);
    send_<16, font::_8x8::_1>::exec(0, 8);
    detail::stop_cond<sda, scl>();                         
    disp.on();
    while(true);
}
