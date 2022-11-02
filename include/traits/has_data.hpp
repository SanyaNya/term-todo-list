#pragma once

#include <utility>
#include <type_traits>
#include <iterator>

namespace todolist::traits
{

namespace detail
{

template<typename T, typename = void>
struct has_data_h : std::false_type {};

template<typename T>
struct has_data_h<
    T, std::void_t<decltype(std::data(std::declval<T>()))>> : 
    std::true_type {};

} //namespace detail

template<typename T>
struct has_data : detail::has_data_h<T> {};

template<typename T>
constexpr bool has_data_v = has_data<T>::value;

} //namespace todolist::traits
