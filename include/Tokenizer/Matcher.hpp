#pragma once

#include "utils/variant_type_match.hpp"
#include "traits/traits.hpp"

namespace todolist::Tokenizer
{

template<typename RawToken>
struct Matcher
{
    RawToken word;

    template<typename U>
    Matcher(U&& w) noexcept : word(w)
    {
        static_assert(std::is_nothrow_constructible_v<RawToken, U&&>);
    }

    Matcher(const Matcher&) noexcept = default;
    Matcher(Matcher&&) noexcept = default;

    template<typename T>
    std::optional<T> operator()() const noexcept
    {
        if constexpr(traits::is_variant_v<T>) 
            return utils::variant_type_match<T>(*this);

        if constexpr(traits::is_matchable_v<T, RawToken>)
            return T::match(word);
        
        if constexpr(traits::is_named_v<T>)
            return T::name == word ? std::optional<T>{T{}} : std::nullopt;
    }
};

template<typename Token, typename RawToken>
inline std::optional<Token> match(RawToken word) noexcept
{
    Matcher<RawToken> m(word);
    return m.template operator()<Token>();
}

} //namespace todolist::Tokenizer::Tokens
