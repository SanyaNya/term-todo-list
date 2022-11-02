#pragma once

#include <type_traits>
#include <utility>

namespace todolist::traits
{

namespace detail
{

using std::get;
using std::tuple_size;
using std::tuple_element;

template<typename T, typename = void>
struct is_tuple_like_h : std::false_type {}; 

template<typename T>
struct is_tuple_like_h<
    T, 
    std::void_t<
        decltype(get<0>(std::declval<T&>())),
        tuple_size<T>,
        tuple_element<0, T>>> : std::true_type {};

} //namespace detail

template<typename T>
struct is_tuple_like : detail::is_tuple_like_h<T> {};

template<typename T>
constexpr bool is_tuple_like_v = is_tuple_like<T>::value;

} //namespace todolist::traits
