#pragma once

#include <variant>
#include "../define_delimiter.hpp"

namespace todolist::Tokenizer::Tokens
{

DEFINE_DELIMITER(quotes, '"')
DEFINE_DELIMITER(dot,    '.')
DEFINE_DELIMITER(dash,   '-')
DEFINE_DELIMITER(colon,  ':')

using Punctuation =
    std::variant<
        Dquotes,
        Ddot,
        Ddash,
        Dcolon>;

} //namespace todolist::Tokenizer::Token
