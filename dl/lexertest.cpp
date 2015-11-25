#include "stdafx.h"
#include "lexertest.h"
#include <assert.h>

namespace testns
{
    auto testcls::operator()(std::vector<size_t> &statestack, std::wistream &stm, testcls_token &token, std::wstring &value, bool &is_eod, davecommon::span &spn) -> bool {
        struct helper {
            static inline auto no_match_action(size_t sstate, std::vector<size_t> &statestack, std::wistream &stm, testcls_token &token, std::wstring &value, bool &is_eod, davecommon::span &spn, const size_t &rewind_state, int rewind_count, const davecommon::position &rewind_position) -> bool {
                while (true) {
                    switch (sstate) {
                    // Non final states
                    case 0:
                    case 11:
                        if (rewind_state == 0) {
                            return false; // Cannot rewind
                        }
                        else {
                            for (int i = 0; i < rewind_count; i++) {
                                stm.unget();
                            }
                            spn.end = rewind_position;
                            value.resize(value.size() - rewind_count);
                            sstate = rewind_state;
                        }
                        break;
                    // Final states
                    case 2:
                        token = testcls_token::identifier;
                        return true;
                    case 4:
                        token = testcls_token::identifier;
                        return true;
                    case 6:
                        token = testcls_token::number;
                        return true;
                    case 7:
                        token = testcls_token::number;
                        return true;
                    case 9:
                        token = testcls_token::number;
                        return true;
                    case 12:
                        token = testcls_token::number;
                        return true;
                    case 14:
                        token = testcls_token::number;
                        return true;
                    case 22:
                        token = testcls_token::whitespace;
                        return true;
                    case 24:
                        token = testcls_token::whitespace;
                        return true;
                    case 25:
                        token = testcls_token::identifier;
                        return true;
                    case 26:
                        token = testcls_token::identifier;
                        return true;
                    case 27:
                        token = testcls_token::identifier;
                        return true;
                    case 28:
                        token = testcls_token::identifier;
                        return true;
                    case 29:
                        token = testcls_token::identifier;
                        return true;
                    case 30:
                        token = testcls_token::return_;
                        return true;
                    default:
                        assert(false); // Invalid state
                        return false;
                    }
                }
            }
            static inline auto match_action(wchar_t ch, std::wstring &value, davecommon::span &spn) -> void {
                value += ch;
                if (ch == L'\n') {
                    spn.end.line++;
                    spn.end.column = 1;
                }
                else if (ch == L'\r') {
                    spn.end.column = 1;
                }
                else {
                    spn.end.column++;
                }
            }
        };
        spn.begin = spn.end;
        auto sstate = statestack.back();
        value.clear();
        is_eod = false;
        size_t rewind_state = 0;
        int rewind_count = 0;
        davecommon::position rewind_position;
        while (true) {
            wchar_t ch;
            if (!stm.get(ch)) {
                is_eod = true;
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
            }
            switch (sstate) {
            case 0:
                switch (ch) {
                case L'\t':
                    helper::match_action(ch, value, spn);
                    sstate = 22;
                    break;
                case L'\n':
                    helper::match_action(ch, value, spn);
                    sstate = 22;
                    break;
                case L'\v':
                    helper::match_action(ch, value, spn);
                    sstate = 22;
                    break;
                case L'\f':
                    helper::match_action(ch, value, spn);
                    sstate = 22;
                    break;
                case L'\r':
                    helper::match_action(ch, value, spn);
                    sstate = 22;
                    break;
                case L' ':
                    helper::match_action(ch, value, spn);
                    sstate = 22;
                    break;
                case L'0':
                    helper::match_action(ch, value, spn);
                    sstate = 6;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 2;
                    break;
                case L'r':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'q') {
                        helper::match_action(ch, value, spn);
                        sstate = 2;
                    }
                    else if (ch >= L's' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 2;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 2;
                    }
                    else if (ch >= L'1' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 7;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_count++;
                break;
            case 2:
                switch (ch) {
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 2;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 4:
                switch (ch) {
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 4;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 7:
                switch (ch) {
                case L'.':
                    helper::match_action(ch, value, spn);
                    sstate = 11;
                    break;
                default:
                    if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 9;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 7;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 9:
                switch (ch) {
                case L'.':
                    helper::match_action(ch, value, spn);
                    sstate = 11;
                    break;
                default:
                    if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 9;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 9;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 6:
                switch (ch) {
                case L'.':
                    helper::match_action(ch, value, spn);
                    sstate = 11;
                    break;
                default:
                    stm.unget();
                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    break;
                }
                rewind_state = 6;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 11:
                if (ch >= L'0' && ch <= L'9') {
                    helper::match_action(ch, value, spn);
                    sstate = 12;
                }
                else {
                    stm.unget();
                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                }
                rewind_count++;
                break;
            case 12:
                if (ch >= L'0' && ch <= L'9') {
                    helper::match_action(ch, value, spn);
                    sstate = 14;
                }
                else {
                    stm.unget();
                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                }
                rewind_state = 12;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 14:
                if (ch >= L'0' && ch <= L'9') {
                    helper::match_action(ch, value, spn);
                    sstate = 14;
                }
                else {
                    stm.unget();
                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                }
                rewind_state = 14;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 22:
                switch (ch) {
                case L'\t':
                    helper::match_action(ch, value, spn);
                    sstate = 24;
                    break;
                case L'\n':
                    helper::match_action(ch, value, spn);
                    sstate = 24;
                    break;
                case L'\v':
                    helper::match_action(ch, value, spn);
                    sstate = 24;
                    break;
                case L'\f':
                    helper::match_action(ch, value, spn);
                    sstate = 24;
                    break;
                case L'\r':
                    helper::match_action(ch, value, spn);
                    sstate = 24;
                    break;
                case L' ':
                    helper::match_action(ch, value, spn);
                    sstate = 24;
                    break;
                default:
                    stm.unget();
                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    break;
                }
                rewind_state = 22;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 24:
                switch (ch) {
                case L'\t':
                    helper::match_action(ch, value, spn);
                    sstate = 24;
                    break;
                case L'\n':
                    helper::match_action(ch, value, spn);
                    sstate = 24;
                    break;
                case L'\v':
                    helper::match_action(ch, value, spn);
                    sstate = 24;
                    break;
                case L'\f':
                    helper::match_action(ch, value, spn);
                    sstate = 24;
                    break;
                case L'\r':
                    helper::match_action(ch, value, spn);
                    sstate = 24;
                    break;
                case L' ':
                    helper::match_action(ch, value, spn);
                    sstate = 24;
                    break;
                default:
                    stm.unget();
                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    break;
                }
                rewind_state = 24;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 25:
                switch (ch) {
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L'e':
                    helper::match_action(ch, value, spn);
                    sstate = 26;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'd') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'f' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 25;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 26:
                switch (ch) {
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L't':
                    helper::match_action(ch, value, spn);
                    sstate = 27;
                    break;
                default:
                    if (ch >= L'a' && ch <= L's') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'u' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 26;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 27:
                switch (ch) {
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L'u':
                    helper::match_action(ch, value, spn);
                    sstate = 28;
                    break;
                default:
                    if (ch >= L'a' && ch <= L't') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'v' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 27;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 28:
                switch (ch) {
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L'r':
                    helper::match_action(ch, value, spn);
                    sstate = 29;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'q') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L's' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 28;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 29:
                switch (ch) {
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L'n':
                    helper::match_action(ch, value, spn);
                    sstate = 30;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'm') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'o' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 29;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 30:
                switch (ch) {
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 4;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 30;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            default:
                assert(false); // Invalid state
                break;
            }
        }
    }
}