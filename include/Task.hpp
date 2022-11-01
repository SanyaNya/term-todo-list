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
        using serialization::net_uint8;
        using serialization::net_uint64;

        serialization::serialize(os, name);
        serialization::serialize(os, description);
        serialization::serialize(os, net_uint64(date));
        serialization::serialize(os, category);
        serialization::serialize(os, net_uint8(status));
    }

    static Task deserialize(std::istream& is)
    {
        using serialization::net_uint8;
        using serialization::net_uint64;

        return Task
        {
            serialization::deserialize<std::string>(is),
            serialization::deserialize<std::string>(is),
            static_cast<std::uint64_t>(
                    serialization::deserialize<net_uint64>(is)),
            serialization::deserialize<std::string>(is),
            static_cast<std::uint8_t>(serialization::deserialize<net_uint8>(is))
        };
    }
};

} //namespace todolist
