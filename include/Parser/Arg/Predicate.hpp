#pragma once

#include "Tokenizer/Token/Token.hpp"
#include "Parser/parse.hpp"
#include "Date.hpp"
#include "LongString.hpp"

namespace todolist::Parser
{

struct Predicate
{
    static constexpr std::string_view token_name = "Predicate";

    Tokenizer::Tokens::ReferenceKeyword ref;
    std::variant<Tokenizer::Tokens::Compare, Tokenizer::Tokens::Klike> cmp;
    std::optional<Tokenizer::Tokens::Dequal> eqopt;
    std::variant<Tokenizer::Tokens::String, Tokenizer::Tokens::Bool, LongString, Date> value;

    template<typename It>
    static std::optional<Predicate> parse(It& begin, It end) noexcept
    {
        using Ref = Tokenizer::Tokens::ReferenceKeyword;
        using Space = Tokenizer::Tokens::Dspace;
        using Cmp = Tokenizer::Tokens::Compare;
        using Like = Tokenizer::Tokens::Klike;
        using Equal = Tokenizer::Tokens::Dequal;
        using String = Tokenizer::Tokens::String;
        using Number = Tokenizer::Tokens::Number;
        using Bool = Tokenizer::Tokens::Bool;
        It initial_begin = begin;

        std::optional<Ref> refopt;
        std::optional<Space> ls;
        std::optional<Cmp> cmpopt;
        std::optional<Equal> eqopt;
        std::optional<Space> rs;
        std::optional<Like> likeopt;
        std::optional<String> stropt;
        std::optional<Number> numopt;
        std::optional<Bool> boolopt;
        std::optional<LongString> longstropt;
        std::optional<Date> dateopt;

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

        eqopt = Parser::parse_arg<Equal>(begin, end);

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

        if(begin == end || 
           !((stropt     = Parser::parse_arg<String>(begin, end))     ||
             (numopt     = Parser::parse_arg<Number>(begin, end))     ||
             (boolopt    = Parser::parse_arg<Bool>(begin, end))       ||
             (longstropt = Parser::parse_arg<LongString>(begin, end)) ||
             (dateopt    = Parser::parse_arg<Date>(begin, end))))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        Predicate p;

        p.ref = refopt.value();

        if(cmpopt) p.cmp = cmpopt.value();
        else       p.cmp = likeopt.value();

        p.eqopt = eqopt;

        if(stropt)          p.value = stropt.value();
        else if(numopt)     p.value = String{numopt.value().word};
        else if(boolopt)    p.value = boolopt.value();
        else if(longstropt) p.value = longstropt.value();
        else if(dateopt)    p.value = dateopt.value();

        return p;
    }
};

} //namespace todolist::Parser
