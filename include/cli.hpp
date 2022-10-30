#pragma once

#include <tuple>
#include "Tokenizer/iter_pair.hpp"
#include "Parser/parse.hpp"
#include "utils/dfs_get.hpp"

namespace todolist
{

template<typename Command>
struct CLI
{
    using iterator = Tokenizer::Iterator<utils::ArgvIterator>;

    iterator begin;
    iterator end;

    CLI(const char* const* argv, int argc) : 
        begin(utils::ArgvIterator(argv, argc)),
        end(utils::ArgvIterator(argv, argc, utils::null_sentinel{})) {}

    auto parse()
    {
        using Tokenizer::Tokens::String;

        auto v = Tokenizer::match<Command>(
                    utils::dfs_get<String>(*begin++).value).value();

        return 
            std::visit([&](auto t)
            { 
                return Command{Parser::parse<decltype(t)>(begin, end)}; 
            }, v);
    }

    static void execute(Command& cmd)
    {
        std::visit([](auto t){ t.execute(); }, cmd);
    }
};

} //namespace todolist
