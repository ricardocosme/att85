#include <att85/type_traits/is_same.hpp>
#include <att85/type_traits/remove_cv.hpp>

using namespace att85;

int main() {
    static_assert(is_same<remove_const_t<int>, int>::value, "");
    static_assert(is_same<remove_const_t<const int>, int>::value, "");
    static_assert(is_same<remove_const_t<const int*>, const int*>::value, "");
    static_assert(is_same<remove_const_t<const int* const>, const int*>::value, "");

    static_assert(is_same<remove_volatile_t<int>, int>::value, "");
    static_assert(is_same<remove_volatile_t<volatile int>, int>::value, "");
    static_assert(is_same<remove_volatile_t<volatile int*>, volatile int*>::value, "");
    static_assert(is_same<remove_volatile_t<volatile int* volatile>, volatile int*>::value, "");
    
    static_assert(is_same<remove_cv_t<int>, int>::value, "");
    static_assert(is_same<remove_cv_t<volatile int>, int>::value, "");
    static_assert(is_same<remove_cv_t<const int>, int>::value, "");
    static_assert(is_same<remove_cv_t<const volatile int>, int>::value, "");
    static_assert(is_same<remove_cv_t<const volatile int*>, const volatile int*>::value, "");
    static_assert(is_same<remove_cv_t<const volatile int* volatile>, const volatile int*>::value, "");
    static_assert(is_same<remove_cv_t<const volatile int* const volatile>, const volatile int*>::value, "");
}
