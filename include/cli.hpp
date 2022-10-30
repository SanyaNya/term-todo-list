#pragma once

#include <tuple>
#include <stdexcept>
#include "Tokenizer/iter_pair.hpp"
#include "Parser/parse.hpp"
#include "utils/dfs_get.hpp"
#include "utils/dfs_holds_alternative.hpp"
#include "Parser/unexpected_end_of_tokens.hpp"
#include "Parser/unexpected_token.hpp"
#include "Parser/cmd_not_found.hpp"

namespace todolist
{

template<typename Command>
class CLI
{
    using iterator = Tokenizer::Iterator<utils::ArgvIterator>;

    iterator begin;
    iterator end;

public:
    CLI(const char* const* argv, int argc) : 
        begin(utils::ArgvIterator(argv, argc)),
        end(utils::ArgvIterator(argv, argc, utils::null_sentinel{})) {}

    auto parse()
    {
        using Tokenizer::Tokens::String;

        if(begin == end)
            throw Parser::unexpected_end_of_tokens();

        if(!utils::dfs_holds_alternative<String>(*begin))
            throw Parser::unexpected_token<String>();

        const auto w = utils::dfs_get<String>(*begin++).value;

        const auto optcmd = Tokenizer::match<Command>(w);

        if(!optcmd) 
            throw Parser::cmd_not_found{std::string(w.begin(), w.end())};

        return 
            std::visit([&](auto t)
            { 
                return Command{Parser::parse<decltype(t)>(begin, end)}; 
            }, optcmd.value());
    }

    static void execute(Command& cmd)
    {
        std::visit([](auto t){ t.execute(); }, cmd);
    }
};

} //namespace todolist
