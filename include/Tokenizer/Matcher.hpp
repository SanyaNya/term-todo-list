#pragma once

#include "utils/variant_type_match.hpp"
#include "utils/is_variant.hpp"
#include "utils/is_named.hpp"
#include "utils/is_matchable.hpp"

namespace todolist::Tokenizer
{

template<typename RawToken>
struct Matcher
{
    RawToken word;

    template<typename U>
    Matcher(U&& w) 
        noexcept(std::is_nothrow_constructible_v<RawToken, U&&>) : 
            word(w) {}

    Matcher(const Matcher&) = default;
    Matcher(Matcher&&) = default;

    template<typename T>
    std::optional<T> operator()() const 
        noexcept(
            (utils::is_matchable_v<T, RawToken> && 
             utils::is_nothrow_matchable_v<T, RawToken>) ||
            (utils::is_named_v<T> && 
             std::is_nothrow_constructible_v<T, T&&>))
    {
        if constexpr(utils::is_variant_v<T>) 
            return utils::variant_type_match<T>(*this);

        if constexpr(utils::is_matchable_v<T, RawToken>)
            return T::match(word);
        
        if constexpr(utils::is_named_v<T>)
            return T::name == word ? std::optional<T>{T{}} : std::nullopt;
    }
};

template<typename Token, typename RawToken>
inline std::optional<Token> match(RawToken word) 
    noexcept(noexcept(
        std::declval<Matcher<RawToken>>().template operator()<Token>()))
{
    Matcher<RawToken> m(word);
    return m.template operator()<Token>();
}

} //namespace todolist::Tokenizer::Tokens
