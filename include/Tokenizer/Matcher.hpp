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

    Matcher(RawToken w) noexcept : word(w) {}

    template<typename T>
    std::optional<T> operator()() const noexcept
    {
        if constexpr(utils::is_variant_v<T>) 
            return utils::variant_type_match<T, Matcher<RawToken>>(*this);

        if constexpr(utils::is_named_v<T>)
            return T::name == word ? std::optional<T>{T{}} : std::nullopt;

        if constexpr(utils::is_matchable_v<T>)
            return T::match(word);
    }
};

template<typename Token, typename RawToken>
inline std::optional<Token> match(RawToken word) noexcept
{
    Matcher<RawToken> m(word);
    return m.template operator()<Token>();
}

} //namespace todolist::Tokenizer::Tokens
