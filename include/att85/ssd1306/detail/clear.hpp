
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/ssd1306/detail/data.hpp>
#include <att85/ssd1306/detail/row_column.hpp>
#include <att85/ssd1306/detail/send_byte.hpp>
#include <att85/ssd1306/detail/start_stop_condition.hpp>

namespace att85 { namespace ssd1306 { namespace detail {

template<typename Display>
constexpr inline void clear() {
    using Sda = typename Display::Sda;
    using Scl = typename Display::Scl;
    data_start<Sda, Scl, Display::Addr>();
    for(uint16_t i{0}; i < 128 * Display::pages; ++i)
        send_byte<Sda, Scl>(0x00);
    stop_cond<Sda, Scl>();
}

}}}
