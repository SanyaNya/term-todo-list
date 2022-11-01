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
        serialization::serialize(os, name);
        serialization::serialize(os, description);
        serialization::serialize(os, date);
        serialization::serialize(os, category);
        serialization::serialize(os, status);
    }

    static Task deserialize(std::istream& is)
    {
        return Task
        {
            serialization::deserialize<std::string>(is),
            serialization::deserialize<std::string>(is),
            static_cast<std::time_t>(
                    serialization::deserialize<net_uint64>(is)),
            serialization::deserialize<std::string>(is),
            static_cast<bool>(serialization::deserialize<net_uint8>(is))
        };
    }
};

} //namespace todolist
