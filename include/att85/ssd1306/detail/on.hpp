
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/ssd1306/commands/commands.hpp>
#include <att85/ssd1306/detail/command.hpp>

namespace att85 { namespace ssd1306 { namespace detail {

template<typename Display>
constexpr inline void on(bool v) {
    using Sda = typename Display::Sda;
    using Scl = typename Display::Scl;
    detail::send_command<Sda, Scl>(v ? commands::On::cmd : commands::Off::cmd);
}

}}}
