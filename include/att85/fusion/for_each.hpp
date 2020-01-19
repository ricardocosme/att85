
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/type_traits/integral_constant.hpp>
#include <att85/type_traits/is_same.hpp>

namespace att85 { namespace fusion {

namespace detail {

template<typename Elem, typename F>
inline void for_each(Elem& e, F& f, true_type)
{ f(e.obj); }

template<typename Elem, typename F>
inline void for_each(Elem& e, F& f, false_type) {
    f(e.obj);
    for_each(static_cast<typename Elem::tail&>(e), f,
             is_same<typename Elem::tail, void>{});
}

} //namespace detail

template<typename Seq, typename F>
inline void for_each(Seq& seq, F&& f)
{ detail::for_each(seq, f, is_same<typename Seq::tail, void>{}); }

}}
