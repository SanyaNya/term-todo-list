#pragma once

#include <cstdint>
#include <type_traits>
#include "utils/endian.hpp"

namespace todolist::serialization
{

namespace detail
{

template<typename T>
struct net_integral
{
    T value;

    static_assert(std::is_integral_v<T>);

public:
    net_integral() = default;
    net_integral(const net_integral&) = default;
    net_integral(net_integral&&) = default;
    net_integral& operator=(const net_integral&) = default;
    net_integral& operator=(net_integral&&) = default;

    explicit net_integral(T v) noexcept :
        value(utils::host_to_network(v)) {}


    explicit operator T() const noexcept
    {
        return utils::network_to_host(value);
    }
};

} //namespace detail

using net_uint8  = detail::net_integral<std::uint8_t>;
using net_uint16 = detail::net_integral<std::uint16_t>;
using net_uint32 = detail::net_integral<std::uint32_t>;
using net_uint64 = detail::net_integral<std::uint64_t>;

} //namespace todolist::serialization
