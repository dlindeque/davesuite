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
        {
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
        }
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
        
#pragma region Create DFA datastructure
        // Create a map for the rest of the processing
        dfa dfa;
        {
            // Build the map (jagged array)
            dfa._tmap.reserve(nfa._next_state);
            for (auto &t : nfa._transition_table) {
                if (dfa._tmap.size() <= t.from()) {
                    dfa._tmap.insert(dfa._tmap.end(), t.from() - dfa._tmap.size() + 1, std::vector<dfa_transition>());
                }
                dfa._tmap[t.from()].emplace_back(t.from(), dfa_transition_guard(t.guard().first(), t.guard().last()), t.to(), std::move(t.actions()));
            }

            // Find reachable states and clear transitions from unreachable states
            std::set<size_t> reachable;
            std::vector<size_t> unprocessed;
            unprocessed.push_back(0);

            while (!unprocessed.empty()) {
                auto s = unprocessed.back();
                unprocessed.pop_back();

                reachable.emplace(s);
                for (auto &t : dfa._tmap[s]) {
                    if (reachable.find(t.to()) == reachable.end()) {
                        unprocessed.push_back(t.to());
                    }
                }
            }

            for (size_t s = 0; s < dfa._tmap.size(); s++) {
                if (reachable.find(s) == reachable.end()) {
                    dfa._tmap[s].clear();
                }
                else {
                    // Make sure we've got a unique set of transition
                    std::set<dfa_transition> discovered;
                    size_t i = 0;
                    while (i < dfa._tmap[s].size()) {
                        auto f = discovered.emplace(dfa._tmap[s][i]);
                        if (f.second) {
                            // The first instance of this transition - keep it
                            i++;
                        }
                        else {
                            // The transition already existed - delete it
                            dfa._tmap[s].erase(dfa._tmap[s].begin() + i);
                        }
                    }
                }
            }
        }

#pragma endregion

#ifdef _DEBUG
        // Clear the nfa so we cannot reuse it
        nfa._section_init_states.clear();
        nfa._transition_table.clear();
        nfa._named_asts.clear();
#endif

#pragma region Split Overlapping Guards

        for (auto &s : dfa._tmap) {
            auto left = s.size();
            while (left != 0) {
                if (s[0].guard().last() == 0 && s[0].guard().first() == 0) {
                    // Nothing overlaps with <eod>
                    s.push_back(std::move(s[0]));
                    s.erase(s.begin());
                    left--;
                    continue;
                }
                // Find the split points for transition 0
                std::set<wchar_t> pts;
                for (size_t i = 1; i != s.size(); i++) {
                    if (s[i].guard().last() == 0 && s[i].guard().first() == 0) {
                        // nothing overlaps with <eod>
                        continue;
                    }
                    if (s[i].guard().first() > s[0].guard().first() && s[i].guard().first() <= s[0].guard().last()) {
                        pts.emplace(s[i].guard().first() - 1);
                    }
                    if (s[i].guard().last() >= s[0].guard().first() && s[i].guard().last() < s[0].guard().last()) {
                        pts.emplace(s[i].guard().last());
                    }
                }
                if (!pts.empty()) {
                    wchar_t f = s[0].guard().first();
                    for (auto &p : pts) {
                        std::vector<transition_action> actions(s[0].actions());
                        s.emplace_back(s[0].from(), dfa_transition_guard(f, p), s[0].to(), std::move(actions));
                        f = p + 1;
                    }
                    s.emplace_back(s[0].from(), dfa_transition_guard(f, s[0].guard().last()), s[0].to(), std::move(s[0].actions()));
                }
                else {
                    s.push_back(std::move(s[0]));
                }
                s.erase(s.begin());
                left--;
            }
        }

#pragma endregion

#pragma region Make Deterministic

        std::map<std::set<size_t>, size_t> composite_states;
        size_t s = 0;
        while (s != dfa._tmap.size()) {
            std::map<dfa_transition_guard, std::vector<size_t>> groups;
            for (size_t i = 0; i < dfa._tmap[s].size(); i++) {
                auto f = groups.find(dfa._tmap[s][i].guard());
                if (f == groups.end()) {
                    std::vector<size_t> g;
                    g.push_back(i);
                    groups.emplace(dfa._tmap[s][i].guard(), std::move(g));
                }
                else {
                    f->second.push_back(i);
                }
            }
            std::set<size_t> delete_indexes;
            for (auto &g : groups) {
                if (g.second.size() == 1) continue; // already deterministic
                assert(g.second.size() > 1);
                
                // Find the composite state
                std::set<size_t> tstates;
                for (auto &gi : g.second) {
                    tstates.emplace(dfa._tmap[s][gi].to());
                }

                auto cs = composite_states.emplace(tstates, nfa._next_state);
                if (cs.second) {
                    // new state
                    nfa._next_state++;
                    if (dfa._tmap.size() <= cs.first->second) {
                        dfa._tmap.insert(dfa._tmap.end(), cs.first->second - dfa._tmap.size() + 1, std::vector<dfa_transition>());
                    }
                    // copy all 'outbound' transitions of target states
                    for (auto &ts : tstates) {
                        for (auto &ot : dfa._tmap[ts]) {
                            dfa._tmap[cs.first->second].emplace_back(cs.first->second, ot.guard(), ot.to(), ot.actions());
                        }
                    }
                }
                // state number = cs.first->second

                // Setup a transition from s to composite state
                std::vector<transition_action> nt_actions;
                for (auto &gi : g.second) {
                    for (auto &a : dfa._tmap[s][gi].actions()) {
                        nt_actions.push_back(a);
                    }
                }
                dfa._tmap[s].emplace_back(s, std::move(g.first), cs.first->second, std::move(nt_actions));

                // record indexes to delete (later)
                for (auto &gi : g.second) {
                    delete_indexes.emplace(gi);
                }
            }
            // Delete the original transitions (the nfa transitions)
            for (auto di = delete_indexes.rbegin(); di != delete_indexes.rend(); di++) {
                dfa._tmap[s].erase(dfa._tmap[s].begin() + *di);
            }
            s++;
        }

        return std::move(dfa);

#pragma endregion

#pragma region Remove transitions from Unreachable states
        {
            std::set<size_t> reachable;
            std::vector<size_t> unprocessed;
            unprocessed.push_back(0);

            while (!unprocessed.empty()) {
                auto s = unprocessed.back();
                unprocessed.pop_back();

                reachable.emplace(s);
                for (auto &t : dfa._tmap[s]) {
                    if (reachable.find(t.to()) == reachable.end()) {
                        unprocessed.push_back(t.to());
                    }
                }
            }

            for (size_t s = 0; s < dfa._tmap.size(); s++) {
                if (reachable.find(s) == reachable.end()) {
                    dfa._tmap[s].clear();
                }
            }

            while (dfa._tmap.back().empty()) {
                dfa._tmap.pop_back();
            }
        }
#pragma endregion

        return std::move(dfa);
    }
}