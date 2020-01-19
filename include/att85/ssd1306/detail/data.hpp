
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/ssd1306/detail/send_byte.hpp>
#include <att85/ssd1306/detail/start_stop_condition.hpp>
#include <att85/ssd1306/detail/start_write_mode.hpp>

namespace att85 { namespace ssd1306 { namespace detail {

template<typename Sda, typename Scl, char Addr>
constexpr inline void data_start() {
    start_write_mode<Sda, Scl, Addr>();
    send_byte<Sda, Scl>(0x40);
}

}}}
