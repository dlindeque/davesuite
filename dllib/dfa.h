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
        std::vector<std::vector<fa_transition>> _tmap;

        dfa()
        {}
    public:
        dfa(const dfa &) = delete;
        dfa(dfa &&c)
            : _tmap(std::move(c._tmap))
        {}

        // the compile will destroy the nfa
        //static auto try_compile(nfa &&nfa, std::wostream &errors, bool &ok, const std::function<size_t(size_t, size_t)> &conflict_resolver)->dfa;
    };
}