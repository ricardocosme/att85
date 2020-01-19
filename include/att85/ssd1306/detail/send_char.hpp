
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/ssd1306/detail/send_byte.hpp>

#include <avr/pgmspace.h>

namespace att85 { namespace ssd1306 { namespace detail {

template<typename Sda,
         typename Scl,
         typename Font,
         typename Seq>
inline void send_char(const Seq seq) {              
    for(uint8_t i{0}; i < Font::height/8 * Font::width; ++i)
        send_byte<Sda, Scl>(pgm_read_byte(&seq[i]));
}

}}}
