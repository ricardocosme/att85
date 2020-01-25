#pragma once

#include <att85/pin.hpp>
#include <att85/type_traits/is_same.hpp>

namespace att85 { namespace ssd1306 { namespace detail {

template<typename Sda, typename Scl>
constexpr inline bool USI()
{ return is_same<Sda, sda>::value && is_same<Scl, scl>::value; }

}}}
