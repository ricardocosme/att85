
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/buzzer/detail/out_impl.hpp>

namespace att85 {

template<typename HiSig, typename LoSig, uint8_t Capacity = 3>
struct buzzer {
    static const uint8_t capacity = Capacity;
    
    uint8_t times[capacity];
    uint8_t val;
    uint8_t idx;
    uint8_t size;

    void poll() {
        if(idx < size) {
            auto& time = times[idx];
            if(time != 0) {
                if (val & (1 << idx)) HiSig{}();
                else LoSig{}();
            }
            if(--time == 0) {
                ++idx;
                PORTB &= ~(1 << PB3);
            }
        }
    }
    
    template<typename... Sigs>
    void out() {
        detail::out_impl<0, 0, Sigs...>{val, times};
        size = sizeof...(Sigs);
        idx = 0;
    }
};

}
