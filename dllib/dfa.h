#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "nfa_builder.h"

namespace davelexer
{
    class dfa {
    public:
    private:
        std::vector<std::vector<fa_transition>> _tmap;
        std::map<size_t, yield_details> _token_yields;
        dfa(std::map<size_t, yield_details> &&token_yields)
            : _token_yields(std::move(token_yields))
        {}
    public:
        dfa(const dfa &) = delete;
        dfa(dfa &&c)
            : _tmap(std::move(c._tmap)), _token_yields(std::move(c._token_yields))
        {}

        inline auto token_yields() const -> const std::map<size_t, yield_details>& { return _token_yields; }
        inline auto tmap() const -> const std::vector<std::vector<fa_transition>>& {
            return _tmap;
        }

        // The compile will destroy the nfa
        static auto try_compile(nfa_builder &&nfa, const std::function<size_t(size_t, size_t)> &conflict_resolver)->dfa;
    };
}