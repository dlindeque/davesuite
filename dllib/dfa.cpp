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
        // Ensure we don't have any epsilon transitions with yields
        for (auto &t : transitions) {
            assert(!t.guard().epsilon() || t.yield() == 0);
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

    auto dfa::try_compile(nfa &&nfa, std::wostream &errors, bool &ok, const std::function<size_t(size_t,size_t)> &conflict_resolver) -> dfa
    {
        ok = true;
        
#pragma region Clear Epsilon Transitions Of Yields
        {
            std::vector<size_t> unprocessed;
            unprocessed.reserve(nfa._transition_table.size());
            for (size_t i = 0; i < nfa._transition_table.size(); i++) {
                if (nfa._transition_table[i].guard().epsilon() && nfa._transition_table[i].yield() != 0) {
                    unprocessed.push_back(i);
                }
            }

            while (!unprocessed.empty()) {
                auto p = unprocessed.back();
                unprocessed.pop_back();
                assert(nfa._transition_table[p].yield() != 0);
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
                        nfa._transition_table.push_back(nfa_transition(new_state, g, nfa._transition_table[o].to(), nfa._transition_table[o].yield()));
                    }
                    // Also copy all recursive transitions
                    for (auto &r : recursive) {
                        nfa._transition_table.emplace_back(new_state, nfa._transition_table[r].guard(), new_state, nfa._transition_table[r].yield());
                    }
                }
                // Move the epsilon transition's action(s) to the outbound transitions
                for (auto &o : outbound) {
                    // Move the yield to the outbound transition
                    if (nfa._transition_table[o].yield() != nfa._transition_table[p].yield()) {
                        assert(nfa._transition_table[p].yield() != 0);
                        size_t y;
                        if (nfa._transition_table[o].yield() == 0) {
                            y = nfa._transition_table[p].yield();
                        }
                        else {
                            // We have a yield/yield conflict - use precedence to select the best one
                            y = conflict_resolver(nfa._transition_table[o].yield(), nfa._transition_table[p].yield());
                        }
                        assert(y != 0); // We assume the resolver can always resolve conflicts
                        nfa._transition_table[o].yield(y);
                    }
                    // check the output transitions, if it's a transition that qualifies for processing, then enqueue it.
                    if (nfa._transition_table[o].guard().epsilon() && nfa._transition_table[o].yield() != 0) {
                        unprocessed.push_back(o);
                    }
                }
                nfa._transition_table[p].yield(0);
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
                    new_txs.emplace_back(et.from(), t.guard(), t.to(), t.yield());
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
                dfa._tmap[t.from()].emplace_back(t.from(), dfa_transition_guard(t.guard().first(), t.guard().last()), t.to(), t.yield());
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

#pragma region Make Deterministic

        std::map<std::set<size_t>, size_t> composite_states;
        size_t s = 0;
        while (s != dfa._tmap.size()) {
            // Split overlapping guards
            auto left = dfa._tmap[s].size();
            while (left != 0) {
                if (dfa._tmap[s][0].guard().last() == 0 && dfa._tmap[s][0].guard().first() == 0) {
                    // Nothing overlaps with <eod>
                    dfa._tmap[s].push_back(std::move(dfa._tmap[s][0]));
                    dfa._tmap[s].erase(dfa._tmap[s].begin());
                    left--;
                    continue;
                }
                // Find the split points for transition 0
                std::set<wchar_t> pts;
                for (size_t i = 1; i != dfa._tmap[s].size(); i++) {
                    if (dfa._tmap[s][i].guard().last() == 0 && dfa._tmap[s][i].guard().first() == 0) {
                        // nothing overlaps with <eod>
                        continue;
                    }
                    if (dfa._tmap[s][i].guard().first() > dfa._tmap[s][0].guard().first() && dfa._tmap[s][i].guard().first() <= dfa._tmap[s][0].guard().last()) {
                        pts.emplace(dfa._tmap[s][i].guard().first() - 1);
                    }
                    if (dfa._tmap[s][i].guard().last() >= dfa._tmap[s][0].guard().first() && dfa._tmap[s][i].guard().last() < dfa._tmap[s][0].guard().last()) {
                        pts.emplace(dfa._tmap[s][i].guard().last());
                    }
                }
                if (!pts.empty()) {
                    wchar_t f = dfa._tmap[s][0].guard().first();
                    for (auto &p : pts) {
                        dfa._tmap[s].emplace_back(dfa._tmap[s][0].from(), dfa_transition_guard(f, p), dfa._tmap[s][0].to(), dfa._tmap[s][0].yield());
                        f = p + 1;
                    }
                    dfa._tmap[s].emplace_back(dfa._tmap[s][0].from(), dfa_transition_guard(f, dfa._tmap[s][0].guard().last()), dfa._tmap[s][0].to(), dfa._tmap[s][0].yield());
                }
                else {
                    dfa._tmap[s].push_back(std::move(dfa._tmap[s][0]));
                }
                dfa._tmap[s].erase(dfa._tmap[s].begin());
                left--;
            }
            s++;
            continue;
            // Merge common guards
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
                            dfa._tmap[cs.first->second].emplace_back(cs.first->second, ot.guard(), ot.to(), ot.yield());
                        }
                    }
                }
                // state number = cs.first->second

                // Setup a transition from s to composite state
                size_t y = 0;
                for (auto &gi : g.second) {
                    if (dfa._tmap[s][gi].yield() != y) {
                        if (y == 0) {
                            y = dfa._tmap[s][gi].yield();
                        }
                        else {
                            y = conflict_resolver(y, dfa._tmap[s][gi].yield());
                        }
                    }
                }
                dfa._tmap[s].emplace_back(s, std::move(g.first), cs.first->second, y);

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