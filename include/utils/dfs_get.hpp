#pragma once

#include <optional>
#include "typelist_dfs.hpp"
#include <variant>

namespace todolist::utils
{

template<typename Path>
struct dfs_get_h {};

template<typename Head, typename ... Tail>
struct dfs_get_h<std::tuple<Head, Tail...>>
{
    template<typename V>
    static auto f(V&& v)
    {
        return dfs_get_h<std::tuple<Tail...>>::f(
                    std::get<Head>(std::forward<V>(v)));
    }
};

template<>
struct dfs_get_h<std::tuple<>>
{
    template<typename V>
    static auto f(V&& v)
    {
        return v;
    }
};

template<typename T, typename V>
inline T dfs_get(V&& v)
{
    using Path = typelist_path_dfs_t<std::decay_t<V>, T>;

    static_assert(!std::is_same_v<Path, void>, "V does not have T");

    return dfs_get_h<Path>::f(std::forward<V>(v));
}

} //namespace todolist::utils
