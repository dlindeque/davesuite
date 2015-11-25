#pragma once

#include <memory>
#include <istream>
#include <unordered_map>
#include "dfa.h"
#include "..\common\span.h"

namespace davelexer
{
    class lexer {
    private:
        dfa _dfa;
    public:
        lexer(dfa &&dfa)
            : _dfa(std::move(dfa))
        {}

        auto operator()(std::vector<size_t> &statestack, std::wistream &stm, std::shared_ptr<std::wstring> &token, std::wstring &value, bool &is_eod, span &spn) -> bool;
    };
}