#pragma once

#include <string_view>
#include <optional>
#include <variant>
#include "../define_keyword.hpp"

namespace todolist::Tokenizer::Tokens
{

DEFINE_KEYWORD(name)
DEFINE_KEYWORD(description)
DEFINE_KEYWORD(date)
DEFINE_KEYWORD(category)
DEFINE_KEYWORD(status)
DEFINE_KEYWORD(where)
DEFINE_KEYWORD(and)
DEFINE_KEYWORD(like)

using Keyword =
    std::variant<
        Kname,
        Kdescription,
        Kdate,
        Kcategory,
        Kstatus,
        Kwhere,
        Kand,
        Klike>;

} //namespace todolist::Tokenizer::Token
