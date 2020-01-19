
// Copyright Ricardo Calheiros de Miranda Cosme 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <att85/utility.hpp>

namespace att85 { namespace timer {

//timer that executes a function OnExpire when expired
//
//This timer is based on a number of ticks that is decremented at each
//call to down(). A function OnExpire is executed when the number of
//ticks reach zero. This component is intended to be used with a clock
//that polls the timer through a call to down() at each clock time
//period.
//
//OnExpire: function to be executed when the timer expires. The
//signature must be: void()
//
template<typename OnExpire>
class deadline : public OnExpire {
public:    
    //TODO 16bits support
    using ticks_t = uint8_t;
    using on_expire_t = OnExpire;
private:    
    ticks_t _remaining{0};
    
    OnExpire& base()
    { return static_cast<OnExpire&>(*this); }
    
    const OnExpire& base() const
    { return static_cast<const OnExpire&>(*this); }

    struct do_nothing { void operator()() const{} };
public:
    deadline() = default;
    explicit deadline(ticks_t tcks, OnExpire f = OnExpire{})
        : OnExpire(move(f))
        , _remaining(tcks)
    {}

    //Returns if the timer is expired
    bool expired() const
    { return _remaining == 0; }
    
    //Returns the remaining number of ticks.
    ticks_t expires_at() const
    { return _remaining; }
    
    //Returns the FunctionObject to be executed when the timer expires.
    OnExpire& onexpire()
    { return base(); }
    
    //See above.
    const OnExpire& onexpire() const
    { return base(); }

    //Decrement the number of ticks and execute OnExpire if `expired == true`.
    //
    //OneShotOnExpire is an optional FunctionObject to be executed
    //when the timer expires and after the execution of OnExpire.
    //
    //Note: This function always decrement the number of ticks. The
    //caller is responsible to control if `down` shouldn't be called
    //when `expired() == true`.
    //
    //precondition: expired() == false
    template<typename OneShotOnExpire = do_nothing>
    void down(OneShotOnExpire&& f = OneShotOnExpire{}) {
        --_remaining;
        if(expired()) {
            onexpire()();
            f();
        }
    }
};

}}
