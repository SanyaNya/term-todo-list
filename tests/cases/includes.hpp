#pragma once

#include <cassert>
#include <utility>
#include <array>
#include "Tokenizer/iter_pair.hpp"

template<typename KW, typename It>
inline void check_keyword(It iter, It end, size_t i, const std::string& name)
{
    using namespace todolist;
    using namespace todolist::Tokenizer::Tokens;

    assert(iter != end);
    Tokenizer::Token w = *iter;
    assert(std::holds_alternative<Word>(w));
    assert(std::holds_alternative<KW>(std::get<Word>(w)));
    assert(std::get<KW>(std::get<Word>(w)).index() == i);
    std::visit(
        [=](auto t)
        {
            assert(decltype(t)::name == name);
        }, std::get<KW>(std::get<Word>(w)));
}

template<typename It>
inline void check_num(It iter, It end, unsigned val)
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
