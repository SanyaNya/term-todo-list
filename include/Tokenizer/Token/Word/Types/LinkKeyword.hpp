#pragma once

#include <variant>
#include "../define_keyword.hpp"

namespace todolist::Tokenizer::Tokens
{

DEFINE_KEYWORD(where)
DEFINE_KEYWORD(and)
DEFINE_KEYWORD(like)

using LinkKeyword =
    std::variant<
        Kwhere,
        Kand,
        Klike>;

} //namespace todolist::Tokenizer::Tokens
