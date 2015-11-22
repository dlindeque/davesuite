#include "stdafx.h"

#include <assert.h>

#include "nfa_builder.h"
#include "dfa.h"
#include "re_lexer.h"
#include "..\common\offset_logger.h"

namespace davelexer
{

#ifdef _DEBUG
    auto assert_valid_nfa_1(const std::vector<fa_transition> &transitions) -> void
    {
        // Ensure we don't have any recursive epsilon transitions with output
    }
#else
    inline auto assert_valid_nfa_1(const std::vector<fa_transition>&) -> void {}
#endif

#ifdef _DEBUG
    auto assert_valid_nfa_2(const std::vector<fa_transition> &transitions) -> void
    {
        // Ensure we don't have any epsilon transitions with yields
        for (auto &t : transitions) {
            assert(!t.epsilon() || t.yield() == 0);
        }
    }
#else
    inline auto assert_valid_nfa_2(const std::vector<fa_transition>&) -> void {}
#endif

#ifdef _DEBUG
    auto assert_valid_nfa_3(const std::vector<fa_transition> &transitions) -> void
    {
        // Ensure we don't have any epsilon transitions
        for (auto &t : transitions) {
            assert(!t.epsilon());
        }
    }
#else
    inline auto assert_valid_nfa_3(const std::vector<fa_transition>&) -> void {}
#endif

    struct dfa_guard {
        wchar_t first;
        wchar_t last;
        bool eod;
        friend inline auto operator <(const dfa_guard &g1, const dfa_guard &g2) -> bool {
            if (g1.eod != g2.eod) return g2.eod;
            if (g1.first != g2.first) return g1.first < g2.first;
            return g1.last < g2.last;
        }
    };

