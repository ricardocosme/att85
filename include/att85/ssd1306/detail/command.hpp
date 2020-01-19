
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
constexpr void command_start() {
    start_write_mode<Sda, Scl, Addr>();
    send_byte<Sda, Scl>(0x00);
}

template<typename Sda, typename Scl>
constexpr void send_command(uint8_t command) 
{ send_byte<Sda, Scl>(command); }

template<typename Display>
struct scoped_commands {
    using Sda = typename Display::Sda;
    using Scl = typename Display::Scl;
    scoped_commands() { command_start<Sda, Scl, Display::Addr>(); }
    ~scoped_commands() { stop_cond<Sda, Scl>(); }
};

}}}
