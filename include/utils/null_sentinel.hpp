#pragma once

namespace todolist::utils
{

struct null_sentinel
{
    constexpr operator char() const noexcept
    {
        return '\0';
    }
};

inline constexpr bool operator==(char c, null_sentinel)
{ 
    return c == '\0'; 
}

inline constexpr bool operator!=(char c, null_sentinel)
{ 
    return c != '\0'; 
}

} //namespace todolist::utils
