#pragma once

#include "utils/endian.hpp"
#include <iostream>
#include <ctime>

namespace todolist::utils
{

inline void serialize(std::ostream& os, std::uint64_t n)
{
    auto nn = utils::host_to_network(static_cast<std::uint64_t>(n));
    os.write(reinterpret_cast<char*>(&nn), sizeof(nn));
}

inline void serialize(std::ostream& os, size_t size)
{
    serialize(os, static_cast<std::uint64_t>(size));
}

inline void serialize(std::ostream& os, std::time_t t)
{
    serialize(os, static_cast<std::uint64_t>(t));
}

inline void serialize(std::ostream& os, char c)
{
    os.put(c);
}

inline void serialize(std::ostream& os, bool b)
{
    serialize(os, static_cast<char>(b));
}

inline void serialize(std::ostream& os, const std::string& s)
{
    serialize(os, s.size());
    os.write(s.data(), static_cast<std::streamsize>(s.size()));
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

        is.read(s.data(), static_cast<std::streamsize>(sz));

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
