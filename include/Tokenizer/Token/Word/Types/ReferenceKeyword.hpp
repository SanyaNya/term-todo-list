#pragma once

#include <variant>
#include "../define_keyword.hpp"

namespace todolist::Tokenizer::Tokens
{

DEFINE_KEYWORD(name)
DEFINE_KEYWORD(description)
DEFINE_KEYWORD(date)
DEFINE_KEYWORD(category)
DEFINE_KEYWORD(status)

using ReferenceKeyword =
    std::variant<
        Kname,
        Kdescription,
        Kdate,
        Kcategory,
        Kstatus>;

} //namespace todolist::Tokenizer::Token
