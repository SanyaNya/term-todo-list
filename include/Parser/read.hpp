#pragma once

#include "utils/ArgvIterator.hpp"
#include "Tokenizer/Iterator.hpp"
#include "Arg/Arg.hpp"
#include "parse.hpp"

namespace todolist::Parser
{

template<typename T, typename R = decltype(T::value)>
inline R read_arg(const char* invocation)
{
    std::string buf;

    std::cout << invocation;
    std::getline(std::cin, buf);

    for(size_t i = 0; ; ++i)
    {
        if(buf[i] == '\0') break;
        if(buf[i] == '\\') buf.erase(i, 1);
        if(buf[i] == '\0') break;
    }

    const char* const bufcstr = buf.c_str();
    
    Tokenizer::Iterator begin(
            utils::ArgvIterator(&bufcstr, 1));
    Tokenizer::Iterator end(
            utils::ArgvIterator(&bufcstr, 1, utils::null_sentinel{}));

    std::optional<T> opt = Parser::parse_arg<T>(begin, end);

    if(opt)
        return R{opt.value().value};
    else 
        throw Parser::unexpected_token<T>();
}

} //namespace todolist::Parser
