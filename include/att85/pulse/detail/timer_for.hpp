#pragma once

#include <att85/pulse/detail/out_pulse_on_expire.hpp>
#include <att85/utility.hpp>

namespace att85 { namespace pulse { namespace detail {

template<typename Timer, typename ClockTime>
struct timer_for {
    using result_type = Timer;
    using on_expire = out_pulse_on_expire<
        typename Timer::on_expire_t::high_pulse,
        typename Timer::on_expire_t::low_pulse>;

    //TODO 16bits support
    template<typename Pulse, typename OnExpire>
    result_type dispatch(Pulse, OnExpire onexpire)
    { return result_type{Pulse::duration::value / ClockTime::value, att85::move(onexpire)}; }
    
    template<typename Pulse, typename OnExpire = typename Timer::on_expire_t>
    result_type operator()(Pulse o, OnExpire onexpire = OnExpire{}) {
        static_assert
            (Pulse::duration::value >= ClockTime::value,
             "Pulse duration must be greater or equal than the clock time.");
        return dispatch(o, onexpire);
    }
};

}}}
