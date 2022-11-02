#pragma once

#include <type_traits>
#include <utility>

namespace todolist::traits
{

namespace detail
{

template<typename T, typename = void>
struct is_resizable_h : std::false_type {};

template<typename T>
struct is_resizable_h<
    T,
    std::void_t<decltype(
        std::declval<T&>().resize(std::declval<std::size_t>()))>> : 
    std::true_type {};

} //namespace detail

template<typename T>
struct is_resizable : detail::is_resizable_h<T> {};

template<typename T>
constexpr bool is_resizable_v = is_resizable<T>::value;

} //namespace todolist::traits
