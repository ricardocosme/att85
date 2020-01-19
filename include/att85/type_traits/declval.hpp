
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/type_traits/add_rvalue_reference.hpp>

namespace att85 {

template <typename T>
add_rvalue_reference_t<T> declval() noexcept;

}
