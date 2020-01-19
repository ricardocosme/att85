
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/ssd1306/detail/clk_pulse.hpp>

#include <att85/pin.hpp>

namespace att85 { namespace ssd1306 { namespace detail {

template<typename Sda, typename Scl>
constexpr inline void send_byte(uint8_t byte) {
    //TODO: Do arithmetic operations using bytes instead of words.
    for(int8_t i = 7; i >= 0; --i)	{
        (byte & (1 << i)) ? high<Sda>() : low<Sda>();
        detail::clk_pulse<Scl>();
    }
    //acknowledge bit
    detail::clk_pulse<Scl>();
}

}}}
