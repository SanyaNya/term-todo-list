#pragma once

#include <tuple>
#include "Parser/parse.hpp"

namespace todolist::Parser
{

namespace detail
{

template<size_t I, typename It, typename Tuple>
inline bool tuple_parse(It& begin, It end, Tuple& tuple) noexcept
{
    using T = std::tuple_element_t<I, Tuple>;

    if(begin == end) return false;

    if(auto opt = Parser::parse_arg<T>(begin, end))
        std::get<I>(tuple) = opt.value();
    else
        return false;

    if constexpr(I+1 != std::tuple_size_v<Tuple>)
        return tuple_parse<I+1>(begin, end, tuple);
    else
        return true;
}

} //namespace detail

template<typename ... Ts>
struct Tuple
{
    static constexpr std::string_view token_name = "Arg";

    std::tuple<Ts...> value;

    template<typename It>
    static std::optional<Tuple> parse(It& begin, It end) noexcept
    {
        Tuple t;
        It initial_begin = begin;

        if(!detail::tuple_parse<0>(begin, end, t.value))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        return t;
    }
};

} //namespace todolist::Parser
