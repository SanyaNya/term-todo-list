#pragma once

namespace todolist::utils
{

enum class endian
{
#ifdef _WIN32
    little = 0,
    big    = 1,
    native = little
#else
    little = __ORDER_LITTLE_ENDIAN__,
    big    = __ORDER_BIG_ENDIAN__,
    native = __BYTE_ORDER__
#endif
};

inline unsigned short byteswap(unsigned short n) noexcept
{
#ifdef _MSC_VER
    return _byteswap_ushort(n);
#else
    return __builtin_bswap16(n);
#endif
}

inline unsigned long byteswap(unsigned long n) noexcept
{
#ifdef _MSC_VER
    return _byteswap_ulong(n);
#else
    return __builtin_bswap32(n);
#endif
}

inline unsigned long long byteswap(unsigned long long n) noexcept
{
#ifdef _MSC_VER
    return _byteswap_uint64(n);
#else
    return __builtin_bswap64(n);
#endif
}

template<typename T>
inline T host_to_network(T n) noexcept
{
    if constexpr(endian::native == endian::little)
        n = byteswap(n);
    return n;
}

template<typename T>
inline T network_to_host(T n) noexcept
{
    if constexpr(endian::native == endian::little)
        n = byteswap(n);
    return n;
}

} //namespace todolist::utils
