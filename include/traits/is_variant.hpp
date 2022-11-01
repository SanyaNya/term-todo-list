#pragma once

#include <variant>

namespace todolist::traits
{

template<typename T>
struct is_variant : std::false_type {};

template<typename ... Args>
struct is_variant<std::variant<Args...>> : std::true_type {};

template<typename T>
constexpr bool is_variant_v = is_variant<T>::value;

} //namespace todolist::traits
