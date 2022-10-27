#pragma once

#define DEFINE_DELIMITER(NAME, SYMBOL)       \
    struct D ## NAME                         \
    {                                        \
        static constexpr char name = SYMBOL; \
    };
