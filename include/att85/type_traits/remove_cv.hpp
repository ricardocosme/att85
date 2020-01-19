
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

namespace att85 {

template<typename T>
struct remove_const
{ using type = T; };

template<typename T>
struct remove_const<const T>
{ using type = T; };

template<typename T>
using remove_const_t = typename remove_const<T>::type;

template<typename T>
struct remove_volatile
{ using type = T; };

template<typename T>
struct remove_volatile<volatile T>
{ using type = T; };

template<typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

template<typename T>
struct remove_cv {
    using type = remove_volatile_t<remove_const_t<T>>;
};

template<typename T>
using remove_cv_t = typename remove_cv<T>::type;

}
