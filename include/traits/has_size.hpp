#pragma once

#include <utility>
#include <type_traits>
#include <iterator>

namespace todolist::traits
{

namespace detail
{

template<typename T, typename = void>
struct has_size_h : std::false_type {};

template<typename T>
struct has_size_h<
    T, std::void_t<decltype(std::size(std::declval<T>()))>> : 
    std::true_type {};

} //namespace detail

template<typename T>
struct has_size : detail::has_size_h<T> {};

template<typename T>
constexpr bool has_size_v = has_size<T>::value;

} //namespace todolist::traits
