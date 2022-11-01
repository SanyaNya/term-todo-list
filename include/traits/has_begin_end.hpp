#pragma once

#include <utility>
#include <iterator>
#include <type_traits>

namespace todolist::traits
{

template<typename T, typename = void>
struct has_begin_end : std::false_type {};

template<typename T>
struct has_begin_end<
    T, std::void_t<
            decltype(std::begin(std::declval<T>())),
            decltype(std::end(std::declval<T>()))>> : 
    std::true_type {};

template<typename T>
constexpr bool has_begin_end_v = has_begin_end<T>::value;

} //namespace todolist::traits
