#pragma once

#include <ostream>
#include <unordered_map>
#include <vector>
#include "model.h"
#include "log.h"
#include "nfa_builder.h"

namespace davelexer
{
    struct graphviz {
        static inline auto write_transition(std::wostream &os, const fa_transition &transition) -> std::wostream& {
            os << L"\"" << transition.from() << L"\"->\"" << transition.to() << L"\" [label=\"";
            if (transition.epsilon()) {
                os << L'.';
            }
            else if (transition.first() == 0 && transition.last() == WCHAR_MAX) {
                os << L"<any>";
            }
            else if (transition.first() == transition.last()) {
                wchar_friendly(transition.first(), os);
            }
            else {
                wchar_friendly(transition.first(), os) << L'-';
                wchar_friendly(transition.last(), os);
                
            }
            return os << L"\"]";
        }

        static inline auto write_graph(std::wostream &os, const std::vector<fa_transition> &transitions, const std::unordered_map<size_t, state_yield> &state_yields) -> std::wostream& {
            os << L"digraph fa {" << std::endl;
            for (auto &sy : state_yields) {
                os << L"  \"" << (int)sy.first << L"\" [color=blue,label=\"" << (int)sy.first << L"\\n" << *sy.second.token;
                if (sy.second.goto_section != nullptr) {
                    os << L"\\ng " << *sy.second.goto_section << L" (" << (int)sy.second.goto_section_start << L')';
                }
                if (sy.second.pop) {
                    os << L"\\npop";
                }
                os << L"\"]" << std::endl;
            }
            for (auto &t : transitions) {
                os << L"  ";
                write_transition(os, t);
                os << std::endl;
            }
            os << L'}' << std::endl;
            return os;
        }
        static inline auto write_graph(std::wostream &os, const std::unordered_map<size_t, std::vector<fa_transition>> &map, const std::unordered_map<size_t, state_yield> &state_yields) -> std::wostream& {
            os << L"digraph fa {" << std::endl;
            for (auto &sy : state_yields) {
                os << L"  \"" << (int)sy.first << L"\" [color=blue,label=\"" << (int)sy.first << L"\\n" << *sy.second.token;
                if (sy.second.goto_section != nullptr) {
                    os << L"\\ng " << *sy.second.goto_section << L" (" << (int)sy.second.goto_section_start << L')';
                }
                if (sy.second.pop) {
                    os << L"\\npop";
                }
                os << L"\"]" << std::endl;
            }
            for (auto &s : map) {
                for (auto &t : s.second) {
                    os << L"  ";
                    write_transition(os, t);
                    os << std::endl;
                }
            }
            os << L'}' << std::endl;
            return os;
        }
    };
}