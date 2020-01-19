#pragma once

#include <att85/type_traits.hpp>

namespace att85 { namespace mpl {

template<typename Seq, template <typename> class Pred>
struct all {
    using type = conditional_t<
        Pred<typename Seq::type>::type::value
        && all<typename Seq::tail, Pred>::type::value,
        true_type,
        false_type>;
};

template<template <typename> class Pred>
struct all<void, Pred> { using type = true_type; };

}}
