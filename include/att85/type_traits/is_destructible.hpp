
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/type_traits/declval.hpp>
#include <att85/type_traits/integral_constant.hpp>

namespace att85 {

//until c++14
struct do_is_destructible {
    template<typename T, typename = decltype(declval<T&>().~T())>
    static true_type test(int);

    template<typename>
    static false_type test(...);
};

template<typename T>
struct is_destructible_impl : do_is_destructible {
    using type = decltype(test<T>(0));
};

template<typename T>
using is_destructible = typename is_destructible_impl<T>::type;

}
