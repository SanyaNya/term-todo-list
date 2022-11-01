#pragma once

#include <utility>
#include <type_traits>
#include <fstream>

namespace todolist::utils
{

template<typename T, typename Location>
class file_resource
{
    T value;

    static T load()
    {
        std::ifstream is(
            Location::path, std::ios::in | std::ios::binary);
        return T::deserialize(is);
    }

public:
    file_resource() : value(load()) {}

    T& get() noexcept { return value; }
    const T& get() const noexcept { return value; }

    ~file_resource()
    {
        std::ofstream os(
            Location::path, std::ios::in | std::ios::binary);
        value.serialize(os);
    }
};

} //namespace todolist::utils