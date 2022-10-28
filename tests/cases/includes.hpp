#pragma once

#include <cassert>
#include <utility>
#include <array>
#include "utils/ArgvIterator.hpp"
#include "Tokenizer/Iterator.hpp"

template<size_t SIZE>
inline auto token_iter_pair(const std::array<const char*, SIZE>& argv)
{
    using namespace todolist;

    utils::ArgvIterator argv_begin(std::data(argv), argv.size());
    utils::ArgvIterator argv_end(std::data(argv), argv.size(), utils::null_sentinel{});

    Tokenizer::Iterator<utils::ArgvIterator> it(argv_begin);
    Tokenizer::Iterator<utils::ArgvIterator> end(argv_end);

    return std::make_pair(it, end);
}

template<typename It>
inline void check_keyword(It iter, It end, size_t i, const std::string& name)
{
    using namespace todolist;
    using namespace todolist::Tokenizer::Tokens;

    assert(iter != end);
    Tokenizer::Token w = *iter;
    assert(std::holds_alternative<Word>(w));
    assert(std::holds_alternative<Keyword>(std::get<Word>(w)));
    assert(std::get<Keyword>(std::get<Word>(w)).index() == i);
    std::visit(
        [=](auto t)
        {
            assert(decltype(t)::name == name);
        }, std::get<Keyword>(std::get<Word>(w)));
}

template<typename It>
inline void check_num(It iter, It end, int val)
{
    using namespace todolist;
    using namespace todolist::Tokenizer::Tokens;

    assert(iter != end);
    Tokenizer::Token w = *iter;
    assert(std::holds_alternative<Word>(w));
    assert(std::holds_alternative<Number>(std::get<Word>(w)));
    Number n = std::get<Number>(std::get<Word>(w));
    assert(n.value == val);
}

template<typename It>
inline void check_string(It iter, It end, const std::string& s)
{
    using namespace todolist;
    using namespace todolist::Tokenizer::Tokens;

    assert(iter != end);
    Tokenizer::Token w = *iter;
    assert(std::holds_alternative<Word>(w));
    assert(std::holds_alternative<String>(std::get<Word>(w)));
    String str = std::get<String>(std::get<Word>(w));
    assert(str.value == s);
}

template<typename T1, typename T2, typename It>
inline void check_delim(It iter, It end)
{
    using namespace todolist;
    using namespace todolist::Tokenizer::Tokens;

    assert(iter != end);
    Tokenizer::Token w = *iter;
    assert(std::holds_alternative<Delimiter>(w));
    assert(std::holds_alternative<T1>(std::get<Delimiter>(w)));
    assert(std::holds_alternative<T2>(std::get<T1>(std::get<Delimiter>(w))));
}
