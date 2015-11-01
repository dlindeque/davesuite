#pragma once

#include <string>
#include "..\common\span.h"

using namespace davecommon;

namespace davelexer
{
    enum class token_type {
        regex
    };

    struct token {
        span spn;
        token_type type;
        std::wstring value;
    };
}