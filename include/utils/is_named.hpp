#pragma once

#include <type_traits>

namespace todolist::utils
{

template<typename T, typename = void>
struct is_named : std::false_type {};

template<typename T>
struct is_named<T, std::void_t<decltype(T::name)>> : std::true_type {};

template<typename T>
constexpr bool is_named_v = is_named<T>::value;

} //namespace todolist::utils
