#pragma once

#include <utility>
#include <iterator>
#include <type_traits>

namespace todolist::traits
{

namespace detail
{

template<typename T, template<typename> typename ... Ps>
struct eval_predicates : 
    std::conjunction<Ps<typename T::value_type>...>{};

template<typename, typename T, template<typename> typename ... Ps>
struct has_value_type_h : std::false_type {};

template<typename T, template<typename> typename ... Ps>
struct has_value_type_h<
    std::void_t<typename T::value_type>, T, Ps...> : 
    eval_predicates<T, Ps...> {};

} //namespace detail

template<typename T, template<typename> typename ... Ps>
constexpr bool has_value_type_v = 
    detail::has_value_type_h<void, T, Ps...>::value;

} //namespace todolist::traits
