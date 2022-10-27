#pragma once

#include "Delimiter/Delimiter.hpp"
#include "Word/Word.hpp"

namespace todolist::Tokenizer
{

using Token =
    std::variant<
        Tokens::Delimiter,
        Tokens::Word>;

} //namespace todolist::Tokenizer
