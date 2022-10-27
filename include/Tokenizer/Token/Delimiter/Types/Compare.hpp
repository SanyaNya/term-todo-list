#pragma once

#include <optional>
#include <variant>
#include "../define_delimiter.hpp"

namespace todolist::Tokenizer::Tokens
{

DEFINE_DELIMITER(less,    '<')
DEFINE_DELIMITER(greater, '>')
DEFINE_DELIMITER(equal,   '=')

using Compare =
    std::variant<
        Dless,
        Dgreater,
        Dequal>;

} //namespace todolist::Tokenizer::Token
