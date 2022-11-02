#pragma once

#include <type_traits>
#include <utility>

namespace todolist::traits
{

template<typename T>
struct is_pair : std::false_type {};

template<typename T1, typename T2>
struct is_pair<std::pair<T1, T2>> : std::true_type {};

template<typename T>
constexpr bool is_pair_v = is_pair<T>::value;

} //namespace todolist::tratis
