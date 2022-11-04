#pragma once

#include <stdexcept>

namespace todolist::Parser
{

struct unexpected_tokens_after_command final : std::runtime_error
{
    unexpected_tokens_after_command() : 
        std::runtime_error("Unexpected tokens after command") {}
};

} //namespace todolist::Parser
