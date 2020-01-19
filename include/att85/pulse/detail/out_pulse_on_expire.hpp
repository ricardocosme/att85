
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

namespace att85 { namespace pulse { namespace detail {

template<typename HighPulse, typename LowPulse>
struct out_pulse_on_expire {
    using high_pulse = HighPulse;
    using low_pulse = LowPulse;
    
    void operator()() const {
        if(high) HighPulse{}();
        else LowPulse{}();
    }
    //hint the compiler to use the bss section for a global or static
    //instance of an uninitialized object that has an `out_pulse_on_expire`.
    bool high{false}; 
};

}}}
