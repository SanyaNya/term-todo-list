#pragma once

#include <iterator>
#include <cstring>
#include "null_sentinel.hpp"

namespace todolist::utils
{

class ArgvIterator
{
    char** argv;
    char** argv_end;
    char* cur;

public:
    using iterator_category = std::forward_iterator_tag;

    ArgvIterator(char** argv_, int argc_) noexcept : 
        argv(argv_), argv_end(argv + argc_), cur(*argv) {}

    ArgvIterator(char** argv_, int argc_, null_sentinel) noexcept :
        ArgvIterator(argv_, argc_) 
    {
        cur = *(argv + (argc_ - 1));
        cur = cur + std::strlen(cur); 
    }

    operator const char*() const noexcept
    {
        return cur;
    }

    bool operator!=(ArgvIterator& it) const noexcept
    {
        return cur != it.cur;
    }

    bool operator!=(null_sentinel) const noexcept
    {
        return *cur != null_sentinel{};
    }

    char operator*() const noexcept
    {
        return *cur;
    }

    ArgvIterator& operator++() noexcept
    {
        if(*cur != null_sentinel{}) ++cur;
        else if(++argv != argv_end) cur = *argv;

        return *this;
    }
};

} //namespace todolist::utils
