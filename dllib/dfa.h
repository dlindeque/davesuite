#pragma once

#include <memory>
#include <vector>

#include "nfa.h"

namespace davelexer
{
    class dfa {
    public:
    private:
        std::map<size_t, std::vector<nfa_transition>> _tmap;

        dfa()
        {}
    public:
        dfa(const dfa &) = delete;
        dfa(dfa &&c)
            : _tmap(std::move(c._tmap))
        {}

        // the compile will destroy the nfa
        static auto try_compile(nfa &&nfa, std::wostream &errors, bool &ok)->dfa;

        friend auto operator << (std::wostream &os, const dfa &dfa) -> std::wostream& {
            os << L"digraph dfa{" << std::endl;
            for (auto &s : dfa._tmap) {
                for (auto &t : s.second) {
                    os << L"  \"" << t.from() << L"\"->\"" << t.to() << L"\" [label=\"";
                    if (t.guard().epsilon()) {
                        os << L".";
                    }
                    else {
                        if (t.guard().first() == 0 && t.guard().last() == WCHAR_MAX) {
                            os << L"<any>";
                        }
                        else if (t.guard().first() == t.guard().last() && t.guard().first() != 0) {
                            os << t.guard().first();
                        }
                        else if (t.guard().first() == t.guard().last() && t.guard().first() == 0) {
                            os << L"<eod>";
                        }
                        else {
                            os << t.guard().first() << L"-" << t.guard().last();
                        }
                    }
                    std::set<const std::wstring*> tokens;
                    for (auto &a : t.actions()) {
                        tokens.emplace(a.reduce_token());
                    }
                    for (auto &tkn : tokens) {
                        bool got_actions = false;
                        for (auto &a : t.actions()) {
                            if (a.reduce_token() == tkn) {
                                got_actions |= a.pop() || a.push() || a.reduce() || !a.output_matched();
                                if (got_actions) break;
                            }
                        }
                        if (got_actions) {
                            os << L" '" << *tkn << L"'(";
                            for (auto &a : t.actions()) {
                                if (a.reduce_token() == tkn) {
                                    if (a.pop()) {
                                        os << L" p";
                                    }
                                    else if (a.push()) {
                                        os << L" g " << a.goto_state();
                                    }
                                    else if (a.reduce()) {
                                        os << L" r";
                                    }
                                    if (!a.output_matched()) {
                                        os << L" o '" << a.output_alternate() << "'";
                                    }
                                }
                            }
                            os << L')';
                        }
                    }
                    os << L"\"]" << std::endl;
                }
            }
            os << L"}" << std::endl;

            return os;
        }
    };
}