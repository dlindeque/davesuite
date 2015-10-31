#pragma once

#include <memory>
#include <vector>

namespace davelexer
{
    class nfa;

    class dfa {
    public:
        struct row {
            int from;
            wchar_t match;
            int to;
            std::wstring output;
            std::wstring token;
        };
    private:
        std::vector<row> _transition_table;
        int _final_state;

        dfa(std::vector<row> &&transition_table, int final_state)
            : _transition_table(std::move(transition_table)), _final_state(final_state)
        { }
    public:
        dfa(const dfa &) = delete;
        dfa(dfa &&c)
            : _transition_table(std::move(c._transition_table)), _final_state(c._final_state)
        { }


        friend nfa;
    };
}