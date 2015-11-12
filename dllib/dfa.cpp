#include "stdafx.h"

#include <assert.h>

#include "nfa.h"
#include "dfa.h"
#include "re_lexer.h"
#include "..\common\offset_logger.h"

namespace davelexer
{

#ifdef _DEBUG
    auto assert_valid_nfa_1(const std::vector<nfa_transition> &transitions) -> void
    {
        // Ensure we don't have any recursive epsilon transitions with output
        std::set<size_t> states;
        for (auto &t : transitions) {
            states.emplace(t.from());
            for (auto &a : t.actions()) {
                assert(a.reduce_token() != nullptr);
            }
        }
        for (auto &s : states) {
        }
    }
#else
    inline auto assert_valid_nfa_1(const std::vector<nfa_transition>&) -> void {}
#endif

#ifdef _DEBUG
    auto assert_valid_nfa_2(const std::vector<nfa_transition> &transitions) -> void
    {
        // Ensure we don't have any epsilon transitions with actions
        for (auto &t : transitions) {
            assert(!t.guard().epsilon() || t.actions().empty());
        }
    }
#else
    inline auto assert_valid_nfa_2(const std::vector<nfa_transition>&) -> void {}
#endif

#ifdef _DEBUG
    auto assert_valid_nfa_3(const std::vector<nfa_transition> &transitions) -> void
    {
        // Ensure we don't have any epsilon transitions
        for (auto &t : transitions) {
            assert(!t.guard().epsilon());
        }
    }
#else
    inline auto assert_valid_nfa_3(const std::vector<nfa_transition>&) -> void {}
#endif

