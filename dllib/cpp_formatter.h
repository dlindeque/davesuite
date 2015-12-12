#pragma once

#include <ostream>
#include <unordered_map>
#include <iomanip>
#include "dfa.h"

namespace davelexer
{
    class cpp_formatter {
    public:
        static inline auto cpp_identifier(const std::wstring &value) -> std::wstring {
            if (value == L"return") return L"return_";
            if (value == L"goto") return L"goto_";
            auto s = value;
            for (auto &c : s) {
                if (c <= L'z' && c >= L'a') continue;
                if (c <= L'Z' && c >= L'A') continue;
                if (c == L'_') continue;
                c = L'_';
            }
            return s;
        }
        static inline auto cpp_char(wchar_t ch) -> std::wstring {
            switch (ch) {
            case L'\n':
                return L"\\n";
            case L'\r':
                return L"\\r";
            case L'\v':
                return L"\\v";
            case L'\t':
                return L"\\t";
            case L'\f':
                return L"\\f";
            case L'\b':
                return L"\\b";
            default:
                if (true) {
                    std::wstringstream s;
                    switch (ch) {
                    case L'!':
                    case L'"':
                    case L'£':
                    case L'$':
                    case L'%':
                    case L'^':
                    case L'&':
                    case L'*':
                    case L'(':
                    case L')':
                    case L'_':
                    case L'-':
                    case L'+':
                    case L'=':
                    case L'{':
                    case L'}':
                    case L'[':
                    case L']':
                    case L':':
                    case L';':
                    case L'@':
                    case L'~':
                    case L'#':
                    case L'<':
                    case L'>':
                    case L',':
                    case L'.':
                    case L'?':
                    case L'/':
                    case L'|':
                    case L' ':
                        s << ch;
                        break;
                    default:
                        if ((ch >= L'a' && ch <= L'z')
                            || (ch >= L'A' && ch <= L'Z')
                            || (ch >= L'0' && ch <= L'9')) {
                            s << ch;
                        }
                        else {
                            auto sf = s.flags();
                            s << L"\\x" << std::hex << std::setfill(L'0') << std::setw(4) << (int)ch;
                            s.flags(sf);
                        }
                    }
                    return s.str();
                }
            }
        }
    public:
        static auto write_lexer_body(const std::wstring &token_enum_name, const dfa &dfa, std::wostream &os) -> void {
            struct final_state {
                std::vector<fa_transition> transitions;
                state_yield yield;
            };
            std::map<size_t, final_state> final_states;
            std::map<size_t, std::vector<fa_transition>> non_final_states;
            for (auto &s : dfa.tmap()) {
                auto f = dfa.state_yields().find(s.first);
                if (f == dfa.state_yields().end()) {
                    non_final_states.emplace(s.first, s.second);
                }
                else {
                    final_states.emplace(s.first, final_state{ s.second, f->second });
                }
            }

            os << L"        struct helper {" << std::endl;
            os << L"            static inline auto no_match_action(size_t sstate, std::vector<size_t> &statestack, std::wistream &stm, testcls_token &token, std::wstring &value, bool &is_eod, davecommon::span &spn, const size_t &rewind_state, int rewind_count, const davecommon::position &rewind_position) -> bool {" << std::endl;
            os << L"                while (true) {" << std::endl;
            os << L"                    switch (sstate) {" << std::endl;
            os << L"                    // Non final states" << std::endl;
            for (auto &s : non_final_states) {
                os << L"                    case " << (int)s.first << L':' << std::endl;
            }
            os << L"                        if (rewind_state == 0) {" << std::endl;
            os << L"                            return false; // Cannot rewind" << std::endl;
            os << L"                        }" << std::endl;
            os << L"                        else {" << std::endl;
            os << L"                            for (int i = 0; i < rewind_count; i++) {" << std::endl;
            os << L"                                stm.unget();" << std::endl;
            os << L"                            }" << std::endl;
            os << L"                            spn.end = rewind_position;" << std::endl;
            os << L"                            value.resize(value.size() - rewind_count);" << std::endl;
            os << L"                            sstate = rewind_state;" << std::endl;
            os << L"                        }" << std::endl;
            os << L"                        break;" << std::endl;
            os << L"                    // Final states" << std::endl;
            for (auto &s : final_states) {
                os << L"                    case " << (int)s.first << L':' << std::endl;
                if (s.second.yield.goto_section != nullptr) {
                    os << L"                        statestack.push_back(" << (int)s.second.yield.goto_section_start << L");" << std::endl;
                }
                if (s.second.yield.pop) {
                    os << L"                        statestack.pop_back();" << std::endl;
                    os << L"                        assert(!statestack.empty());" << std::endl;
                }
                os << L"                        token = " << token_enum_name << "::" << cpp_identifier(*s.second.yield.token) << L';' << std::endl;
                os << L"                        return true;" << std::endl;
            }
            os << L"                    default:" << std::endl;
            os << L"                        assert(false); // Invalid state" << std::endl;
            os << L"                        return false;" << std::endl;
            os << L"                    }" << std::endl;
            os << L"                }" << std::endl;
            os << L"            }" << std::endl;
            os << L"            static inline auto match_action(wchar_t ch, std::wstring &value, davecommon::span &spn) -> void {" << std::endl;
            os << L"                value += ch;" << std::endl;
            os << L"                if (ch == L'\\n') {" << std::endl;
            os << L"                    spn.end.line++;" << std::endl;
            os << L"                    spn.end.column = 1;" << std::endl;
            os << L"                }" << std::endl;
            os << L"                else if (ch == L'\\r') {" << std::endl;
            os << L"                    spn.end.column = 1;" << std::endl;
            os << L"                }" << std::endl;
            os << L"                else {" << std::endl;
            os << L"                    spn.end.column++;" << std::endl;
            os << L"                }" << std::endl;
            os << L"            }" << std::endl;
            os << L"        };" << std::endl;
            os << L"        spn.begin = spn.end;" << std::endl;
            os << L"        auto sstate = statestack.back();" << std::endl;
            os << L"        value.clear();" << std::endl;
            os << L"        is_eod = false;" << std::endl;
            os << L"        size_t rewind_state = 0;" << std::endl;
            os << L"        int rewind_count = 0;" << std::endl;
            os << L"        davecommon::position rewind_position;" << std::endl;
            os << L"        while (true) {" << std::endl;
            os << L"            wchar_t ch;" << std::endl;
            os << L"            if (!stm.get(ch)) {" << std::endl;
            os << L"                is_eod = true;" << std::endl;
            os << L"                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);" << std::endl;
            os << L"            }" << std::endl;
            os << L"            switch (sstate) {" << std::endl;
            for (auto &s : dfa.tmap()) {
                os << L"            case " << (int)s.first << L":" << std::endl;
                std::map<wchar_t, const fa_transition*> switch_guards;
                std::vector<const fa_transition*> if_guards;
                for (auto &t : s.second) {
                    if (t.first() == t.last()) {
                        switch_guards.emplace(t.first(), &t);
                    }
                    else {
                        if_guards.push_back(&t);
                    }
                }
                if (!switch_guards.empty()) {
                    os << L"                switch (ch) {" << std::endl;
                    for (auto &sg : switch_guards) {
                        os << L"                case L'" << cpp_char(sg.first) << L"':" << std::endl;
                        os << L"                    helper::match_action(ch, value, spn);" << std::endl;
                        os << L"                    sstate = " << (int)sg.second->to() << L';' << std::endl;
                        os << L"                    break;" << std::endl;
                    }
                    os << L"                default:" << std::endl;
                    if (if_guards.empty()) {
                        os << L"                    stm.unget();" << std::endl;
                        os << L"                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);" << std::endl;
                    }
                    else {
                        bool first = true;
                        for (auto &ig : if_guards) {
                            if (first) {
                                os << L"                    if (ch >= L'" << cpp_char(ig->first()) << "' && ch <= L'" << cpp_char(ig->last()) << "') {" << std::endl;
                                first = false;
                            }
                            else {
                                os << L"                    else if (ch >= L'" << cpp_char(ig->first()) << "' && ch <= L'" << cpp_char(ig->last()) << "') {" << std::endl;
                            }
                            os << L"                        helper::match_action(ch, value, spn);" << std::endl;
                            os << L"                        sstate = " << (int)ig->to() << L';' << std::endl;
                            os << L"                    }" << std::endl;
                        }
                        os << L"                    else {" << std::endl;
                        os << L"                        stm.unget();" << std::endl;
                        os << L"                        return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);" << std::endl;
                        os << L"                    }" << std::endl;
                    }
                    os << L"                    break;" << std::endl;
                    os << L"                }" << std::endl;
                }
                else {
                    if (if_guards.empty()) {
                        os << L"                stm.unget();" << std::endl;
                        os << L"                return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);" << std::endl;
                    }
                    else {
                        bool first = true;
                        for (auto &ig : if_guards) {
                            if (first) {
                                os << L"                if (ch >= L'" << cpp_char(ig->first()) << "' && ch <= L'" << cpp_char(ig->last()) << "') {" << std::endl;
                                first = false;
                            }
                            else {
                                os << L"                else if (ch >= L'" << cpp_char(ig->first()) << "' && ch <= L'" << cpp_char(ig->last()) << "') {" << std::endl;
                            }
                            os << L"                    helper::match_action(ch, value, spn);" << std::endl;
                            os << L"                    sstate = " << (int)ig->to() << L';' << std::endl;
                            os << L"                }" << std::endl;
                        }
                        os << L"                else {" << std::endl;
                        os << L"                    stm.unget();" << std::endl;
                        os << L"                    return helper::no_match_action(sstate, statestack, stm, token, value, is_eod, spn, rewind_state, rewind_count, rewind_position);" << std::endl;
                        os << L"                }" << std::endl;
                    }
                }
                auto fs = dfa.state_yields().find(s.first);
                if (fs == dfa.state_yields().end()) {
                    os << L"                rewind_count++;" << std::endl;
                }
                else {
                    os << L"                rewind_state = " << (int)s.first << L";" << std::endl;
                    os << L"                rewind_count = 0;" << std::endl;
                    os << L"                rewind_position = spn.end;" << std::endl;
                }
                os << L"                break;" << std::endl;
            }
            os << L"            default:" << std::endl;
            os << L"                assert(false); // Invalid state" << std::endl;
            os << L"                break;" << std::endl;
            os << L"            }" << std::endl;
            os << L"        }" << std::endl;
        }
    };
}