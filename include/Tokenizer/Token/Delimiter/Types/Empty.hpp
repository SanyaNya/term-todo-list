#pragma once

#include <variant>
#include "../define_delimiter.hpp"

namespace todolist::Tokenizer::Tokens
{

DEFINE_DELIMITER(space,   ' ')
DEFINE_DELIMITER(newline, '\n')
DEFINE_DELIMITER(tab,     '\t')

using Empty = 
    std::variant<
        Dspace,
        Dnewline,
        Dtab>;

} //namespace todolist::Tokenizer::Token
