#include <float.h>
#include <iomanip>
#include <iostream>
#include <stdint.h>
#include <utility>

namespace att85 {
template<typename T>
constexpr T abs(const T x) noexcept
{ return(x == T(0) ? T(0) : x < T(0) ? - x : x ); }
}

struct hdw_timer_params {
    int clk_divisor, timer_cmp;
};

constexpr hdw_timer_params f
(unsigned long long hdw_clk, float soft_clk_period) {
    auto il = {1., 2., 4., 8., 16., 32., 64., 128., 256., 512., 1024., 2048., 4096., 8192., 16384.};
    auto min_diff = FLT_MAX;
    int ret{INT_MAX};
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
    return {static_cast<int>(clk_divisor), ret};
}

int main() {
    static_assert(f(1E6, 1E-2).timer_cmp == 39,"");
    auto res = f(1E6, 0.011);
    std::cout << "win whole=" << res.timer_cmp << " " 
              << "win divisor=" << res.clk_divisor << std::endl;
}
