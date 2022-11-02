#pragma once

#include <type_traits>

namespace todolist::traits
{

namespace detail
{

template<typename T, typename = void>
struct is_named_h : std::false_type {};

template<typename T>
struct is_named_h<T, std::void_t<decltype(T::name)>> : std::true_type {};

} //namespace detail

template<typename T>
struct is_named : detail::is_named_h<T> {};

template<typename T>
constexpr bool is_named_v = is_named<T>::value;

} //namespace todolist::traits
