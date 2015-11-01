#pragma once

#include <istream>
#include "..\common\span.h"

using namespace davecommon;

namespace davelexer
{
    enum class re_token_type
    {
        eod,
        char_,
        char_set,
        name,
        hyphen,
        bracket_left,
        bracket_right,
        ex_bracket_left,
        parenthesis_left,
        parenthesis_right,
        pipe,
        output,
        cardinality
    };

    enum class re_char_set {
        word,
        digit,
        lalpha,
        ualpha,
        space,
        any
    };

    struct re_token {
        span spn;
        re_token_type type;
        wchar_t char_;
        re_char_set cs;
        std::wstring name_output_whitespace;
        int cardinality_min;
        int cardinality_max;
    };

    auto re_lex(
        std::wistream &src,
        register int &end_line, register int &end_column,
        register int &state,
        re_token &token)->void;
}