#pragma once

#include <cstddef>
#include <utility>
#include <type_traits>
#include <iostream>
#include <tuple>
#include <optional>
#include "utils/dfs_get.hpp"
#include "utils/dfs_holds_alternative.hpp"
#include "utils/is_named.hpp"
#include "utils/is_parsable.hpp"
#include "Error/unexpected_end_of_tokens.hpp"
#include "Error/unexpected_token.hpp"
#include "Error/cmd_not_found.hpp"

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

    if constexpr(utils::is_parsable_v<Arg, It>)
        return Arg::template parse(begin, end);
}

namespace detail
{

template<typename Arg, typename It>
inline Arg parse_arg_exc(It& begin, It end)
{
    if(begin == end) throw unexpected_end_of_tokens();

    if(auto opt = parse_arg<Arg>(begin, end)) 
        return opt.value();

    throw unexpected_token<Arg>();
}

template<typename Args, typename It, std::size_t ... Is>
inline Args parse_args(It& begin, It end, std::index_sequence<Is...>)
{
    return Args{
        parse_arg_exc<std::tuple_element_t<Is, Args>>(begin, end)...};
}

} //namespace detail

template<typename Command, typename It>
inline Command parse(It& begin, It end)
{
    using Tuple = decltype(std::declval<Command>().args);

    return Command{
            detail::parse_args<Tuple>(
                begin, end, 
                std::make_index_sequence<std::tuple_size_v<Tuple>>{})};
}

} //namespace todolist::Parser
