#pragma once

#include <stdexcept>

namespace todolist::Parser
{

struct cmd_not_found : std::runtime_error
{
    cmd_not_found(const std::string& name) : 
        std::runtime_error("Command " + name + " not found") {}
};

} //namespace todolist::Parser
