
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/ssd1306/detail/send_char.hpp>

namespace att85 { namespace ssd1306 { namespace detail {

template<typename Display, typename Font, typename Charset>
constexpr void out(const runtime::c_str<Charset>& o) {
    using Sda = typename Display::Sda;
    using Scl = typename Display::Scl;
    constexpr uint8_t char_size{Font::height * Font::width/8};
    for(uint8_t i{0}; o.str[i] != '\0'; ++i)
        send_char<Sda, Scl, Font>(
            Charset::seq
            + (char_size * (o.str[i] - Charset::fst_idx)));
}

}}}
