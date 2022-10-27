#pragma once

#include <type_traits>
#include <utility>
#include <optional>
#include <string_view>

namespace todolist::utils
{

template<typename T, typename = void>
struct is_matchable : std::false_type {};

template<typename T>
struct is_matchable<
    T, std::void_t<decltype(
        T::match(std::declval<const char*&>()))>> : 
    std::bool_constant<
        std::is_same_v<
            std::invoke_result_t<decltype(T::match), const char*&>, 
            std::optional<T>>> {};

template<typename T>
constexpr bool is_matchable_v = is_matchable<T>::value;

} //namespace todolist::utils
