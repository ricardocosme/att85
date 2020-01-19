#include <att85/type_traits/is_destructible.hpp>

using namespace att85;

struct destructible {};
struct not_destructible { ~not_destructible() = delete; };

int main() {
    static_assert(!is_destructible<void>::value, "");
    static_assert(is_destructible_impl<destructible>::type::value, "");
    
    //until c++14
    static_assert(!is_destructible_impl<destructible&>::type::value, "");
    
    static_assert(!is_destructible<not_destructible>::value, "");
}
