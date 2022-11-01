#pragma once

#include <type_traits>
#include <iostream>
#include <utility>

namespace todolist::traits
{

template<typename T, typename = void>
struct is_serializable : std::false_type {};

template<typename T>
struct is_serializable<
        T, 
        std::void_t<decltype(
            std::declval<const T&>().serialize(
                std::declval<std::ostream&>()))>> : std::true_type {};

template<typename T>
constexpr bool is_serializable_v = is_serializable<T>::value;

} //namespace todolist::traits
