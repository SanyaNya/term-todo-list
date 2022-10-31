#pragma once

#include <string_view>

#define DEFINE_DELIMITER(NAME, SYMBOL)                        \
    struct D ## NAME                                          \
    {                                                         \
        static constexpr char name = SYMBOL;                  \
        static constexpr std::string_view token_name = #NAME; \
    };
