#pragma once

#include <type_traits>
#include <utility>
#include <optional>
#include <string_view>

namespace todolist::traits
{

namespace detail
{

template<typename T, typename It, typename = void>
struct is_parsable_h : std::false_type {};

template<typename T, typename It>
struct is_parsable_h<
    T, It, 
    std::void_t<decltype(
        noexcept(T::parse(std::declval<It&>(), std::declval<It>())))>> : 
    std::bool_constant<
        std::is_same_v<
            std::invoke_result_t<decltype(T::template parse<It>), It&, It>, 
            std::optional<T>>> {};

} //namespace detail

template<typename T, typename It>
struct is_parsable : detail::is_parsable_h<T, It> {};

template<typename T, typename It>
constexpr bool is_parsable_v = is_parsable<T, It>::value;

} //namespace todolist::traits
