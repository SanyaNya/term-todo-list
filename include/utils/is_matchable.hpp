#pragma once

#include <type_traits>
#include <utility>
#include <optional>
#include <string_view>

namespace todolist::utils
{

template<typename T, typename RawToken, typename = void>
struct is_matchable : std::false_type {};

template<typename T, typename RawToken>
struct is_matchable<
    T, RawToken, 
    std::void_t<decltype(
        T::match(std::declval<RawToken>()))>> : 
    std::bool_constant<
        std::is_same_v<
            std::invoke_result_t<decltype(T::match), RawToken>, 
            std::optional<T>>> {};

template<typename T, typename RawToken>
constexpr bool is_matchable_v = is_matchable<T, RawToken>::value;

} //namespace todolist::utils
