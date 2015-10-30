#pragma once

#include <string>
#include "..\common\span.h"

using namespace davecommon;

namespace daveparser
{
    enum class token_type {
        identifier
    };

    struct token_value {
        token_type type;
        std::wstring value;
    };

    struct token {
        token_value value;
        span span;
    };
}