#pragma once

#include <string_view>

#define DEFINE_KEYWORD(NAME)                                  \
    struct K ## NAME                                          \
    {                                                         \
        static constexpr std::string_view name = #NAME;       \
        static constexpr std::string_view token_name = #NAME; \
    };

