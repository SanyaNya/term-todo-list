#pragma once

#define DEFINE_KEYWORD(NAME)                            \
    struct K ## NAME                                    \
    {                                                   \
        static constexpr std::string_view name = #NAME; \
    };

