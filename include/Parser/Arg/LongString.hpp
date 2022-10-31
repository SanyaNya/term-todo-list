#pragma once

#include <string>
#include "Parser/parse.hpp"
#include "Tokenizer/Token/Token.hpp"

namespace todolist::Parser
{

struct LongString
{
    static constexpr std::string_view token_name = "LongString";

    std::string value;

    template<typename It>
    static std::optional<LongString> parse(It& begin, It end) noexcept
    {
        using Quotes = Tokenizer::Tokens::Dquotes;

        if(begin != end && Parser::parse_arg<Quotes>(begin, end))
        {
            LongString ls;

            while(begin != end)
            {
                auto rt = begin.raw_token();
                auto t = Parser::parse_arg<
                            Tokenizer::Token>(begin, end).value();

                if(utils::dfs_holds_alternative<Quotes>(t))
                    break;

                ls.value += rt;
            }

            return ls;
        }

        return std::nullopt;
    }
};

} //namespace todolist::Parser
