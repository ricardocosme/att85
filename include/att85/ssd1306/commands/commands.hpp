
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

namespace att85 { namespace ssd1306 { namespace commands {

struct ChargePump {};

struct Inverse{ constexpr static uint8_t cmd{0xA7}; };
constexpr inline Inverse inverse;

struct On{ constexpr static uint8_t cmd{0xAF}; };
constexpr inline On on;

struct Off{ constexpr static uint8_t cmd{0xAE}; };
constexpr inline Off off;

struct Contrast{ constexpr static uint8_t cmd{0x81}; };
constexpr inline Contrast contrast;

template<uint8_t v>
struct of{ constexpr static uint8_t cmd{v}; };

}}}
