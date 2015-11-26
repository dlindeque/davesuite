#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <unordered_map>

#include "nfa_builder.h"

namespace davelexer
{
    class dfa {
    public:
    private:
        std::unordered_map<size_t, std::vector<fa_transition>> _tmap;
        std::unordered_map<size_t, state_yield> _state_yields;
        dfa() {}
    public:
        dfa(const dfa &) = delete;
        dfa(dfa &&c)
            : _tmap(std::move(c._tmap)), _state_yields(std::move(c._state_yields))
        {}

        inline auto tmap() const -> const std::unordered_map<size_t, std::vector<fa_transition>>& {
            return _tmap;
        }

        inline auto state_yields() const -> const std::unordered_map<size_t, state_yield>& { return _state_yields; }

        // The compile will destroy the nfa
        static auto try_compile(nfa_builder &&nfa)->dfa;
    };
}