#pragma once

#include <string_view>
#include <optional>

namespace todolist::Tokenizer::Tokens
{

struct String
{
    static constexpr std::string_view token_name = "string";

    std::string_view value;

    static std::optional<String> match(std::string_view word) noexcept
    {
        return String{word};
    }
};

} //namespace todolist::Tokenizer::Token
