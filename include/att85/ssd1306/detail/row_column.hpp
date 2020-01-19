
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/ssd1306/detail/command.hpp>
#include <att85/ssd1306/detail/send_byte.hpp>

namespace att85 { namespace ssd1306 { namespace detail {

template<typename Sda, typename Scl>
constexpr inline void send_start_end(uint8_t start, uint8_t end) {
    send_byte<Sda, Scl>(start);
    send_byte<Sda, Scl>(end);
}

template<typename Sda, typename Scl>
constexpr inline void row(uint8_t start, uint8_t end) {
    send_command<Sda, Scl>(0x22);
    send_start_end<Sda, Scl>(start, end);
}

template<typename Sda, typename Scl>
constexpr inline void column(uint8_t start, uint8_t end) {
    send_command<Sda, Scl>(0x21);
    send_start_end<Sda, Scl>(start, end);
}

template<typename Display>
constexpr inline void row_column(uint8_t row_start, uint8_t row_end,
                                 uint8_t col_start, uint8_t col_end) {
    using Sda = typename Display::Sda;
    using Scl = typename Display::Scl;
    scoped_commands<Display> b;
    row<Sda, Scl>(row_start, row_end);
    column<Sda, Scl>(col_start, col_end);
}

}}}
