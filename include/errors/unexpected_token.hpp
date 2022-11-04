#pragma once

#include <stdexcept>
#include "traits/is_variant.hpp"

namespace todolist::Parser
{

namespace detail
{

template<typename T>
struct get_token_name
{
    static std::string f()
    {
        return std::string(T::token_name);
    }
};

template<typename ... Ts>
struct get_token_name<std::variant<Ts...>>
{
    static std::string f()
    {
        return "[" + ((get_token_name<Ts>::f() + ", ") + ...) + "]";
    }
};

} //namespace detail

template<typename T>
struct unexpected_token : std::runtime_error
{
    unexpected_token() : 
        std::runtime_error(
            "Unexpected token. Expected: " + 
            detail::get_token_name<T>::f()) {}
};

} //namespace todolist::Parser
