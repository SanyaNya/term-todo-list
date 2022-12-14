#pragma once

#include <iterator>
#include <algorithm>
#include "utils/null_sentinel.hpp"
#include "Matcher.hpp"
#include "Token/Token.hpp"

namespace todolist::Tokenizer
{

template<typename It>
class Iterator
{
    It cur_word;
    It next_delim;

    It find_next_delim() noexcept
    {
        using null = utils::null_sentinel;

        It p = cur_word;
        while(*p != null{} && !match<Tokens::Delimiter>(*p)) ++p;

        return p;
    }

public:
    using iterator_category = std::input_iterator_tag;
    using value_type = Token;
    using pointer = Token*;
    using reference = Token&;
    using difference_type = int;

    Iterator(It it) noexcept : 
        cur_word(it), next_delim(find_next_delim()) {}

    bool operator!=(Iterator it) const noexcept
    {
        return cur_word != it.cur_word;
    }

    bool operator==(Iterator it) const noexcept
    {
        return cur_word == it.cur_word;
    }

    Token operator*() const noexcept
    {
        if(cur_word != next_delim) 
            return match<Tokens::Word>(
                    cur_word.token(next_delim)).value();
        else
            return match<Tokens::Delimiter>(*cur_word).value();
    }

    std::string raw_token() const
    {
        std::string res;

        if(cur_word != next_delim)
            std::copy(cur_word, next_delim, std::back_inserter(res));
        else res.push_back(*next_delim);

        return res;
    }

    Iterator& operator++() noexcept
    {
        if(cur_word == next_delim)
        {
            ++cur_word;
            next_delim = find_next_delim();
        }
        else cur_word = next_delim;

        return *this;
    }

    Iterator operator++(int) noexcept
    {
        Iterator it = *this;
        ++(*this);
        return it;
    }
};

} //namespace todolist::Tokenizer
