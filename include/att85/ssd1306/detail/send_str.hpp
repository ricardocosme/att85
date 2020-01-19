
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "att85/ssd1306/c_str.hpp"
#include "att85/ssd1306/send_char.hpp"
#include "att85/utility.hpp"

namespace att85 { namespace ssd1306 { namespace detail {

template<typename Display, typename Font, char c>
constexpr inline void send(compiletime::c_str<c>)
{ att85::ssd1306::send_char<Display, Font, c>::send(); }

template<typename Display, typename Font, char c, char... cs>
constexpr inline void send(compiletime::c_str<c, cs...>) {
    send<Display, Font>(compiletime::c_str<c>{});
    send<Display, Font>(compiletime::c_str<cs...>{});
}

template<typename Str, uint8_t... indices>
auto build_string(att85::index_sequence<indices...>) {
    return compiletime::c_str<Str().chars[indices]...>();
}

}}}

#define ATT85_SSD1306_STR(str)                                      \
    []{                                                             \
        struct Str { const char * chars = str; };                   \
        return att85::ssd1306::detail::build_string<Str>(           \
            att85::make_index_sequence<sizeof(str)>::type());       \
    }()
