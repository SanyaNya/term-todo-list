#pragma once

#include <string>
#include <ctime>

namespace todolist
{

struct Task
{
    std::string name;
    std::string description;
    std::time_t date;
    std::string category;
    bool status;
};

} //namespace todolist
