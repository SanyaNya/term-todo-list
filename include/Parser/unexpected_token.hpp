#pragma once

#include <stdexcept>

namespace todolist::Parser
{

template<typename T>
struct unexpected_token : std::runtime_error
{
    unexpected_token() : 
        std::runtime_error(
            "Unexpected token: expected " + 
            std::string(T::token_name.begin(), T::token_name.end())) {}
};

} //namespace todolist::Parser
