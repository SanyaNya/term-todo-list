#pragma once

#include <iostream>
#include <vector>
#include "Parser/parse.hpp"
#include "Tokenizer/Token/Delimiter/Types/Empty.hpp"

namespace todolist::Parser
{

template<typename Arg, typename Delim = Tokenizer::Tokens::Empty>
struct VarArray
{
    static constexpr std::string_view token_name = "VarArray";

    std::vector<Arg> array;

    template<typename It>
    static std::optional<VarArray> parse(It& begin, It end) noexcept
    {
        VarArray va;

        while(true)
        {
            std::optional<Arg> opt;
            if(begin != end && (opt = Parser::parse_arg<Arg>(begin, end)))
                va.array.emplace_back(opt.value());
            else 
                break;

            if(begin == end || !Parser::parse_arg<Delim>(begin, end))
                break;
        }

        return va;
    }
};

} //namespace todolist::Parser
