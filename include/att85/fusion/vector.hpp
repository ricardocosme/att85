
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/mpl/integral_constant.hpp>

namespace att85 { namespace fusion {

template<typename... T>
struct vector;

template<typename T>
struct vector<T> {
    using tail = void;
    using type = T;
    type obj;
};
    
template<typename T, typename... Tail>
struct vector<T, Tail...> : vector<Tail...> {
    using tail = vector<Tail...>;
    using type = T;
    type obj;
};

namespace detail {

template<unsigned char cnt, typename Seq, typename T>
struct idx;

template<unsigned char cnt, typename T>
struct idx<cnt, void, T> {
    using type = void;
};
    
template<unsigned char cnt, typename Seq, typename T>
struct idx {
    using type =
        conditional_t<
        is_same<typename Seq::type, T>::value,
        mpl::uint8_t_<cnt>,
        typename idx<cnt + 1, typename Seq::tail, T>::type>;
};

} //namespace detail

template<typename Seq, typename T>
using idx  = detail::idx<0, Seq, T>;

}}