    auto dfa::try_compile(nfa &&nfa, std::wostream &errors, bool &ok) -> dfa
    {
        ok = true;

#pragma region Clear Epsilon Transitions Of Actions

        std::vector<size_t> unprocessed;
        unprocessed.reserve(nfa._transition_table.size());
        for (size_t i = 0; i < nfa._transition_table.size(); i++) {
            if (nfa._transition_table[i].guard().epsilon() && !nfa._transition_table[i].actions().empty()) {
                unprocessed.push_back(i);
            }
        }

        while (!unprocessed.empty()) {
            auto p = unprocessed.back();
            unprocessed.pop_back();

            std::vector<size_t> inbound, outbound, recursive;
            inbound.reserve(10);
            outbound.reserve(10);
            recursive.reserve(10);
            for (size_t i = 0; i < nfa._transition_table.size(); i++) {
                if (&nfa._transition_table[i] != &nfa._transition_table[p] && nfa._transition_table[i].to() == nfa._transition_table[p].to()) {
                    inbound.push_back(i); // include recursive transitions
                }
                if (nfa._transition_table[i].from() == nfa._transition_table[p].to()) {
                    if (nfa._transition_table[i].from() != nfa._transition_table[i].to())
                    {
                        outbound.push_back(i);
                    }
                    else {
                        recursive.push_back(i);
                    }
                }
            }

            // For each inbound transition, clone the state, copy the transitions and redirect the transition
            while (!inbound.empty()) {
                auto ip = inbound.back();
                inbound.pop_back();
                // Generate a new state
                size_t new_state = nfa._next_state++;
                // Change the transition to point to the new state
                nfa._transition_table[ip].to(new_state);
                // Clone the state - copy all outbound transitions
                for (auto &o : outbound) {
                    auto g = nfa._transition_table[o].guard();
                    nfa._transition_table.push_back(nfa_transition(new_state, g, nfa._transition_table[o].to(), nfa._transition_table[o].actions()));
                }
                // Also copy all recursive transitions
                for (auto &r : recursive) {
                    nfa._transition_table.emplace_back(new_state, nfa._transition_table[r].guard(), new_state, nfa._transition_table[r].actions());
                }
            }
            // Move the epsilon transition's action(s) to the outbound transitions
            for (auto &o : outbound) {
                // Copy the actions (in reverse order)
                for (auto a = nfa._transition_table[p].actions().rbegin(); a != nfa._transition_table[p].actions().rend(); a++) {
                    nfa._transition_table[o].actions().insert(nfa._transition_table[o].actions().cbegin(), *a);
                }
                // check the output transitions, if it's a transition that qualifies for processing, then enqueue it.
                if (nfa._transition_table[o].guard().epsilon() && !nfa._transition_table[o].actions().empty()) {
                    unprocessed.push_back(o);
                }
            }
            nfa._transition_table[p].actions().clear();
        }

        assert_valid_nfa_1(nfa._transition_table);
        assert_valid_nfa_2(nfa._transition_table);

#pragma endregion

#pragma region Delete Epsilon Transitions
        std::vector<size_t> epsilon_transitions;
        epsilon_transitions.reserve(nfa._transition_table.size());
        for (size_t i = 0; i < nfa._transition_table.size(); i++) {
            if (nfa._transition_table[i].guard().epsilon()) {
                epsilon_transitions.push_back(i);
            }
        }

        size_t i = 0;
        while (i != epsilon_transitions.size()) {
            assert(i < epsilon_transitions.size());
            auto t = epsilon_transitions[i];
            auto &et = nfa._transition_table[t];
            std::vector<nfa_transition> new_txs;
            new_txs.reserve(nfa._transition_table.size());
            for (auto &t : nfa._transition_table) {
                if (et.to() == t.from()) {
                    new_txs.emplace_back(et.from(), t.guard(), t.to(), t.actions());
                }
            }
            for (auto &nt : new_txs) {
                if (nt.guard().epsilon()) {
                    epsilon_transitions.push_back(nfa._transition_table.size());
                }
                nfa._transition_table.push_back(std::move(nt));
            }
            i++;
        }

        // Erase all epsilon transitions
        for (auto it = epsilon_transitions.rbegin(); it != epsilon_transitions.rend(); it++) {
            nfa._transition_table.erase(nfa._transition_table.begin() + *it);
        }

        assert_valid_nfa_3(nfa._transition_table);

#pragma endregion

        // Create a map for the rest of the processing
        dfa dfa;
        for (auto &t : nfa._transition_table) {
            auto f = dfa._tmap.find(t.from());
            if (f == dfa._tmap.end()) {
                auto s = t.from();
                std::vector<nfa_transition> m;
                m.reserve(10);
                m.push_back(std::move(t));
                dfa._tmap.emplace(s, std::move(m));
            }
            else {
                f->second.push_back(std::move(t));
            }
        }

#ifdef _DEBUG
        // Clear the nfa so we cannot reuse it
        nfa._tokens.clear();
        nfa._section_init_states.clear();
        nfa._transition_table.clear();
        nfa._named_asts.clear();
#endif

#pragma region Split Overlapping Guards

        for (auto &s : dfa._tmap) {
            auto left = s.second.size();
            while (left != 0) {
                // Find the split points for transition 0
                std::set<wchar_t> pts;
                for (size_t i = 1; i != s.second.size(); i++) {
                    if (s.second[i].guard().first() > s.second[0].guard().first() && s.second[i].guard().first() <= s.second[0].guard().last()) {
                        pts.emplace(s.second[i].guard().first() - 1);
                    }
                    if (s.second[i].guard().last() >= s.second[0].guard().first() && s.second[i].guard().last() < s.second[0].guard().last()) {
                        pts.emplace(s.second[i].guard().last());
                    }
                }
                if (!pts.empty()) {
                    size_t f = s.second[0].guard().first();
                    for (auto &p : pts) {
                        s.second.emplace_back(s.second[0].from(), nfa_transition_guard(f, p), s.second[0].to(), s.second[0].actions());
                        f = p + 1;
                    }
                    s.second.emplace_back(s.second[0].from(), nfa_transition_guard(f, s.second[0].guard().last()), s.second[0].to(), std::move(s.second[0].actions()));
                }
                else {
                    s.second.push_back(std::move(s.second[0]));
                }
                s.second.erase(s.second.begin());
                left--;
            }
        }

#pragma endregion

        return std::move(dfa);
    }
}