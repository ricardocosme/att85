
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <stdint.h>

namespace att85 { namespace mpl {

template<uint8_t base, uint8_t n>
struct pow {
    static const uint8_t value = base * pow<base, n - 1>::value;
};

template<uint8_t base>
struct pow<base, 0> {
    static const uint8_t value = 1;
};

}}
