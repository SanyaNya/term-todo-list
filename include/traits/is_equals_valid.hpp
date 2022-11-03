#pragma once

#include <type_traits>
#include <utility>

namespace todolist::traits
{

namespace detail
{

template<typename T1, typename T2, typename = void>
struct is_equals_valid_h : std::false_type {};

template<typename T1, typename T2>
struct is_equals_valid_h<
    T1, T2, 
    std::void_t<decltype(
        std::declval<const T1&>() == std::declval<const T2&>())>> : 
    std::true_type {};

} //namespace detail

template<typename T1, typename T2>
struct is_equals_valid : detail::is_less_valid_h<T1, T2> {};

template<typename T1, typename T2>
constexpr bool is_equals_valid_v = is_less_valid<T1, T2>::value;

} //namespace todolist::traits
