#pragma once

#include <iostream>
#include "traits/traits.hpp"

namespace todolist::serialization
{

template<typename T>
inline std::enable_if_t<traits::is_serializable_v<T>> 
serialize(std::ostream& os, const T& t)
{
    t.serialize(os);
}

template<typename T>
inline
std::enable_if_t<
    !traits::is_serializable_v<T> &&
    !std::is_integral_v<T>        &&
    std::is_trivially_copyable_v<T>>
serialize(std::ostream& os, const T& t)
{
    os.write(reinterpret_cast<const char*>(&t), sizeof(T));
}

template<typename T>
inline
std::enable_if_t<
    !traits::is_serializable_v<T>                   &&
    !std::is_trivially_copyable_v<T>                &&
    !traits::has_trivially_copyable_value_type_v<T> &&
    traits::has_size_v<T>                           &&
    traits::has_begin_end_v<T>>
serialize(std::ostream& os, const T& t)
{
    serialize(os, net_uint64(std::size(t)));
    for(const auto& obj : t)
        serialize(os, obj);
}

template<typename T>
inline
std::enable_if_t<
    !traits::is_serializable_v<T>                  &&
    !std::is_trivially_copyable_v<T>               &&
    traits::has_trivially_copyable_value_type_v<T> &&
    traits::has_size_v<T>                          &&
    traits::has_data_v<T>>
serialize(std::ostream& os, const T& t)
{
    serialize(os, net_uint64(std::size(t)));
    os.write(std::data(t), std::size(t)*sizeof(typename T::value_type));
}

} //namespace todolist::serialization
