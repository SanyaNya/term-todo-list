#pragma once

#include <variant>
#include "../define_keyword.hpp"

namespace todolist::Tokenizer::Tokens
{

DEFINE_KEYWORD(off)
DEFINE_KEYWORD(on)

using Bool = std::variant<Koff, Kon>;

} //namespace todolist::Tokenizer::Tokens
