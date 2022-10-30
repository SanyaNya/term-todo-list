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

} //namespace todolist::utils
