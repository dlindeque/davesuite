#pragma once

#include <string>
#include <memory>
#include <ostream>
#include <istream>
#include <functional>
#include "dfa.h"

namespace davelexer
{
    class nfa {
    private:
        
    private:
        std::vector<row> _transition_table;
        long _next_state;
    public:
        nfa()
            : _next_state(1)
        {}
        nfa(const nfa &) = delete;
        nfa(nfa &&c)
            : _transition_table(std::move(c._transition_table)), _next_state(c._next_state)
        {}

        auto try_compile(bool &good, std::wostream &errors)->dfa;

        auto try_add(const std::wstring &token, std::wistream &re, std::wostream &errors)->bool;
    };
}