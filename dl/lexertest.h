#pragma once

#include <vector>
#include <memory>
#include <string>
#include "..\common\span.h"

namespace testns
{
    enum class testcls_token {
        identifier,
        number,
        whitespace,
        return_
    };

    class testcls {
    public:
        auto operator()(std::vector<size_t> &statestack, std::wistream &stm, testcls_token &token, std::wstring &value, bool &is_eod, davecommon::span &spn) -> bool;
    };
}