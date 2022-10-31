#pragma once

#include <string>
#include <ctime>
#include "utils/serialization.hpp"

namespace todolist
{

struct Task
{
    std::string name;
    std::string description;
    std::time_t date;
    std::string category;
    bool status;

    void serialize(std::ostream& os) const
    {
        utils::serialize(os, name);
        utils::serialize(os, description);
        utils::serialize(os, date);
        utils::serialize(os, category);
        utils::serialize(os, status);
    }

    static Task deserialize(std::istream& is)
    {
        return Task
        {
            utils::deserialize<std::string>(is),
            utils::deserialize<std::string>(is),
            utils::deserialize<std::time_t>(is),
            utils::deserialize<std::string>(is),
            utils::deserialize<bool>(is)
        };
    }
};

} //namespace todolist
