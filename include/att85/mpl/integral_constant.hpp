
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/type_traits.hpp>

namespace att85 { namespace mpl {

template<unsigned char v>
using uint8_t_ = integral_constant<unsigned char, v>;
    
}}
