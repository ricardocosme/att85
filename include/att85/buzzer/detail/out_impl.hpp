
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/buzzer/signals.hpp>
#include <att85/mpl/pow.hpp>
#include <att85/type_traits.hpp>

namespace att85 { namespace detail {

template<uint8_t idx, uint8_t outs, typename... Sigs>
struct out_impl;

template<uint8_t idx, bool B>
struct out_of;

template<uint8_t idx>
struct out_of<idx, true> {
    static const uint8_t value = mpl::pow<idx>::value;
};

template<uint8_t idx>
struct out_of<idx, false> {
    static const uint8_t value = 0;
};

template<typename T, uint8_t N>
struct is_beep;
template<uint8_t N>
struct is_beep<beep<N>, N> : true_type {};
template<uint8_t N>
struct is_beep<pause<N>, N> : false_type {};

template<uint8_t idx, uint8_t outs, typename Sig>
struct out_impl<idx, outs, Sig> {
    out_impl(uint8_t& val, uint8_t* times)
    {
        times[idx] = Sig::duration;
        val = outs + out_of<idx, is_beep<Sig, Sig::duration>::value>::value;
    }
};
    
template<uint8_t idx, uint8_t outs, typename Sig, typename... Sigs>
struct out_impl<idx, outs, Sig, Sigs...>
    : out_impl<idx + 1,
               outs + out_of<idx, is_beep<Sig, Sig::duration>::value>::value,
               Sigs...> {
    using base = out_impl
        <idx + 1,
         outs + out_of<idx, is_beep<Sig, Sig::duration>::value>::value,
         Sigs...>;
    out_impl(uint8_t& val, uint8_t* times) : base(val, times)
    { times[idx] = Sig::duration; }
};

}}
