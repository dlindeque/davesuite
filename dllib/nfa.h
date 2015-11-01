#pragma once

#include <string>
#include <memory>
#include <ostream>
#include <istream>
#include <map>
#include "dfa.h"
#include "re_parser.h"
#include "lexer.h"

namespace davelexer
{
    class nfa {
    private:
        std::vector<nfa_transition> _transition_table;
        std::map<std::wstring, unsigned int> _section_init_states;
    public:
        nfa()
        {}
        nfa(const nfa &) = delete;
        nfa(nfa &&c)
            : _transition_table(std::move(c._transition_table)), _section_init_states(std::move(c._section_init_states))
        {}

        auto try_compile(bool &good, std::wostream &errors)->dfa;

        auto try_add(const std::wstring &section, const std::wstring &token_name, nfa_action action, container *container, const token &re, logger *logger)->bool;
    };
}