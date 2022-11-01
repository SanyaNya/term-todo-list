#pragma once

#include <string>
#include <ctime>
#include "serialization/serialization.hpp"

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
        using namespace serialization;

        serialize(os, name);
        serialize(os, description);
        serialize(os, date);
        serialize(os, category);
        serialize(os, status);
    }

    static Task deserialize(std::istream& is)
    {
        using namespace serialization;

        return Task
        {
            deserialize<std::string>(is),
            deserialize<std::string>(is),
            static_cast<std::time_t>(deserialize<net_uint64>(is)),
            deserialize<std::string>(is),
            static_cast<bool>(deserialize<net_uint8>(is))
        };
    }
};

} //namespace todolist
