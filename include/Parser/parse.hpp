#pragma once

#include <cstddef>
#include <utility>
#include <type_traits>
#include <iostream>
#include <tuple>
#include <optional>
#include "utils/dfs_get.hpp"
#include "utils/dfs_holds_alternative.hpp"
#include "traits/traits.hpp"
#include "errors/errors.hpp"

namespace todolist::Parser
{

template<typename Arg, typename It>
inline std::optional<Arg> parse_arg(It& begin, It end) noexcept
{
    using V = std::decay_t<decltype(*begin)>;

    if constexpr(utils::typelist_dfs_contains_v<V, Arg>) 
    {
        auto t = *begin;

        if(utils::dfs_holds_alternative<Arg>(t))
        {
            ++begin;
            return utils::dfs_get<Arg>(t);
        }

        return std::nullopt;
    }

    if constexpr(traits::is_parsable_v<Arg, It>)
        return Arg::template parse(begin, end);
}

template<typename Arg>
struct Optional;

namespace detail
{

template<typename Arg>
struct parse_arg_exc
{
    template<typename It>
    static void f(Arg& arg, It& begin, It end)
    {
        if(begin == end) 
            throw unexpected_end_of_tokens();

        if(auto opt = parse_arg<Arg>(begin, end)) 
            arg = opt.value();
        else
            throw unexpected_token<Arg>();
    }
};

template<typename T>
struct parse_arg_exc<Optional<T>>
{
    template<typename It>
    static void f(Optional<T>& arg, It& begin, It end)
    {
        if(begin == end) 
            arg = Optional<T>{ std::nullopt };
        else
            arg = parse_arg<Optional<T>>(begin, end).value();
    }
};

template<typename Args, typename It, std::size_t ... Is>
inline Args parse_args(It& begin, It end, std::index_sequence<Is...>)
{
    Args args;
    ((parse_arg_exc<std::tuple_element_t<Is, Args>>::f(std::get<Is>(args), begin, end)), ...);

    return args;
}

} //namespace detail

template<typename Command, typename It>
inline Command parse(It& begin, It end)
{
    using Tuple = decltype(std::declval<Command>().args);

    Command cmd = 
        Command{
            detail::parse_args<Tuple>(
                begin, end, 
                std::make_index_sequence<std::tuple_size_v<Tuple>>{})};

    if(begin != end)
        throw unexpected_tokens_after_command();

    return cmd;
}

} //namespace todolist::Parser
