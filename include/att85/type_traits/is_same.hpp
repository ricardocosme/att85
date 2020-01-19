
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/type_traits/integral_constant.hpp>

namespace att85 {

template<typename, typename>
struct is_same : false_type {};

template<typename T>
struct is_same<T, T> : true_type {};

}
