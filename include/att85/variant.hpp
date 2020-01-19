#pragma once

#include <att85/mpl/all.hpp>
#include <att85/mpl/integral_constant.hpp>
#include <att85/mpl/max_element.hpp>
#include <att85/mpl/vector.hpp>
#include <att85/utility.hpp>
#include <att85/type_traits.hpp>
#include <att85/new.hpp>

namespace att85 {

template<typename, typename>
struct visitor_impl;
    
template<typename V, typename Seq>
struct apply_to_type {
    struct base {
        template<typename F>
        static typename F::result_type invoke(V& v, unsigned char idx, F&& f) {
            using type = typename Seq::type;
            // return f(type{});
            return f(reinterpret_cast<type&>(v.storage));
        }
    };

    struct recursive {
        template<typename F>
        static typename F::result_type invoke(V& v, unsigned char idx, F f) {
            if(idx == 0) {
                using type = typename Seq::type;
                // return f(type{});
                return f(reinterpret_cast<type&>(v.storage));
            }
            return apply_to_type<V, typename Seq::tail>::invoke
                (v, idx - 1, move(f));
        }
    };
    template<typename F>
    static typename F::result_type invoke(V& v, unsigned char idx, F f) {
        using Invoke = conditional_t<
            is_same<void, typename Seq::tail>::value,
            base,
            recursive>;
        return Invoke::invoke(v, idx, move(f));
    }
};

template<typename Variant, typename Visitor>
struct visitor_impl {
    using result_type = typename Visitor::result_type;
    template<typename T>
    typename Visitor::result_type operator()(T& o) const
    { return visitor(reinterpret_cast<T&>(v.storage)); }
    Variant& v;
    Visitor visitor;
};

template<typename Variant, typename Visitor>
inline typename Visitor::result_type visit(Variant& v, Visitor visitor)
{
    return apply_to_type<Variant, typename Variant::types>::invoke
        (v, v.which(), 
         visitor_impl<Variant, Visitor>{v, move(visitor)});
}

struct dtor_visitor {
    using result_type = void;
    template<typename T>
    result_type operator()(T& o) const
    { o.~T(); }
};

template<typename B, typename... T>
class variant_impl;
    
template<typename... T>
class variant_impl<false_type, T...> {
public:    
    using types = mpl::vector<T...>;
private:    
    unsigned char _which;
    alignas(T...) unsigned char storage[sizeof(mpl::max_element_t<types>)];

    template<typename, typename>
    friend struct visitor_impl;
    
    template<typename, typename>
    friend struct apply_to_type;
public:
    variant_impl() { new (&storage) typename types::type(); }

    ~variant_impl()
    { visit(*this, dtor_visitor{}); }
    
    unsigned char which() const
    { return _which; }
    
    template<typename U>
    void operator=(U o) {
        new (&storage) U(move(o));
        _which = mpl::idx<types, U>::type::value;
    }
};

template<typename... T>
class variant_impl<true_type, T...> {
public:    
    using types = mpl::vector<T...>;
private:    
    unsigned char _which;
    alignas(T...) unsigned char storage[sizeof(mpl::max_element_t<types>)];

    template<typename, typename>
    friend struct visitor_impl;

    template<typename, typename>
    friend struct apply_to_type;
public:
    variant_impl() = default;

    unsigned char which() const
    { return _which; }
    
    template<typename U>
    void operator=(U o) {
        new (&storage) U(move(o));
        _which = mpl::idx<types, U>::type::value;
    }
};

template<typename T>
struct wrap_is_trivially_destructible {
    using type = is_trivially_destructible<T>;
};

template<typename... T>
struct variant
    : variant_impl<
      typename mpl::all<mpl::vector<T...>, wrap_is_trivially_destructible>::type,
      T...>
{
    using base = variant_impl<
        typename mpl::all<mpl::vector<T...>, wrap_is_trivially_destructible>::type, T...>;
    using base::base;
    using base::operator=;
};

}
