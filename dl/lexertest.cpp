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
                    case 7:
                    case 10:
                    case 22:
                    case 74:
                    case 76:
                    case 77:
                    case 85:
                    case 102:
                    case 104:
                    case 124:
                    case 171:
                    case 172:
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
                        token = testcls_token::whitespace;
                        return true;
                    case 4:
                        token = testcls_token::whitespace;
                        return true;
                    case 5:
                        token = testcls_token::line_comment;
                        return true;
                    case 11:
                        statestack.push_back(77);
                        token = testcls_token::comment_start;
                        return true;
                    case 23:
                        token = testcls_token::identifier;
                        return true;
                    case 25:
                        token = testcls_token::identifier;
                        return true;
                    case 26:
                        token = testcls_token::equal;
                        return true;
                    case 27:
                        statestack.push_back(85);
                        token = testcls_token::re_start;
                        return true;
                    case 28:
                        token = testcls_token::semi_colon;
                        return true;
                    case 42:
                        token = testcls_token::open_curly;
                        return true;
                    case 43:
                        token = testcls_token::close_curly;
                        return true;
                    case 72:
                        token = testcls_token::string;
                        return true;
                    case 78:
                        statestack.pop_back();
                        assert(!statestack.empty());
                        token = testcls_token::comment_return;
                        return true;
                    case 80:
                        token = testcls_token::comment_content;
                        return true;
                    case 81:
                        token = testcls_token::comment_content;
                        return true;
                    case 83:
                        token = testcls_token::comment_content;
                        return true;
                    case 93:
                        token = testcls_token::re_exclude_set;
                        return true;
                    case 99:
                        token = testcls_token::re_reference;
                        return true;
                    case 107:
                        token = testcls_token::re_escaped;
                        return true;
                    case 109:
                        token = testcls_token::re_char;
                        return true;
                    case 110:
                        statestack.pop_back();
                        assert(!statestack.empty());
                        token = testcls_token::re_return;
                        return true;
                    case 111:
                        token = testcls_token::re_open_parenthesis;
                        return true;
                    case 112:
                        token = testcls_token::re_close_parenthesis;
                        return true;
                    case 113:
                        token = testcls_token::re_asterisk;
                        return true;
                    case 114:
                        token = testcls_token::re_plus;
                        return true;
                    case 115:
                        token = testcls_token::re_hyphen;
                        return true;
                    case 116:
                        token = testcls_token::re_dot;
                        return true;
                    case 117:
                        token = testcls_token::re_question;
                        return true;
                    case 118:
                        token = testcls_token::re_open_bracket;
                        return true;
                    case 119:
                        token = testcls_token::re_char;
                        return true;
                    case 120:
                        token = testcls_token::re_close_bracket;
                        return true;
                    case 121:
                        token = testcls_token::re_open_curly;
                        return true;
                    case 122:
                        token = testcls_token::re_pipe;
                        return true;
                    case 123:
                        token = testcls_token::re_close_curly;
                        return true;
                    case 125:
                        token = testcls_token::identifier;
                        return true;
                    case 126:
                        token = testcls_token::identifier;
                        return true;
                    case 127:
                        token = testcls_token::identifier;
                        return true;
                    case 128:
                        token = testcls_token::identifier;
                        return true;
                    case 129:
                        token = testcls_token::identifier;
                        return true;
                    case 130:
                        token = testcls_token::identifier;
                        return true;
                    case 131:
                        token = testcls_token::identifier;
                        return true;
                    case 132:
                        token = testcls_token::identifier;
                        return true;
                    case 133:
                        token = testcls_token::identifier;
                        return true;
                    case 134:
                        token = testcls_token::identifier;
                        return true;
                    case 135:
                        token = testcls_token::identifier;
                        return true;
                    case 136:
                        token = testcls_token::identifier;
                        return true;
                    case 137:
                        token = testcls_token::identifier;
                        return true;
                    case 138:
                        token = testcls_token::identifier;
                        return true;
                    case 139:
                        token = testcls_token::identifier;
                        return true;
                    case 140:
                        token = testcls_token::identifier;
                        return true;
                    case 141:
                        token = testcls_token::identifier;
                        return true;
                    case 142:
                        token = testcls_token::identifier;
                        return true;
                    case 143:
                        token = testcls_token::identifier;
                        return true;
                    case 144:
                        token = testcls_token::identifier;
                        return true;
                    case 145:
                        token = testcls_token::identifier;
                        return true;
                    case 146:
                        token = testcls_token::identifier;
                        return true;
                    case 147:
                        token = testcls_token::identifier;
                        return true;
                    case 148:
                        token = testcls_token::identifier;
                        return true;
                    case 149:
                        token = testcls_token::identifier;
                        return true;
                    case 150:
                        token = testcls_token::identifier;
                        return true;
                    case 151:
                        token = testcls_token::identifier;
                        return true;
                    case 152:
                        token = testcls_token::identifier;
                        return true;
                    case 153:
                        token = testcls_token::identifier;
                        return true;
                    case 154:
                        token = testcls_token::identifier;
                        return true;
                    case 155:
                        token = testcls_token::identifier;
                        return true;
                    case 156:
                        token = testcls_token::pattern;
                        return true;
                    case 157:
                        token = testcls_token::identifier;
                        return true;
                    case 158:
                        token = testcls_token::identifier;
                        return true;
                    case 159:
                        token = testcls_token::identifier;
                        return true;
                    case 160:
                        token = testcls_token::identifier;
                        return true;
                    case 161:
                        token = testcls_token::identifier;
                        return true;
                    case 162:
                        token = testcls_token::identifier;
                        return true;
                    case 163:
                        token = testcls_token::identifier;
                        return true;
                    case 164:
                        token = testcls_token::identifier;
                        return true;
                    case 165:
                        token = testcls_token::identifier;
                        return true;
                    case 166:
                        token = testcls_token::identifier;
                        return true;
                    case 167:
                        token = testcls_token::identifier;
                        return true;
                    case 168:
                        token = testcls_token::identifier;
                        return true;
                    case 169:
                        token = testcls_token::identifier;
                        return true;
                    case 170:
                        token = testcls_token::identifier;
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
            case 128:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'e':
                    helper::match_action(ch, value, spn);
                    sstate = 146;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'd') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'f' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 128;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 0:
                switch (ch) {
                case L'\t':
                    helper::match_action(ch, value, spn);
                    sstate = 2;
                    break;
                case L'\n':
                    helper::match_action(ch, value, spn);
                    sstate = 2;
                    break;
                case L'\v':
                    helper::match_action(ch, value, spn);
                    sstate = 2;
                    break;
                case L'\f':
                    helper::match_action(ch, value, spn);
                    sstate = 2;
                    break;
                case L'\r':
                    helper::match_action(ch, value, spn);
                    sstate = 2;
                    break;
                case L'\x0020':
                    helper::match_action(ch, value, spn);
                    sstate = 2;
                    break;
                case L'"':
                    helper::match_action(ch, value, spn);
                    sstate = 74;
                    break;
                case L'\x0027':
                    helper::match_action(ch, value, spn);
                    sstate = 27;
                    break;
                case L'/':
                    helper::match_action(ch, value, spn);
                    sstate = 124;
                    break;
                case L';':
                    helper::match_action(ch, value, spn);
                    sstate = 28;
                    break;
                case L'=':
                    helper::match_action(ch, value, spn);
                    sstate = 26;
                    break;
                case L'@':
                    helper::match_action(ch, value, spn);
                    sstate = 22;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 23;
                    break;
                case L'g':
                    helper::match_action(ch, value, spn);
                    sstate = 125;
                    break;
                case L'h':
                    helper::match_action(ch, value, spn);
                    sstate = 23;
                    break;
                case L'i':
                    helper::match_action(ch, value, spn);
                    sstate = 126;
                    break;
                case L'p':
                    helper::match_action(ch, value, spn);
                    sstate = 127;
                    break;
                case L'q':
                    helper::match_action(ch, value, spn);
                    sstate = 23;
                    break;
                case L'r':
                    helper::match_action(ch, value, spn);
                    sstate = 128;
                    break;
                case L's':
                    helper::match_action(ch, value, spn);
                    sstate = 129;
                    break;
                case L't':
                    helper::match_action(ch, value, spn);
                    sstate = 130;
                    break;
                case L'{':
                    helper::match_action(ch, value, spn);
                    sstate = 42;
                    break;
                case L'}':
                    helper::match_action(ch, value, spn);
                    sstate = 43;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'f') {
                        helper::match_action(ch, value, spn);
                        sstate = 23;
                    }
                    else if (ch >= L'j' && ch <= L'o') {
                        helper::match_action(ch, value, spn);
                        sstate = 23;
                    }
                    else if (ch >= L'u' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 23;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 23;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_count++;
                break;
            case 130:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'o':
                    helper::match_action(ch, value, spn);
                    sstate = 131;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'n') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'p' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 130;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 2:
                switch (ch) {
                case L'\t':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L'\n':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L'\v':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L'\f':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L'\r':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L'\x0020':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                default:
                    stm.unget();
                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    break;
                }
                rewind_state = 2;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 132:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'e':
                    helper::match_action(ch, value, spn);
                    sstate = 133;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'd') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'f' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 132;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 4:
                switch (ch) {
                case L'\t':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L'\n':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L'\v':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L'\f':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L'\r':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                case L'\x0020':
                    helper::match_action(ch, value, spn);
                    sstate = 4;
                    break;
                default:
                    stm.unget();
                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    break;
                }
                rewind_state = 4;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 131:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'k':
                    helper::match_action(ch, value, spn);
                    sstate = 132;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'j') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'l' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 131;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 136:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'a':
                    helper::match_action(ch, value, spn);
                    sstate = 137;
                    break;
                default:
                    if (ch >= L'b' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 136;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 135:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'c':
                    helper::match_action(ch, value, spn);
                    sstate = 141;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'b') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'd' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 135;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 7:
                switch (ch) {
                case L'\n':
                    helper::match_action(ch, value, spn);
                    sstate = 5;
                    break;
                default:
                    if (ch >= L'\x0000' && ch <= L'\t') {
                        helper::match_action(ch, value, spn);
                        sstate = 10;
                    }
                    else if (ch >= L'\v' && ch <= L'\xffff') {
                        helper::match_action(ch, value, spn);
                        sstate = 10;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_count++;
                break;
            case 138:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'e':
                    helper::match_action(ch, value, spn);
                    sstate = 139;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'd') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'f' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 138;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 10:
                switch (ch) {
                case L'\n':
                    helper::match_action(ch, value, spn);
                    sstate = 5;
                    break;
                default:
                    if (ch >= L'\x0000' && ch <= L'\t') {
                        helper::match_action(ch, value, spn);
                        sstate = 10;
                    }
                    else if (ch >= L'\v' && ch <= L'\xffff') {
                        helper::match_action(ch, value, spn);
                        sstate = 10;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_count++;
                break;
            case 137:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'r':
                    helper::match_action(ch, value, spn);
                    sstate = 138;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'q') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L's' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 137;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 134:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 134;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 140:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 140;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 143:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'o':
                    helper::match_action(ch, value, spn);
                    sstate = 144;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'n') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'p' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 143;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 142:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'i':
                    helper::match_action(ch, value, spn);
                    sstate = 143;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'h') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'j' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 142;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 22:
                switch (ch) {
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 23;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 23;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 23;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_count++;
                break;
            case 23:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 23;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 25:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
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
            case 74:
                switch (ch) {
                case L'"':
                    helper::match_action(ch, value, spn);
                    sstate = 72;
                    break;
                case L'.':
                    helper::match_action(ch, value, spn);
                    sstate = 171;
                    break;
                default:
                    if (ch >= L'\x0000' && ch <= L'!') {
                        helper::match_action(ch, value, spn);
                        sstate = 76;
                    }
                    else if (ch >= L'#' && ch <= L'-') {
                        helper::match_action(ch, value, spn);
                        sstate = 76;
                    }
                    else if (ch >= L'/' && ch <= L'\xffff') {
                        helper::match_action(ch, value, spn);
                        sstate = 76;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_count++;
                break;
            case 76:
                switch (ch) {
                case L'"':
                    helper::match_action(ch, value, spn);
                    sstate = 72;
                    break;
                case L'.':
                    helper::match_action(ch, value, spn);
                    sstate = 171;
                    break;
                default:
                    if (ch >= L'\x0000' && ch <= L'!') {
                        helper::match_action(ch, value, spn);
                        sstate = 76;
                    }
                    else if (ch >= L'#' && ch <= L'-') {
                        helper::match_action(ch, value, spn);
                        sstate = 76;
                    }
                    else if (ch >= L'/' && ch <= L'\xffff') {
                        helper::match_action(ch, value, spn);
                        sstate = 76;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_count++;
                break;
            case 77:
                switch (ch) {
                case L'*':
                    helper::match_action(ch, value, spn);
                    sstate = 172;
                    break;
                default:
                    if (ch >= L'\x0000' && ch <= L')') {
                        helper::match_action(ch, value, spn);
                        sstate = 81;
                    }
                    else if (ch >= L'+' && ch <= L'\xffff') {
                        helper::match_action(ch, value, spn);
                        sstate = 81;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_count++;
                break;
            case 81:
                if (ch >= L'\x0000' && ch <= L')') {
                    helper::match_action(ch, value, spn);
                    sstate = 83;
                }
                else if (ch >= L'+' && ch <= L'\xffff') {
                    helper::match_action(ch, value, spn);
                    sstate = 83;
                }
                else {
                    stm.unget();
                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                }
                rewind_state = 81;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 83:
                if (ch >= L'\x0000' && ch <= L')') {
                    helper::match_action(ch, value, spn);
                    sstate = 83;
                }
                else if (ch >= L'+' && ch <= L'\xffff') {
                    helper::match_action(ch, value, spn);
                    sstate = 83;
                }
                else {
                    stm.unget();
                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                }
                rewind_state = 83;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 85:
                switch (ch) {
                case L'\x0027':
                    helper::match_action(ch, value, spn);
                    sstate = 110;
                    break;
                case L'(':
                    helper::match_action(ch, value, spn);
                    sstate = 111;
                    break;
                case L')':
                    helper::match_action(ch, value, spn);
                    sstate = 112;
                    break;
                case L'*':
                    helper::match_action(ch, value, spn);
                    sstate = 113;
                    break;
                case L'+':
                    helper::match_action(ch, value, spn);
                    sstate = 114;
                    break;
                case L',':
                    helper::match_action(ch, value, spn);
                    sstate = 109;
                    break;
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 115;
                    break;
                case L'.':
                    helper::match_action(ch, value, spn);
                    sstate = 116;
                    break;
                case L'?':
                    helper::match_action(ch, value, spn);
                    sstate = 117;
                    break;
                case L'[':
                    helper::match_action(ch, value, spn);
                    sstate = 118;
                    break;
                case L'\x005c':
                    helper::match_action(ch, value, spn);
                    sstate = 119;
                    break;
                case L']':
                    helper::match_action(ch, value, spn);
                    sstate = 120;
                    break;
                case L'{':
                    helper::match_action(ch, value, spn);
                    sstate = 121;
                    break;
                case L'|':
                    helper::match_action(ch, value, spn);
                    sstate = 122;
                    break;
                case L'}':
                    helper::match_action(ch, value, spn);
                    sstate = 123;
                    break;
                default:
                    if (ch >= L'\x0000' && ch <= L'&') {
                        helper::match_action(ch, value, spn);
                        sstate = 109;
                    }
                    else if (ch >= L'/' && ch <= L'>') {
                        helper::match_action(ch, value, spn);
                        sstate = 109;
                    }
                    else if (ch >= L'@' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 109;
                    }
                    else if (ch >= L'^' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 109;
                    }
                    else if (ch >= L'~' && ch <= L'\xffff') {
                        helper::match_action(ch, value, spn);
                        sstate = 109;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_count++;
                break;
            case 102:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 104;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 104;
                    break;
                case L'}':
                    helper::match_action(ch, value, spn);
                    sstate = 99;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 104;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 104;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 104;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_count++;
                break;
            case 104:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 104;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 104;
                    break;
                case L'}':
                    helper::match_action(ch, value, spn);
                    sstate = 99;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 104;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 104;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 104;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_count++;
                break;
            case 109:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 109;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 118:
                switch (ch) {
                case L'^':
                    helper::match_action(ch, value, spn);
                    sstate = 93;
                    break;
                default:
                    stm.unget();
                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    break;
                }
                rewind_state = 118;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 119:
                if (ch >= L'\x0000' && ch <= L'\xffff') {
                    helper::match_action(ch, value, spn);
                    sstate = 107;
                }
                else {
                    stm.unget();
                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                }
                rewind_state = 119;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 121:
                switch (ch) {
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 102;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 102;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 102;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 121;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 123:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 123;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 122:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 122;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 99:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 99;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 120:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 120;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 107:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 107;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 93:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 93;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 117:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 117;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 116:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 116;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 115:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 115;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 114:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 114;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 113:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 113;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 112:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 112;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 111:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 111;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 110:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 110;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 124:
                switch (ch) {
                case L'*':
                    helper::match_action(ch, value, spn);
                    sstate = 11;
                    break;
                case L'/':
                    helper::match_action(ch, value, spn);
                    sstate = 7;
                    break;
                default:
                    stm.unget();
                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    break;
                }
                rewind_count++;
                break;
            case 125:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'o':
                    helper::match_action(ch, value, spn);
                    sstate = 168;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'n') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'p' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 125;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 126:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'm':
                    helper::match_action(ch, value, spn);
                    sstate = 157;
                    break;
                case L'n':
                    helper::match_action(ch, value, spn);
                    sstate = 158;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'l') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'o' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 126;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 127:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'a':
                    helper::match_action(ch, value, spn);
                    sstate = 151;
                    break;
                default:
                    if (ch >= L'b' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 127;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 129:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'e':
                    helper::match_action(ch, value, spn);
                    sstate = 135;
                    break;
                case L'h':
                    helper::match_action(ch, value, spn);
                    sstate = 136;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'd') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'f' && ch <= L'g') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'i' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 129;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 43:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 43;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 42:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 42;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 133:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'n':
                    helper::match_action(ch, value, spn);
                    sstate = 134;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'm') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'o' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 133;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 139:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'd':
                    helper::match_action(ch, value, spn);
                    sstate = 140;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'c') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'e' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 139;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 141:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L't':
                    helper::match_action(ch, value, spn);
                    sstate = 142;
                    break;
                default:
                    if (ch >= L'a' && ch <= L's') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'u' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 141;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 144:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'n':
                    helper::match_action(ch, value, spn);
                    sstate = 145;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'm') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'o' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 144;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 145:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 145;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 146:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L't':
                    helper::match_action(ch, value, spn);
                    sstate = 147;
                    break;
                default:
                    if (ch >= L'a' && ch <= L's') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'u' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 146;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 147:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'u':
                    helper::match_action(ch, value, spn);
                    sstate = 148;
                    break;
                default:
                    if (ch >= L'a' && ch <= L't') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'v' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 147;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 148:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'r':
                    helper::match_action(ch, value, spn);
                    sstate = 149;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'q') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L's' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 148;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 149:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'n':
                    helper::match_action(ch, value, spn);
                    sstate = 150;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'm') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'o' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 149;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 150:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 150;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 151:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L't':
                    helper::match_action(ch, value, spn);
                    sstate = 152;
                    break;
                default:
                    if (ch >= L'a' && ch <= L's') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'u' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 151;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 152:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L't':
                    helper::match_action(ch, value, spn);
                    sstate = 153;
                    break;
                default:
                    if (ch >= L'a' && ch <= L's') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'u' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 152;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 153:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'e':
                    helper::match_action(ch, value, spn);
                    sstate = 154;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'd') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'f' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 153;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 154:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'r':
                    helper::match_action(ch, value, spn);
                    sstate = 155;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'q') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L's' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 154;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 155:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'n':
                    helper::match_action(ch, value, spn);
                    sstate = 156;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'm') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'o' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 155;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 156:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 156;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 157:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'p':
                    helper::match_action(ch, value, spn);
                    sstate = 164;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'o') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'q' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 157;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 158:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'c':
                    helper::match_action(ch, value, spn);
                    sstate = 159;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'b') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'd' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 158;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 159:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'l':
                    helper::match_action(ch, value, spn);
                    sstate = 160;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'k') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'm' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 159;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 160:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'u':
                    helper::match_action(ch, value, spn);
                    sstate = 161;
                    break;
                default:
                    if (ch >= L'a' && ch <= L't') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'v' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 160;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 161:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'd':
                    helper::match_action(ch, value, spn);
                    sstate = 162;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'c') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'e' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 161;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 162:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'e':
                    helper::match_action(ch, value, spn);
                    sstate = 163;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'd') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'f' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 162;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 163:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 163;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 164:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'o':
                    helper::match_action(ch, value, spn);
                    sstate = 165;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'n') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'p' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 164;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 165:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'r':
                    helper::match_action(ch, value, spn);
                    sstate = 166;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'q') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L's' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 165;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 166:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L't':
                    helper::match_action(ch, value, spn);
                    sstate = 167;
                    break;
                default:
                    if (ch >= L'a' && ch <= L's') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'u' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 166;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 167:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 167;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 168:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L't':
                    helper::match_action(ch, value, spn);
                    sstate = 169;
                    break;
                default:
                    if (ch >= L'a' && ch <= L's') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'u' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 168;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 169:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'o':
                    helper::match_action(ch, value, spn);
                    sstate = 170;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'n') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'p' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 169;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 170:
                switch (ch) {
                case L'-':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                case L'_':
                    helper::match_action(ch, value, spn);
                    sstate = 25;
                    break;
                default:
                    if (ch >= L'a' && ch <= L'z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'A' && ch <= L'Z') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else if (ch >= L'0' && ch <= L'9') {
                        helper::match_action(ch, value, spn);
                        sstate = 25;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_state = 170;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 26:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 26;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 28:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 28;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 5:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 5;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 11:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 11;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 27:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 27;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 171:
                switch (ch) {
                case L'"':
                    helper::match_action(ch, value, spn);
                    sstate = 72;
                    break;
                case L'.':
                    helper::match_action(ch, value, spn);
                    sstate = 171;
                    break;
                default:
                    if (ch >= L'\x0000' && ch <= L'!') {
                        helper::match_action(ch, value, spn);
                        sstate = 76;
                    }
                    else if (ch >= L'#' && ch <= L'-') {
                        helper::match_action(ch, value, spn);
                        sstate = 76;
                    }
                    else if (ch >= L'/' && ch <= L'\xffff') {
                        helper::match_action(ch, value, spn);
                        sstate = 76;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_count++;
                break;
            case 72:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 72;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 172:
                switch (ch) {
                case L'/':
                    helper::match_action(ch, value, spn);
                    sstate = 78;
                    break;
                default:
                    if (ch >= L'\x0000' && ch <= L'.') {
                        helper::match_action(ch, value, spn);
                        sstate = 80;
                    }
                    else if (ch >= L'0' && ch <= L'\xffff') {
                        helper::match_action(ch, value, spn);
                        sstate = 80;
                    }
                    else {
                        stm.unget();
                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                    }
                    break;
                }
                rewind_count++;
                break;
            case 80:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 80;
                rewind_count = 0;
                rewind_position = spn.end;
                break;
            case 78:
                stm.unget();
                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);
                rewind_state = 78;
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