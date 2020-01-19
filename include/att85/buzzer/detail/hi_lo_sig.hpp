
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "att85/pin.hpp"

namespace att85 { namespace buzzer { namespace detail {

template<typename Pin>
struct HiSig {
    void operator()()
    { hi<Pin>(); }
};

template<typename Pin>
struct LoSig {
    void operator()()
    { lo<Pin>(); }
};

}}}
