#pragma once

#include <iostream>
#include "traits/traits.hpp"
#include "net_integral.hpp"

namespace todolist::serialization
{

template<typename T>
inline void serialize(std::ostream& os, const T& t);

namespace detail
{

template<typename T, size_t ... Is>
void expand_serialize(
        std::ostream& os, const T& t, std::index_sequence<Is...>)
{
    (serialize(os, std::get<Is>(t)), ...);
}

} //namespace detail

template<typename T>
inline void serialize(std::ostream& os, const T& t)
{
    if constexpr(traits::is_serializable_v<T>)
        t.serialize(os);
    else
    {
        if constexpr(std::is_trivially_copyable_v<T>)
        {
            static_assert(
                !std::is_integral_v<T>, 
                "Serialization of integrals is forbidden, use net_uint types");

            os.write(reinterpret_cast<const char*>(&t), sizeof(T));
        }
        else
        {
            if constexpr(
                traits::has_begin_end_v<T> && traits::has_size_v<T>)
            {
                if constexpr(
                    traits::has_data_v<T> && 
                    traits::has_value_type_v<
                        T, std::is_trivially_copyable>)
                {
                    serialize(os, net_uint64(std::size(t)));
                    os.write(
                        std::data(t), 
                        static_cast<std::streamsize>(
                            std::size(t)*sizeof(typename T::value_type)));
                }
                else
                {
                    serialize(os, net_uint64(std::size(t)));
                    for(const auto& obj : t)
                        serialize(os, obj);
                }
            }
            else if constexpr(traits::is_tuple_like_v<T>)
            {
                serialize(os, net_uint64(std::tuple_size_v<T>));
                detail::expand_serialize(
                    os, t, 
                    std::make_index_sequence<std::tuple_size_v<T>>{});
            }
        }
    }
}

} //namespace todolist::serialization
