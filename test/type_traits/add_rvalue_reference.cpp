#include <att85/type_traits/add_rvalue_reference.hpp>
#include <att85/type_traits/is_same.hpp>

using namespace att85;

int main() {
    static_assert(is_same<add_rvalue_reference_t<int&>, int&>::value, "");
    static_assert(is_same<add_rvalue_reference_t<int&&>, int&&>::value, "");
    static_assert(is_same<add_rvalue_reference_t<int>, int&&>::value, "");
    static_assert(is_same<add_rvalue_reference_t<const int>, const int&&>::value, "");
    static_assert(is_same<add_rvalue_reference_t<volatile const int>, volatile const int&&>::value, "");
}
