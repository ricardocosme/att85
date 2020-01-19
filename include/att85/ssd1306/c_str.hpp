
// Copyright Ricardo Calheiros de Miranda Cosme 2020.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include "att85/utility.hpp"
#include "att85/ssd1306/send_char.hpp"

namespace att85 { namespace ssd1306 {

namespace compiletime {

template<char... Chars>
struct c_str;

template<char c>
struct c_str<c> {
    constexpr static char fst_char = c;
    using rest = void;
};

template<char c, char... Chars>
struct c_str<c, Chars...> : c_str<Chars...> {
    constexpr static char fst_char = c;
    using rest = c_str<Chars...>;
};

}//namespace compiletime

namespace runtime {
template<typename Charset>
struct c_str {
    using charset = Charset;
    const char* str;
};
}//namespace runtime

}}
