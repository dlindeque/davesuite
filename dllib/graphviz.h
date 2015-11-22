#pragma once

#include <ostream>
#include <map>
#include <vector>
#include "model.h"
#include "log.h"
#include "nfa_builder.h"

namespace davelexer
{
    struct graphviz {
        static inline auto write_transition(std::wostream &os, const std::map<size_t, yield_details> &yield_details, const fa_transition &transition) -> std::wostream& {
            os << L"\"" << transition.from() << L"\"->\"" << transition.to() << L"\" [label=\"";
            if (transition.epsilon()) {
                os << L'.';
            }
            else if (transition.eod()) {
                os << L"<eod>";
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
            if (transition.yield() != 0) {
                auto f = yield_details.find(transition.yield());
                if (f == yield_details.end()) {
                    os << L"(Yield " << (int)transition.yield() << " not found)";
                }
                else {
                    os << L'(' << f->second.token;
                    if (f->second.goto_state != 0) {
                        os << L" g " << (int)f->second.goto_state;
                    }
                    if (f->second.pop) {
                        os << L" p";
                    }
                    os << L')';
                }
            }
            return os << L"\"]";
        }

        static inline auto write_graph(std::wostream &os, const std::map<size_t, yield_details> &yield_details, const std::vector<fa_transition> &transitions) -> std::wostream& {
            os << L"digraph fa {" << std::endl;
            for (auto &t : transitions) {
                os << L"  ";
                write_transition(os, yield_details, t);
                os << std::endl;
            }
            os << L'}' << std::endl;
            return os;
        }
        static inline auto write_graph(std::wostream &os, const std::map<size_t, yield_details> &yield_details, const std::vector<std::vector<fa_transition>> &map) -> std::wostream& {
            os << L"digraph fa {" << std::endl;
            for (auto &transitions : map) {
                for (auto &t : transitions) {
                    os << L"  ";
                    write_transition(os, yield_details, t);
                    os << std::endl;
                }
            }
            os << L'}' << std::endl;
            return os;
        }
    };
}