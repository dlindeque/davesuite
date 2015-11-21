#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "nfa.h"

namespace davelexer
{
    class dfa {
    public:
    private:
        std::vector<std::vector<dfa_transition>> _tmap;

        dfa()
        {}
    public:
        dfa(const dfa &) = delete;
        dfa(dfa &&c)
            : _tmap(std::move(c._tmap))
        {}

        // the compile will destroy the nfa
        static auto try_compile(nfa &&nfa, std::wostream &errors, bool &ok, const std::function<size_t(size_t, size_t)> &conflict_resolver)->dfa;

        friend auto operator << (std::wostream &os, const dfa &dfa) -> std::wostream& {
            os << L"digraph dfa{" << std::endl;
            for (auto &s : dfa._tmap) {
                for (auto &t : s) {
                    os << L"  \"" << t.from() << L"\"->\"" << t.to() << L"\" [label=\"";
                    if (t.guard().first() == 0 && t.guard().last() == WCHAR_MAX) {
                        os << L"<any>";
                    }
                    else if (t.guard().first() == t.guard().last() && t.guard().first() != 0) {
                        os << t.guard().first();
                    }
                    else if (t.guard().first() == t.guard().last() && t.guard().first() == 0) {
                        os << L"<eod>";
                    }
                    else if (t.guard().first() == 0) {
                        os << L"<s>-" << t.guard().last();
                    }
                    else if (t.guard().last() == WCHAR_MAX) {
                        os << t.guard().first() << L"-<e>";
                    }
                    else {
                        os << t.guard().first() << L"-" << t.guard().last();
                    }
                    if (t.yield() != 0) {
                        os << L'(' << (int)t.yield() << L')';
                    }
                    os << L"\"]" << std::endl;
                }
            }
            os << L"}" << std::endl;

            return os;
        }
    };
}