#pragma once

#include "Types/Keyword.hpp"
#include "Types/Number.hpp"
#include "Types/String.hpp"

namespace todolist::Tokenizer::Tokens
{

using Word =
    std::variant<
        Keyword,
        Number,
        String>;

} //namespace todolist::Tokenizer::Token
