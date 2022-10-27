#pragma once

#include "Types/Compare.hpp"
#include "Types/Punctuation.hpp"
#include "Types/Empty.hpp"

namespace todolist::Tokenizer::Tokens
{

using Delimiter =
    std::variant<
        Compare,
        Punctuation,
        Empty>;

} //namespace todolist::Tokenizer::Token
