#pragma once

#include <iterator>
#include <cstring>
#include "null_sentinel.hpp"

namespace todolist::utils
{

class ArgvIterator
{
    const char** argv;
    const char* cur;
    const char* end;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = char;
    using pointer = char*;
    using reference = char&;
    using difference_type = int;

    ArgvIterator(const char** argv_, int argc_) noexcept : 
        argv(argv_), cur(*argv)
    {
        end = *(argv + (argc_ - 1));
        end = end + std::strlen(end); 
    }

    ArgvIterator(const char** argv_, int argc_, null_sentinel) noexcept :
        ArgvIterator(argv_, argc_) 
    {
        cur = end;
    }

    std::string_view token() const noexcept
    {
        return cur;
    }

    std::string_view token(const ArgvIterator& e) const noexcept
    {
        return {cur, static_cast<size_t>(e.cur-cur)};
    }

    void to_next_token() noexcept
    {
        cur = *(++argv);
    }

    bool operator!=(const ArgvIterator& it) const noexcept
    {
        return cur != it.cur;
    }

    bool operator!=(null_sentinel) const noexcept
    {
        return *cur != null_sentinel{};
    }

    bool operator==(const ArgvIterator& it) const noexcept
    {
        return cur == it.cur;
    }

    bool operator==(null_sentinel) const noexcept
    {
        return *cur == null_sentinel{};
    }

    char operator*() const noexcept
    {
        if(*cur == null_sentinel{} && cur != end) return ' ';
        
        return *cur;
    }

    ArgvIterator& operator++() noexcept
    {
        if(*cur != null_sentinel{}) ++cur;
        else cur = *(++argv);

        return *this;
    }
};

} //namespace todolist::utils
