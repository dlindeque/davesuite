#include "stdafx.h"
#include "lexer.h"



namespace davelexer
{
    auto lexer::operator()(std::vector<size_t> &statestack, std::wistream &stm, std::shared_ptr<std::wstring> &token, std::wstring &value, bool &is_eod, span &spn) -> bool
    {
        spn.begin = spn.end;
        auto sstate = statestack.back();
        value.clear();
        const state_yield *rewind_yield = nullptr;
        int rewind_count = 0;
        position rewind_position;
        is_eod = false;
        while (true) {
            bool transition_found = false;
            if (!stm.eof()) {
                // match ch
                auto ch = stm.get();
                if (ch != std::char_traits<wchar_t>::eof()) {
                    auto f = _dfa.tmap().find(sstate);
                    assert(f != _dfa.tmap().end());
                    for (auto &t : f->second) {
                        if (t.first() <= ch && t.last() >= ch) {
                            // found the transition
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
                            transition_found = true;
                            sstate = t.to();
                            auto f = _dfa.state_yields().find(t.to());
                            if (f != _dfa.state_yields().end()) {
                                // This is a final state - capture it as a rewind state
                                rewind_yield = &f->second;
                                rewind_count = 0;
                                rewind_position = spn.end;
                            }
                            else {
                                rewind_count++;
                            }
                            break;
                        }
                    }
                }
                else {
                    is_eod = true;
                }
            }
            else {
                is_eod = true;
            }
            if (!transition_found) {
                // No transition found - if we're on a final state, then return the token for this final state
                if (!is_eod) {
                    stm.unget(); // Put back the last digit, since we're not consuming it.
                }
                auto f = _dfa.state_yields().find(sstate);
                if (f == _dfa.state_yields().end()) {
                    // Not a final state - seek back to previous yield state
                    if (rewind_yield == nullptr) {
                        // Cannot process this text
                        return false;
                    }
                    assert(rewind_yield != nullptr);
                    for (int i = 0; i < rewind_count; i++) {
                        stm.unget();
                    }
                    spn.end = rewind_position;
                    value.resize(value.size() - rewind_count);
                    if (rewind_yield->goto_section != nullptr) {
                        statestack.push_back(rewind_yield->goto_section_start);
                    }
                    else if (rewind_yield->pop) {
                        assert(!statestack.empty());
                        statestack.pop_back();
                        assert(!statestack.empty());
                    }

                    token = rewind_yield->token;
                    return true;
                }
                else {
                    // Final state
                    if (f->second.goto_section != nullptr) {
                        // push a new state
                        statestack.push_back(f->second.goto_section_start);
                    }
                    else if (f->second.pop) {
                        // pop the state
                        assert(!statestack.empty());
                        statestack.pop_back();
                        assert(!statestack.empty());
                    }

                    token = f->second.token;
                    return true;
                }
            }
        }
    }
}