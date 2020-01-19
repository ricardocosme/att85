
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/ssd1306/detail/send_char.hpp>
#include <att85/type_traits/enable_if.hpp>
#include <att85/type_traits/is_same.hpp>

namespace att85 { namespace ssd1306 { namespace detail {

template<typename Display, typename Font, typename UInt>
constexpr inline enable_if_t<
    is_same<UInt, uint8_t>::value
    || is_same<UInt, uint16_t>::value
    || is_same<UInt, uint32_t>::value
    || is_same<UInt, uint64_t>::value>
out(UInt n)  {
    using Sda = typename Display::Sda;
    using Scl = typename Display::Scl;
    if(n < 10)
        send_char<Sda, Scl, Font>(
            Font::digits::seq + (Font::height * Font::width/8 * n));
    else {
        out<Display, Font>(static_cast<UInt>(n / 10));
        out<Display, Font>(static_cast<UInt>(n % 10));
    }
}

}}}
