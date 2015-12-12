#pragma once

#include <vector>
#include <memory>
#include <string>
#include "..\common\span.h"

namespace testns
{
    enum class testcls_token {
        close_curly,
        comment_content,
        comment_return,
        comment_start,
        equal,
        goto_,
        identifier,
        import,
        include,
        line_comment,
        open_curly,
        pattern,
        re_asterisk,
        re_char,
        re_close_curly,
        re_close_parenthesis,
        re_close_bracket,
        re_dot,
        re_escaped,
        re_exclude_set,
        re_hyphen,
        re_open_bracket,
        re_open_curly,
        re_open_parenthesis,
        re_pipe,
        re_plus,
        re_question,
        re_reference,
        re_return,
        re_start,
        return_,
        section,
        semi_colon,
        shared,
        string,
        token,
        whitespace,
    };
    inline auto test_cls_token_name(testcls_token tkn) -> std::wstring {
        switch(tkn) {
        case testcls_token::close_curly: return L"close-curly";
        case testcls_token::comment_content: return L"comment-content";
        case testcls_token::comment_return: return L"comment-return";
        case testcls_token::comment_start: return L"comment-start";
        case testcls_token::equal: return L"equal";
        case testcls_token::goto_: return L"goto";
        case testcls_token::identifier: return L"identifier";
        case testcls_token::import: return L"import";
        case testcls_token::include: return L"include";
        case testcls_token::line_comment: return L"line-comment";
        case testcls_token::open_curly: return L"open-curly";
        case testcls_token::pattern: return L"pattern";
        case testcls_token::re_asterisk: return L"re-asterisk";
        case testcls_token::re_char: return L"re-char";
        case testcls_token::re_close_curly: return L"re-close-curly";
        case testcls_token::re_close_parenthesis: return L"re-close-parenthesis";
        case testcls_token::re_close_bracket: return L"re-close_bracket";
        case testcls_token::re_dot: return L"re-dot";
        case testcls_token::re_escaped: return L"re-escaped";
        case testcls_token::re_exclude_set: return L"re-exclude-set";
        case testcls_token::re_hyphen: return L"re-hyphen";
        case testcls_token::re_open_bracket: return L"re-open-bracket";
        case testcls_token::re_open_curly: return L"re-open-curly";
        case testcls_token::re_open_parenthesis: return L"re-open-parenthesis";
        case testcls_token::re_pipe: return L"re-pipe";
        case testcls_token::re_plus: return L"re-plus";
        case testcls_token::re_question: return L"re-question";
        case testcls_token::re_reference: return L"re-reference";
        case testcls_token::re_return: return L"re-return";
        case testcls_token::re_start: return L"re-start";
        case testcls_token::return_: return L"return";
        case testcls_token::section: return L"section";
        case testcls_token::semi_colon: return L"semi-colon";
        case testcls_token::shared: return L"shared";
        case testcls_token::string: return L"string";
        case testcls_token::token: return L"token";
        case testcls_token::whitespace: return L"whitespace";
        default: return L"unknown";
        }
    }

    class testcls {
    public:
        auto operator()(std::vector<size_t> &statestack, std::wistream &stm, testcls_token &token, std::wstring &value, bool &is_eod, davecommon::span &spn) -> bool;
    };
}
