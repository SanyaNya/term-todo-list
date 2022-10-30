#pragma once

#include <stdexcept>

namespace todolist::Parser
{

struct unexpected_end_of_tokens final : std::runtime_error
{
    unexpected_end_of_tokens() : 
        std::runtime_error("Unexpected end of tokens") {}
};

} //namespace todolist::Parser
