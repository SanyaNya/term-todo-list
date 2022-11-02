#pragma once

#include <type_traits>
#include <iostream>
#include <utility>

namespace todolist::traits
{

namespace detail
{

template<typename T, typename = void>
struct is_deserializable_h : std::false_type {};

template<typename T>
struct is_deserializable_h<
    T, 
    std::void_t<
        decltype(
            T::deserialize(std::declval<std::istream&>()))>> : 
    std::bool_constant<
        std::is_same_v<
            std::invoke_result_t<decltype(T::deserialize), std::istream&>,
            T>> {};

} //namespace detail

template<typename T>
struct is_deserializable : detail::is_deserializable_h<T> {};

template<typename T>
constexpr bool is_deserializable_v = is_deserializable<T>::value;

} //namespace todolist::traits
