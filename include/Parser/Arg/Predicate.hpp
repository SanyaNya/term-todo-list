#pragma once

#include "Tokenizer/Token/Token.hpp"
#include "Parser/parse.hpp"

namespace todolist::Parser
{

struct Predicate
{
    static constexpr std::string_view token_name = "Predicate";

    Tokenizer::Tokens::ReferenceKeyword ref;
    std::variant<Tokenizer::Tokens::Compare, Tokenizer::Tokens::Klike> cmp;
    Tokenizer::Token value;

    template<typename It>
    static std::optional<Predicate> parse(It& begin, It end) noexcept
    {
        using Ref = Tokenizer::Tokens::ReferenceKeyword;
        using Space = Tokenizer::Tokens::Dspace;
        using Cmp = Tokenizer::Tokens::Compare;
        using Like = Tokenizer::Tokens::Klike;
        using Token = Tokenizer::Token;
        It initial_begin = begin;

        std::optional<Ref> refopt;
        std::optional<Space> ls;
        std::optional<Cmp> cmpopt;
        std::optional<Space> rs;
        std::optional<Like> likeopt;
        std::optional<Token> vopt;

        if(begin == end || !(refopt = Parser::parse_arg<Ref>(begin, end)))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end)
        {
            begin = initial_begin;
            return std::nullopt;
        }
        ls = Parser::parse_arg<Space>(begin, end);

        if(begin == end)
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end || 
           !((cmpopt = Parser::parse_arg<Cmp>(begin, end)) ||
             (likeopt = Parser::parse_arg<Like>(begin, end))))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end)
        {
            begin = initial_begin;
            return std::nullopt;
        }
        rs = Parser::parse_arg<Space>(begin, end);

        if(likeopt && (!ls || !rs))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end || !(vopt = Parser::parse_arg<Token>(begin, end)))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        return Predicate
        { 
            refopt.value(), 
            (cmpopt ? 
             decltype(cmp){cmpopt.value()} : 
             decltype(cmp){likeopt.value()}), 
            vopt.value()
        };
    }
};

} //namespace todolist::Parser
