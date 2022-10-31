#pragma once

#include "Types/ReferenceKeyword.hpp"
#include "Types/LinkKeyword.hpp"
#include "Types/Number.hpp"
#include "Types/String.hpp"

namespace todolist::Tokenizer::Tokens
{

using Word =
    std::variant<
        ReferenceKeyword,
        LinkKeyword,
        Number,
        String>;

} //namespace todolist::Tokenizer::Token
