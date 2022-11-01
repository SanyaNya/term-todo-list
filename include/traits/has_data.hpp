#pragma once

#include <utility>
#include <type_traits>
#include <iterator>

namespace todolist::traits
{

template<typename T, typename = void>
struct has_data : std::false_type {};

template<typename T>
struct has_data<
    T, std::void_t<decltype(std::data(std::declval<T>()))>> : 
    std::true_type {};

template<typename T>
constexpr bool has_data_v = has_data<T>::value;

} //namespace todolist::traits
