#pragma once

#include <string_view>
#include <optional>
#include <charconv>

namespace todolist::Tokenizer::Tokens
{

struct Number
{
    int value;

    static std::optional<Number> match(std::string_view word)
    {
        int val;
        const auto [ptr, err] = 
            std::from_chars(word.begin(), word.end(), val);

        if(ptr == word.end()) 
            return Number{val};
        
        return std::nullopt;
    }
};

} //namespace todolist::Tokenizer::Token
