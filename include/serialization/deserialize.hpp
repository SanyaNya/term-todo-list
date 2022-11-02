#pragma once

#include <iostream>
#include <type_traits>
#include "traits/traits.hpp"
#include "utils/func_iterator.hpp"
#include "net_integral.hpp"

namespace todolist::serialization
{

template<typename T>
inline
std::enable_if_t<traits::is_deserializable_v<T>, T> f(std::istream& is)
{
    return T::deserialize(is);
}

template<typename T>
inline 
std::enable_if_t<
    !traits::is_deserializable_v<T> &&
    !std::is_integral_v<T>          &&
    std::is_trivially_copyable_v<T> &&
    std::is_default_constructible_v<T>, T> deserialize(std::istream& is)
{
    T t;
    is.read(reinterpret_cast<char*>(&t), sizeof(T));

    return t;
}

template<typename T>
inline 
std::enable_if_t<
    !traits::is_deserializable_v<T>                          &&
    !std::is_trivially_copyable_v<T>                         &&
    traits::has_value_type_v<T>                              &&
    !traits::has_value_type_v<T, std::is_trivially_copyable> &&
    traits::is_range_constructible_v<T>, T> deserialize(std::istream& is)
{
    const auto f = [&is]()
    { 
        return deserialize<typename T::value_type>(is); 
    };

    size_t sz{static_cast<std::uint64_t>(deserialize<net_uint64>(is))};
    return T{utils::func_iterator(f, 0), utils::func_iterator(f, sz)};
}

template<typename T>
inline 
std::enable_if_t<
    !traits::is_deserializable_v<T>                         &&
    !std::is_trivially_copyable_v<T>                        &&
    std::is_default_constructible_v<T>                      &&
    traits::is_resizable_v<T>                               &&
    traits::has_value_type_v<T>                             &&
    traits::has_value_type_v<T, std::is_trivially_copyable> &&
    traits::has_data_v<T>, T> deserialize(std::istream& is)
{
    size_t sz{static_cast<std::uint64_t>(deserialize<net_uint64>(is))};
    T t;
    t.resize(sz);

    is.read(std::data(t), sz * sizeof(typename T::value_type));

    return t;
}

} //namespace todolist::serialization
