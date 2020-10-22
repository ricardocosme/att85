
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/pin.hpp>
#include <att85/ssd1306/detail/clk_pulse.hpp>
#include <att85/ssd1306/detail/USI.hpp>

#include <avr/io.h>

namespace att85 { namespace ssd1306 { namespace detail {

inline void clk_pulse() {
    constexpr uint8_t cr = (0 << USISIE)
        | (0 << USIOIE)
        | (1 << USIWM1)
        | (0 << USIWM0)
        | (1 << USICS1)
        | (0 << USICS0)
        | (1 << USICLK)
        | (1 << USITC);
    USICR = cr; // Generate positve SCL edge.
    USICR = cr; // Generate negative SCL edge.
}

template<typename Sda, typename Scl>
constexpr inline void send_byte(uint8_t byte) {
    //We use USI(Universal Serial Interface) hardware if possible to
    //optimize the communication with the display. The generated code
    //is faster and smaller than the version which is only using a
    //software solution.(see below)
    if constexpr(USI<Sda, Scl>()) { 
       high<Sda>();
       USIDR = byte;
       USISR = (1 << USISIF)
           | (1 << USIOIF)
           | (1 << USIPF)
           | (0x0 << USICNT0);
       do { clk_pulse(); }
       while(!(USISR & (1 << USIOIF))); // Check for transfer complete.

       USIDR = 0xFF; // Release SDA.
       clk_pulse();
    } else { //When USI isn't available
        for(uint8_t i = 8; i > 0; --i) {
            low<Sda>();
            if(byte & 0x80) high<Sda>();
            byte <<= 1;
            detail::clk_pulse<Scl>();
        }
        //acknowledge bit
        detail::clk_pulse<Scl>();
    }
}

}}}
