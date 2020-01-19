#include <att85/type_traits/is_void.hpp>

using namespace att85;

int main() {
    static_assert(is_void<void>::value, "");
    static_assert(is_void<const void>::value, "");
    static_assert(is_void<volatile void>::value, "");
    static_assert(is_void<const volatile void>::value, "");
    static_assert(!is_void<int>::value, "");
}
