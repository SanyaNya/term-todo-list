#pragma once

#include <optional>
#include <variant>
#include "typelist_dfs.hpp"

namespace todolist::utils
{

namespace detail
{

template<typename Path>
struct dfs_holds_alternative_h {};

template<typename Head, typename ... Tail>
struct dfs_holds_alternative_h<std::tuple<Head, Tail...>>
{
    template<typename V>
    static bool f(V&& v) noexcept
    {
        if(std::holds_alternative<Head>(v))
            return dfs_holds_alternative_h<std::tuple<Tail...>>::f(
                    std::get<Head>(std::forward<V>(v)));

        return false;
    }
};

template<>
struct dfs_holds_alternative_h<std::tuple<>>
{
    template<typename V>
    static bool f(V&&) noexcept { return true; }
};

} //namespace detail

template<typename T, typename V>
inline bool dfs_holds_alternative(V&& v) noexcept
{
    using Path = typelist_path_dfs_t<std::decay_t<V>, T>;

    static_assert(!std::is_same_v<Path, void>, "V does not have T");

    return detail::dfs_holds_alternative_h<Path>::f(std::forward<V>(v));
}

} //namespace todolist::utils
