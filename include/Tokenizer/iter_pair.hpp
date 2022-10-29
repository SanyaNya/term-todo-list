#pragma once

#include "utils/ArgvIterator.hpp"
#include "Iterator.hpp"

namespace todolist::Tokenizer
{

inline auto iter_pair(const char* const* argv, int argc)
{
    using namespace todolist;

    utils::ArgvIterator argv_begin(argv, argc);
    utils::ArgvIterator argv_end(argv, argc, utils::null_sentinel{});

    Tokenizer::Iterator<utils::ArgvIterator> it(argv_begin);
    Tokenizer::Iterator<utils::ArgvIterator> end(argv_end);

    return std::make_pair(it, end);
}

} //namespace todolist::Tokenizer
