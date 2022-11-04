#pragma once

#include <ctime>
#include "Parser/parse.hpp"
#include "Tokenizer/Token/Token.hpp"

namespace todolist::Parser
{

struct Date
{
    static constexpr std::string_view token_name = "Date";

    std::time_t value;

    template<typename It>
    static std::optional<Date> parse(It& begin, It end) noexcept
    {
        using Quotes = Tokenizer::Tokens::Dquotes;
        using Num = Tokenizer::Tokens::Number;
        using Dash = Tokenizer::Tokens::Ddash;
        using Colon = Tokenizer::Tokens::Dcolon;
        using Empty = Tokenizer::Tokens::Empty;

        It initial_begin = begin;

        Date date;
        std::optional<Num> year, month, day, hours, minutes;
        std::tm t;

        if(begin == end || !Parser::parse_arg<Quotes>(begin, end))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end || !(year = Parser::parse_arg<Num>(begin, end)))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end || !(Parser::parse_arg<Dash>(begin, end)))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end || !(month = Parser::parse_arg<Num>(begin, end)))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end || !(Parser::parse_arg<Dash>(begin, end)))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end || !(day = Parser::parse_arg<Num>(begin, end)))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end || !(Parser::parse_arg<Empty>(begin, end)))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end || !(hours = Parser::parse_arg<Num>(begin, end)))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end || !(Parser::parse_arg<Colon>(begin, end)))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end || !(minutes = Parser::parse_arg<Num>(begin, end)))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end || !Parser::parse_arg<Quotes>(begin, end))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        t.tm_year = static_cast<int>(year.value().value - 1900);
        t.tm_mon  = static_cast<int>(month.value().value - 1);
        t.tm_mday = static_cast<int>(day.value().value);
        t.tm_hour = static_cast<int>(hours.value().value);
        t.tm_min  = static_cast<int>(minutes.value().value);
        t.tm_isdst = 0;

        date.value = std::mktime(&t);

        return date;
    }
};

} //namespace todolist::Parser
