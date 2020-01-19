#include <att85/type_traits/is_trivially_destructible.hpp>

using namespace att85;

struct trivial {};
struct not_trivial {
    void* p;
    ~not_trivial(){ p = nullptr; }
};

int main() {
    static_assert(is_trivially_destructible<trivial>::value, "");
    static_assert(!is_trivially_destructible<not_trivial>::value, "");
}
