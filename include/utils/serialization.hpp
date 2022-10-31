#pragma once

#include "utils/endian.hpp"
#include <iostream>
#include <ctime>

namespace todolist::utils
{

inline void serialize(std::ostream& os, const std::string& s)
{
    auto sz = utils::host_to_network(static_cast<std::uint64_t>(s.size()));
    os.write(reinterpret_cast<char*>(&sz), sizeof(sz));
    os.write(s.data(), s.size());
}

inline void serialize(std::ostream& os, std::time_t t)
{
    auto n = utils::host_to_network(static_cast<std::uint64_t>(t));
    os.write(reinterpret_cast<char*>(&n), sizeof(n));
}

inline void serialize(std::ostream& os, bool b)
{
    os.put(static_cast<char>(b));
}

namespace detail
{

template<typename T>
struct deserialize_h;

template<>
struct deserialize_h<size_t>
{
    static size_t f(std::istream& is)
    {
        std::uint64_t n;
        is.read(reinterpret_cast<char*>(&n), sizeof(n));

        return static_cast<size_t>(utils::network_to_host(n));
    }
};

template<>
struct deserialize_h<std::time_t>
{
    static std::time_t f(std::istream& is)
    {
        std::uint64_t n;
        is.read(reinterpret_cast<char*>(&n), sizeof(n));

        return static_cast<std::time_t>(utils::network_to_host(n));
    }
};

template<>
struct deserialize_h<bool>
{
    static bool f(std::istream& is)
    {
        char c;
        is.get(c);

        return static_cast<bool>(c);
    }
};

template<>
struct deserialize_h<std::string>
{
    static std::string f(std::istream& is)
    {
        size_t sz = deserialize_h<size_t>::f(is);

        std::string s(sz, 0);

        is.read(s.data(), sz);

        return s;
    }
};

} //namespace detail

template<typename T>
inline T deserialize(std::istream& is)
{
    return detail::deserialize_h<T>::f(is);
}

}
