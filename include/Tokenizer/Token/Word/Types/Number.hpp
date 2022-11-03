#pragma once

#include <string_view>
#include <optional>
#include <charconv>

namespace todolist::Tokenizer::Tokens
{

struct Number
{
    static constexpr std::string_view token_name = "number";

    unsigned value;
    std::string_view word;

    static std::optional<Number> match(std::string_view word) noexcept
    {
        unsigned val;
        const auto [ptr, err] = 
            std::from_chars(word.begin(), word.end(), val);

        if(ptr == word.end()) 
            return Number{val, word};
        
        return std::nullopt;
    }
};

} //namespace todolist::Tokenizer::Token
