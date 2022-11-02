#pragma once

#include <type_traits>
#include <utility>
#include <optional>
#include <string_view>

namespace todolist::traits
{

namespace detail
{

template<typename T, typename RawToken, typename = void>
struct is_matchable_h : std::false_type {};

template<typename T, typename RawToken>
struct is_matchable_h<
    T, RawToken, 
    std::void_t<decltype(
        noexcept(T::match(std::declval<RawToken>())))>> : 
    std::bool_constant<
        std::is_same_v<
            std::invoke_result_t<decltype(T::match), RawToken>, 
            std::optional<T>>> {};

} //namespace detail

template<typename T, typename RawToken>
struct is_matchable : detail::is_matchable_h<T, RawToken> {};

template<typename T, typename RawToken>
constexpr bool is_matchable_v = is_matchable<T, RawToken>::value;

} //namespace todolist::traits
