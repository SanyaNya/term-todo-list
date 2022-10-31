#pragma once

#include "Types/Compare.hpp"
#include "Types/Punctuation.hpp"
#include "Types/Empty.hpp"
#include "Types/Star.hpp"

namespace todolist::Tokenizer::Tokens
{

using Delimiter =
    std::variant<
        Compare,
        Punctuation,
        Empty,
        Dstar>;

} //namespace todolist::Tokenizer::Token
