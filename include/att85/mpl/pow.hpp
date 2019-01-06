
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

namespace att85 { namespace mpl {

template<uint8_t n>
struct pow {
    static const uint8_t value = 2 * pow<n - 1>::value;
};

template<>
struct pow<0> {
    static const uint8_t value = 1;
};

}}
