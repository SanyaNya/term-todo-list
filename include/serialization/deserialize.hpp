#pragma once

#include <iostream>
#include <type_traits>
#include "traits/traits.hpp"
#include "utils/func_iterator.hpp"
#include "net_integral.hpp"

namespace todolist::serialization
{

template<typename T>
inline std::decay_t<T> deserialize(std::istream& is);

namespace detail
{

template<typename T, size_t ... Is>
inline T expand_deserialize(std::istream& is, std::index_sequence<Is...>)
{
    return T{deserialize<std::tuple_element_t<Is, T>>(is)...};
}

template<typename T>
inline T deserialize_h(std::istream& is)
{
    if constexpr(traits::is_deserializable_v<T>)
        return T::deserialize(is);
    else
    {
        if constexpr(
            std::is_trivially_copyable_v<T> && 
            std::is_default_constructible_v<T>)
        {
            static_assert(
                !std::is_integral_v<T>, 
                "Serialization of integrals is forbidden, use net_uint types");

            T t;
            is.read(reinterpret_cast<char*>(&t), sizeof(T));

            return t;
        }
        else
        {
            if constexpr(
                traits::has_begin_end_v<T> && traits::has_size_v<T>)
            {
                if constexpr(
                    traits::has_data_v<T> &&
                    traits::has_value_type_v<
                        T, std::is_trivially_copyable> &&
                    traits::is_resizable_v<T>)
                {
                    size_t sz{
                        static_cast<std::uint64_t>(
                            deserialize<net_uint64>(is))};
                    T t;
                    t.resize(sz);

                    is.read(
                        std::data(t), 
                        static_cast<std::streamsize>(
                            sz * sizeof(typename T::value_type)));

                    return t;
                }
                else if constexpr(
                    traits::has_value_type_v<T> &&
                    traits::is_range_constructible_v<T>)
                {
                    const auto f = [&is]()
                    { 
                        return deserialize<typename T::value_type>(is); 
                    };

                    size_t sz{
                        static_cast<std::uint64_t>(
                            deserialize<net_uint64>(is))};

                    return T
                    {
                        utils::func_iterator(f, 0), 
                        utils::func_iterator(f, sz)
                    };
                }
            }
            else if constexpr(traits::is_tuple_like_v<T>)
            {
                return expand_deserialize<T>(
                        is,
                        std::make_index_sequence<
                            std::tuple_size_v<T>>{});
            }
        }
    }
}

} //namespace detail

template<typename T>
inline std::decay_t<T> deserialize(std::istream& is)
{
    return detail::deserialize_h<std::decay_t<T>>(is);
}

} //namespace todolist::serialization
