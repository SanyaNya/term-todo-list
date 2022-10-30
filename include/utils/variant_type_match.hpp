#pragma once

#include <optional>
#include <variant>

namespace todolist::utils
{

template<typename Variant, typename Predicate, size_t I = 0>
inline std::optional<Variant> variant_type_match(const Predicate& p = Predicate())
    noexcept(noexcept(
        p.template operator()<std::variant_alternative_t<I, Variant>>()))
{
    using T = std::variant_alternative_t<I, Variant>;

    static_assert(
        std::is_invocable_r_v<
            std::optional<T>,
            decltype(&Predicate::template operator()<T>), 
            Predicate*>,
        "Predicate must return std::optional and have no args");

    if(auto opt = p.template operator()<T>()) 
        return opt;
    
    if constexpr(I+1 != std::variant_size_v<Variant>)
        return variant_type_match<Variant, Predicate, I+1>(p);
    else
        return std::nullopt;
}

} //namespace todolist::utils