    auto dfa::try_compile(nfa_builder &&nfa, const std::function<size_t(size_t,size_t)> &conflict_resolver) -> dfa
    {
#pragma region Clear Epsilon Transitions Of Yields
        {
            std::vector<size_t> unprocessed;
            unprocessed.reserve(nfa._transitions.size());
            for (size_t i = 0; i < nfa._transitions.size(); i++) {
                if (nfa._transitions[i].epsilon() && nfa._transitions[i].yield() != 0) {
                    unprocessed.push_back(i);
                }
            }

            while (!unprocessed.empty()) {
                auto p = unprocessed.back();
                unprocessed.pop_back();
                assert(nfa._transitions[p].yield() != 0);
                std::vector<size_t> inbound, outbound, recursive;
                inbound.reserve(10);
                outbound.reserve(10);
                recursive.reserve(10);
                for (size_t i = 0; i < nfa._transitions.size(); i++) {
                    if (&nfa._transitions[i] != &nfa._transitions[p] && nfa._transitions[i].to() == nfa._transitions[p].to()) {
                        inbound.push_back(i); // include recursive transitions
                    }
                    if (nfa._transitions[i].from() == nfa._transitions[p].to()) {
                        if (nfa._transitions[i].from() != nfa._transitions[i].to())
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
                    nfa._transitions[ip].to(new_state);
                    // Clone the state - copy all outbound transitions
                    for (auto &o : outbound) {
                        nfa._transitions.emplace_back(new_state, nfa._transitions[o].epsilon(), nfa._transitions[o].eod(), nfa._transitions[o].first(), nfa._transitions[o].last(), nfa._transitions[o].to(), nfa._transitions[o].yield());
                    }
                    // Also copy all recursive transitions
                    for (auto &r : recursive) {
                        nfa._transitions.emplace_back(new_state, nfa._transitions[r].epsilon(), nfa._transitions[r].eod(), nfa._transitions[r].first(), nfa._transitions[r].last(), new_state, nfa._transitions[r].yield());
                    }
                }
                // Move the epsilon transition's action(s) to the outbound transitions
                for (auto &o : outbound) {
                    // Move the yield to the outbound transition
                    if (nfa._transitions[o].yield() != nfa._transitions[p].yield()) {
                        assert(nfa._transitions[p].yield() != 0);
                        size_t y;
                        if (nfa._transitions[o].yield() == 0) {
                            y = nfa._transitions[p].yield();
                        }
                        else {
                            // We have a yield/yield conflict - use precedence to select the best one
                            y = conflict_resolver(nfa._transitions[o].yield(), nfa._transitions[p].yield());
                        }
                        assert(y != 0); // We assume the resolver can always resolve conflicts
                        nfa._transitions[o].yield(y);
                    }
                    // check the output transitions, if it's a transition that qualifies for processing, then enqueue it.
                    if (nfa._transitions[o].epsilon() && nfa._transitions[o].yield() != 0) {
                        unprocessed.push_back(o);
                    }
                }
                nfa._transitions[p].yield(0);
            }

            assert_valid_nfa_1(nfa._transitions);
            assert_valid_nfa_2(nfa._transitions);
        }
#pragma endregion
        
#pragma region Delete Epsilon Transitions
        // Build list of indexes to epsilon transitions
        std::vector<size_t> epsilon_transitions;
        epsilon_transitions.reserve(nfa._transitions.size());
        for (size_t i = 0; i < nfa._transitions.size(); i++) {
            if (nfa._transitions[i].epsilon()) {
                epsilon_transitions.push_back(i);
            }
        }

        size_t i = 0;
        while (i != epsilon_transitions.size()) {
            assert(i < epsilon_transitions.size());
            // Get a reference to the epsilon transition
            auto &et = nfa._transitions[epsilon_transitions[i]];
            std::vector<fa_transition> new_txs;
            new_txs.reserve(nfa._transitions.size());
            for (auto &t : nfa._transitions) {
                if (et.to() == t.from()) {
                    // Found a transition (t) out of the state that the epsilon transition (et) points to
                    new_txs.emplace_back(et.from(), t.epsilon(), t.eod(), t.first(), t.last(), t.to(), t.yield());
                }
            }
            for (auto &nt : new_txs) {
                if (nt.epsilon()) {
                    epsilon_transitions.push_back(nfa._transitions.size());
                }
                nfa._transitions.emplace_back(nt.from(), nt.epsilon(), nt.eod(), nt.first(), nt.last(), nt.to(), nt.yield());
            }
            i++;
        }

        // Erase all epsilon transitions
        for (auto it = epsilon_transitions.rbegin(); it != epsilon_transitions.rend(); it++) {
            nfa._transitions.erase(nfa._transitions.begin() + *it);
        }

        assert_valid_nfa_3(nfa._transitions);

#pragma endregion

#pragma region Create DFA datastructure
        // Create a map for the rest of the processing
        dfa dfa(nfa.compile_yield_details());
        {
            // Build the map (jagged array)
            dfa._tmap.reserve(nfa._next_state);
            for (auto &t : nfa._transitions) {
                if (dfa._tmap.size() <= t.from()) {
                    dfa._tmap.insert(dfa._tmap.end(), t.from() - dfa._tmap.size() + 1, std::vector<fa_transition>());
                }
                dfa._tmap[t.from()].emplace_back(t.from(), t.epsilon(), t.eod(), t.first(), t.last(), t.to(), t.yield());
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
                    std::set<fa_transition> discovered;
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
        nfa._bindings.clear();
        nfa._transitions.clear();
        nfa._shared_sections.clear();
#endif

#pragma region Make Deterministic
        std::map<std::set<size_t>, size_t> composite_states;
        size_t s = 0;
        while (s != dfa._tmap.size()) {
            // Split overlapping guards
            auto left = dfa._tmap[s].size();
            while (left != 0) {
                if (dfa._tmap[s][0].eod()) {
                    // Nothing overlaps with <eod>
                    //fa_transition(from, ep, eod, first, last, to, yield)
                    dfa._tmap[s].emplace_back(dfa._tmap[s][0].from(), dfa._tmap[s][0].epsilon(), dfa._tmap[s][0].eod(), dfa._tmap[s][0].first(), dfa._tmap[s][0].last(), dfa._tmap[s][0].to(), dfa._tmap[s][0].yield());
                    dfa._tmap[s].erase(dfa._tmap[s].begin());
                    left--;
                    continue;
                }
                // Find the split points for transition 0
                std::set<wchar_t> pts;
                for (size_t i = 1; i != dfa._tmap[s].size(); i++) {
                    if (dfa._tmap[s][i].eod()) {
                        // nothing overlaps with <eod>
                        continue;
                    }
                    if (dfa._tmap[s][i].first() > dfa._tmap[s][0].first() && dfa._tmap[s][i].first() <= dfa._tmap[s][0].last()) {
                        pts.emplace(dfa._tmap[s][i].first() - 1);
                    }
                    if (dfa._tmap[s][i].last() >= dfa._tmap[s][0].first() && dfa._tmap[s][i].last() < dfa._tmap[s][0].last()) {
                        pts.emplace(dfa._tmap[s][i].last());
                    }
                }
                if (!pts.empty()) {
                    wchar_t f = dfa._tmap[s][0].first();
                    for (auto &p : pts) {
                        //fa_transition(from, ep, eod, first, last, to, yield)
                        dfa._tmap[s].emplace_back(dfa._tmap[s][0].from(), dfa._tmap[s][0].epsilon(), dfa._tmap[s][0].eod(), f, p, dfa._tmap[s][0].to(), dfa._tmap[s][0].yield());
                        f = p + 1;
                    }
                    //fa_transition(from, ep, eod, first, last, to, yield)
                    dfa._tmap[s].emplace_back(dfa._tmap[s][0].from(), dfa._tmap[s][0].epsilon(), dfa._tmap[s][0].eod(), f, dfa._tmap[s][0].last(), dfa._tmap[s][0].to(), dfa._tmap[s][0].yield());
                }
                else {
                    //fa_transition(from, ep, eod, first, last, to, yield)
                    dfa._tmap[s].emplace_back(dfa._tmap[s][0].from(), dfa._tmap[s][0].epsilon(), dfa._tmap[s][0].eod(), dfa._tmap[s][0].first(), dfa._tmap[s][0].last(), dfa._tmap[s][0].to(), dfa._tmap[s][0].yield());
                }
                dfa._tmap[s].erase(dfa._tmap[s].begin());
                left--;
            }

            // Merge common guards
            std::map<dfa_guard, std::vector<size_t>> groups;
            for (size_t i = 0; i < dfa._tmap[s].size(); i++) {
                dfa_guard g;
                g.first = dfa._tmap[s][i].first();
                g.last = dfa._tmap[s][i].last();
                g.eod = dfa._tmap[s][i].eod();
                auto f = groups.find(g);
                if (f == groups.end()) {
                    std::vector<size_t> gv;
                    gv.push_back(i);
                    groups.emplace(g, std::move(gv));
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
                        dfa._tmap.insert(dfa._tmap.end(), cs.first->second - dfa._tmap.size() + 1, std::vector<fa_transition>());
                    }
                    // copy all 'outbound' transitions of target states
                    for (auto &ts : tstates) {
                        for (auto &ot : dfa._tmap[ts]) {
                            dfa._tmap[cs.first->second].emplace_back(cs.first->second, ot.epsilon(), ot.eod(), ot.first(), ot.last(), ot.to(), ot.yield());
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
                dfa._tmap[s].emplace_back(s, false, g.first.eod, g.first.first, g.first.last, cs.first->second, y);
            
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

        return dfa;
    }
}