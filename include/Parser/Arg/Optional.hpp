#pragma once

#include "Parser/parse.hpp"

namespace todolist::Parser
{

template<typename Arg>
struct Optional
{
    static constexpr std::string_view token_name = "Optional";

    std::optional<Arg> value;

    template<typename It>
    static std::optional<Optional> parse(It& begin, It end) noexcept
    {
        return Optional{Parser::parse_arg<Arg>(begin, end)};
    }
};

} //namespace todolist::Parser
