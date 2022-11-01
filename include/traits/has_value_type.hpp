#pragma once

#include <utility>
#include <iterator>
#include <type_traits>

namespace todolist::traits
{

template<typename T, typename = void>
struct has_value_type : std::false_type {};

template<typename T>
struct has_value_type<
    T, std::void_t<typename T::value_type>> : 
    std::true_type {};

template<typename T>
constexpr bool has_value_type_v = has_value_type<T>::value;

} //namespace todolist::traits
