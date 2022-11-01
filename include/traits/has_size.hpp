#pragma once

#include <utility>
#include <type_traits>
#include <iterator>

namespace todolist::traits
{

template<typename T, typename = void>
struct has_size : std::false_type {};

template<typename T>
struct has_size<
    T, std::void_t<decltype(std::size(std::declval<T>()))>> : 
    std::true_type {};

template<typename T>
constexpr bool has_size_v = has_size<T>::value;

} //namespace todolist::traits
