#pragma once

#include <type_traits>
#include <utility>
#include <optional>
#include <string_view>

namespace todolist::utils
{

template<typename T, typename It, typename = void>
struct is_parsable : std::false_type {};

template<typename T, typename It>
struct is_parsable<
    T, It, 
    std::void_t<decltype(
        noexcept(T::parse(std::declval<It&>(), std::declval<It>())))>> : 
    std::bool_constant<
        std::is_same_v<
            std::invoke_result_t<decltype(T::template parse<It>), It&, It>, 
            std::optional<T>>> {};

template<typename T, typename It>
constexpr bool is_parsable_v = is_parsable<T, It>::value;

} //namespace todolist::utils
