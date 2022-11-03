#pragma once

#include <functional>
#include "Tokenizer/Token/Token.hpp"
#include "Parser/parse.hpp"
#include "Date.hpp"
#include "LongString.hpp"

namespace todolist::Parser
{

namespace detail
{

template<typename Ref, typename T>
inline const auto& get_ref(const T& t)
{
    using namespace Tokenizer::Tokens;

    if constexpr(std::is_same_v<Ref, Kname>)
        return t.name;
    if constexpr(std::is_same_v<Ref, Kdescription>)
        return t.description;
    if constexpr(std::is_same_v<Ref, Kdate>)
        return t.date;
    if constexpr(std::is_same_v<Ref, Kcategory>)
        return t.category;
    if constexpr(std::is_same_v<Ref, Kstatus>)
        return t.status;
}

template<typename T1, typename T2>
inline bool less(const T1& t1, const T2& t2)
{
    return t1 < t2;
}

template<typename T1, typename T2>
inline bool less_or_equal(const T1& t1, const T2& t2)
{
    return t1 <= t2;
}

template<typename T1, typename T2>
inline bool greater(const T1& t1, const T2& t2)
{
    return t1 > t2;
}

template<typename T1, typename T2>
inline bool greater_or_equal(const T1& t1, const T2& t2)
{
    return t1 >= t2;
}

template<typename T1, typename T2>
inline bool equals(const T1& t1, const T2& t2)
{
    return t1 == t2;
}

template<typename T1, typename T2>
inline bool always_false(const T1&, const T2&)
{
    return false;
}

template<typename T1, typename T2>
inline auto get_cmp(Tokenizer::Tokens::Compare c, bool eq)
{
    using namespace Tokenizer::Tokens;

    return
        std::visit([eq](auto t)
        {
            using C = decltype(t);

            if(eq)
            {
                if constexpr(
                        std::is_same_v<C, Dless> &&
                        traits::is_less_valid_v<T1, T2>)
                    return less<T1, T2>;

                if constexpr(
                        std::is_same_v<C, Dgreater> &&
                        traits::is_greater_valid_v<T1, T2>)
                    return greater<T1, T2>;
            }
            else
            {
                if constexpr(
                        std::is_same_v<C, Dless> &&
                        traits::is_less_or_equal_valid_v<T1, T2>)
                    return less_or_equal<T1, T2>;

                if constexpr(
                        std::is_same_v<C, Dgreater> &&
                        traits::is_greater_or_equal_valid_v<T1, T2>)
                    return greater_or_equal<T1, T2>;
            }

            if constexpr(
                    std::is_same_v<C, Dequal> && 
                    traits::is_equals_valid_v<T1, T2>)
                return equals<T1, T2>;

            return always_false<T1, T2>;
        }, c);
}

template<typename T1, typename T2>
inline auto get_like()
{
    return 
        [](const T1& str, const T2& substr)
        { 
            return str.find(substr) != T1::npos; 
        };
}

} //namespace detail

template<typename T>
struct Predicate
{
    static constexpr std::string_view token_name = "Predicate";

    std::function<bool(const T&)> value;

    template<typename It>
    static std::optional<Predicate> parse(It& begin, It end) noexcept
    {
        using namespace Tokenizer::Tokens;

        It initial_begin = begin;

        std::optional<ReferenceKeyword> refopt;
        std::optional<Dspace> ls;
        std::optional<Compare> cmpopt;
        std::optional<Dequal> eqopt;
        std::optional<Dspace> rs;
        std::optional<Klike> likeopt;
        std::optional<String> stropt;
        std::optional<Number> numopt;
        std::optional<Bool> boolopt;
        std::optional<LongString> longstropt;
        std::optional<Date> dateopt;

        if(begin == end || !(refopt = Parser::parse_arg<ReferenceKeyword>(begin, end)))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end)
        {
            begin = initial_begin;
            return std::nullopt;
        }
        ls = Parser::parse_arg<Dspace>(begin, end);

        if(begin == end)
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end || 
           !((cmpopt = Parser::parse_arg<Compare>(begin, end)) ||
             (likeopt = Parser::parse_arg<Klike>(begin, end))))
        {
            begin = initial_begin;
            return std::nullopt;
        }

        if(begin == end)
        {
            begin = initial_begin;
            return std::nullopt;
        }
        eqopt = Parser::parse_arg<Dequal>(begin, end);

        if(begin == end)
        {
            begin = initial_begin;
            return std::nullopt;
        }
        rs = Parser::parse_arg<Dspace>(begin, end);

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

        std::variant<std::string_view, std::string, bool, std::time_t> val;
        if(stropt)       val = stropt.value().value;
        else if(numopt)  val = numopt.value().word;
        else if(boolopt) val = static_cast<bool>(boolopt.value().index());
        else if(dateopt) val = dateopt.value().value;

        return Predicate{
            std::visit([cmpopt, eqopt](auto r, auto v)
            {
                using R = decltype(r);
                using V = decltype(v);
                using RT =
                    std::decay_t<
                        std::invoke_result_t<
                            decltype(detail::get_ref<R, T>), 
                            const T&>>;

                if(cmpopt)
                {
                    auto cmp = 
                        detail::get_cmp<RT, V>(
                                cmpopt.value(), eqopt.has_value());

                    return std::function<bool(const T&)>{
                        [cmp, v](const T& t)
                        { 
                            const auto& ref = detail::get_ref<R, T>(t);
                            return cmp(ref, v); 
                        }};
                }
                
                if constexpr(
                    std::is_same_v<RT, std::string> && 
                    (std::is_same_v<V, std::string> || 
                     std::is_same_v<V, std::string_view>))
                {
                    auto like = detail::get_like<RT, V>();

                    return std::function<bool(const T&)>{
                        [like, v](const T& t)
                        {
                            const auto& ref = detail::get_ref<R>(t);
                            return like(ref, v);
                        }};
                }

                return 
                    std::function<bool(const T&)>{
                        [](const T&){ return false; }};
            }, refopt.value(), val)};
    }
};

} //namespace todolist::Parser
