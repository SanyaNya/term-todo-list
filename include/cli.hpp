#pragma once

#include <tuple>
#include <stdexcept>
#include "Tokenizer/iter_pair.hpp"
#include "Parser/parse.hpp"
#include "utils/dfs_get.hpp"
#include "utils/dfs_holds_alternative.hpp"

namespace todolist
{

template<typename Command>
class CLI
{
    using iterator = Tokenizer::Iterator<utils::ArgvIterator>;

    iterator begin;
    iterator end;

    template<typename T>
    static void print_help()
    {
        std::cout << T::name << " info: " << T::info << "\n";
        std::cout << T::name << " usage: " << T::usage << "\n\n";
    }

    template<size_t ... Is>
    static void print_help(std::index_sequence<Is...>)
    {
        (print_help<std::variant_alternative_t<Is, Command>>(), ...);
    }

public:
    CLI(const char* const* argv, int argc) : 
        begin(utils::ArgvIterator(argv, argc)),
        end(utils::ArgvIterator(argv, argc, utils::null_sentinel{})) {}

    auto parse_and_exec()
    {
        using Tokenizer::Tokens::String;

        if(begin == end)
        {
            std::cout << "Use help [NAME]\n";
            return;
        }

        if(!utils::dfs_holds_alternative<String>(*begin))
            throw Parser::unexpected_token<String>();

        const auto w = utils::dfs_get<String>(*begin++).value;

        if(w == "help")
        {
            if(begin != end)
            {
                ++begin;
                const auto cmdw = utils::dfs_get<String>(*begin++).value;
                const auto optcmd = Tokenizer::match<Command>(cmdw);

                if(!optcmd) 
                    throw Parser::cmd_not_found{
                            std::string(w.begin(), w.end())};

                std::visit([](auto t)
                {
                    print_help<decltype(t)>();
                }, optcmd.value());
            }
            else
            {
                print_help(
                    std::make_index_sequence<
                        std::variant_size_v<Command>>{});
            }

            return;
        }

        const auto optcmd = Tokenizer::match<Command>(w);

        if(!optcmd) 
            throw Parser::cmd_not_found{std::string(w.begin(), w.end())};

        return 
            std::visit([&](auto t)
            { 
                auto cmd = Parser::parse<decltype(t)>(begin, end);
                cmd.execute();
            }, optcmd.value());
    }
};

} //namespace todolist
