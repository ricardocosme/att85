#pragma once

#include <att85/type_traits.hpp>

namespace att85 { namespace mpl {

template<typename Seq>
class max_element;

template<typename Seq>
using max_element_t = typename max_element<Seq>::type;

template<typename Seq>
class max_element {
    using head = typename Seq::type;
    using tail = max_element_t<typename Seq::tail>;
public:    
    using type = conditional_t<
        sizeof(head) >= sizeof(tail),
        head,
        tail>;
};

template<>
struct max_element<void> { using type = char; };

}}
