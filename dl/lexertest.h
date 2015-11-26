#pragma once

#include <vector>
#include <memory>
#include <string>
#include "..\common\span.h"

namespace testns
{
    enum class testcls_token {
        identifier,
        whitespace,
        return_,
        comment_start,
        comment_content,
        comment_return,
        line_comment,
        equal,
        re_start,
        re_return,
        semi_colon,
        open_curly,
        close_curly,
        string,
        re_exclude_set,
        re_reference,
        re_char,
        token,
        shared,
        section,
        include,
        import,
        goto_,
        re_open_parenthesis,
        re_close_parenthesis,
        re_asterisk,
        re_plus,
        re_hyphen,
        re_dot,
        re_question,
        re_open_bracket,
        re_close_bracket,
        re_open_curly,
        re_pipe,
        re_close_curly,
        pattern,
        re_escaped
    };

    class testcls {
    public:
        auto operator()(std::vector<size_t> &statestack, std::wistream &stm, testcls_token &token, std::wstring &value, bool &is_eod, davecommon::span &spn) -> bool;
    };
}