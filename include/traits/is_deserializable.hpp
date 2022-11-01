#pragma once

#include <type_traits>
#include <iostream>
#include <utility>

namespace todolist::traits
{

template<typename T, typename = void>
struct is_deserializable : std::false_type {};

template<typename T>
struct is_deserializable<
    T, 
    std::void_t<
        decltype(
            T::deserialize(std::declval<std::istream&>()))>> : 
    std::bool_constant<
        std::is_same_v<
            std::invoke_result_t<decltype(T::deserialize), std::istream&>,
            T>> {};

template<typename T>
constexpr bool is_deserializable_v = is_deserializable<T>::value;

} //namespace todolist::traits
