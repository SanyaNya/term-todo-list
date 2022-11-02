#pragma once

#include <type_traits>
#include <iterator>

namespace todolist::traits
{

namespace detail
{

template<typename T>
struct dumb_iterator
{
    using iterator_category = std::input_iterator_tag;
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using difference_type = int;

    bool operator!=(dumb_iterator) const noexcept
    {
        return true;
    }

    value_type operator*() const noexcept
    {
        return std::declval<value_type>();
    }

    pointer operator->()
    {
        return std::declval<pointer>();
    }

    dumb_iterator& operator++() noexcept
    {
        return *this; 
    }

    dumb_iterator& operator++(int) noexcept
    {
        return *this; 
    }
};

template<typename T, typename = void>
struct is_range_constructible_h : std::false_type {};

template<typename T>
struct is_range_constructible_h<
    T, std::void_t<
        typename T::value_type, 
        decltype(T
                {
                std::declval<detail::dumb_iterator<T>>(),
                std::declval<detail::dumb_iterator<T>>()
                })>> : 
            std::true_type {};

} //namespace detail

template<typename T>
struct is_range_constructible : detail::is_range_constructible_h<T> {};

template<typename T>
constexpr bool is_range_constructible_v = 
    is_range_constructible<T>::value;

} //namespace todolist::traits
