#pragma once

#include <att85/chrono/duration.hpp>

#include <initializer_list>
#include <float.h>
#include <limits.h>
#include <stdint.h>

namespace att85 { namespace clock {

namespace att85 {
template<typename T>
constexpr T abs(const T x) noexcept
{ return(x == T(0) ? T(0) : x < T(0) ? - x : x ); }
}

struct hdw_timer_params {
    int clk_divisor;
    uint8_t timer_cmp;
};

template<uint8_t v>
constexpr float to_seconds(chrono::literals::ms<v> from)
{ return chrono::literals::ms<v>::value * 1E-3; }

constexpr hdw_timer_params timer_params
(unsigned long long hdw_clk, float soft_clk_period) {
    auto il = {1., 2., 4., 8., 16., 32., 64., 128., 256., 512., 1024., 2048., 4096., 8192., 16384.};
    auto min_diff = FLT_MAX;
    int ret{255};
    float clk_divisor{1.};
    for(auto d : il) {
        auto base_freq = hdw_clk / d;
        auto timer_cmp = soft_clk_period * base_freq;
        if(timer_cmp < 1) continue;
        
        int whole = timer_cmp + 0.5;
        if(whole > 255) continue; 
       
        auto hard_clk_tm = whole * 1/base_freq;
        auto diff = att85::abs(hard_clk_tm - soft_clk_period);
        if((min_diff - diff) > 1E-10) { /* diff < min_dif */
            min_diff = diff;
            ret = whole;
            clk_divisor = d;
        } else if((min_diff - diff) < -1E-10) continue; /* diff > min_dif */
        else if(ret > whole) { /* diff == min_dif */
            min_diff = diff;
            ret = whole;
            clk_divisor = d;
        }

    }
    return {static_cast<int>(clk_divisor), static_cast<uint8_t>(ret)};
    // return {static_cast<int>(1024), static_cast<uint8_t>(10)};
}

}}
