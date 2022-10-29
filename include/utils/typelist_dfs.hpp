#pragma once

#include <cstddef>
#include <type_traits>
#include <tuple>
#include "type_identity.hpp"

namespace todolist::utils
{

namespace detail
{

template<typename List>
struct find_valid;

template<
    typename Head, typename ... Tail>
struct find_valid<std::tuple<Head, Tail...>> :
    std::conditional<
        !std::is_same_v<Head, void>,
        Head,
        typename find_valid<std::tuple<Tail...>>::type> {};

template<>
struct find_valid<std::tuple<>> : 
    type_identity<void> {};

} //namespace detail


template<typename L, typename T, typename ... Path>
struct typelist_path_dfs :
    std::conditional<
        std::is_same_v<L, T>, std::tuple<Path...>, void> {};

template<
    template<typename...> typename List, typename ... Args,
    typename T, typename ... Path>
struct typelist_path_dfs<List<Args...>, T, Path...> :
    std::conditional<
        std::is_same_v<List<Args...>, T>,
        std::tuple<Path...>,
        typename detail::find_valid<
            std::tuple<
                typename typelist_path_dfs<
                    Args, T, Path..., Args>::type...>>::type> {};

template<typename List, typename T>
using typelist_path_dfs_t = 
    typename typelist_path_dfs<List, T>::type;

} //namespace
