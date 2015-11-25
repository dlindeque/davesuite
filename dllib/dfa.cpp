#include "stdafx.h"

#include <assert.h>
#include <algorithm>

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
        friend inline auto operator <(const dfa_guard &g1, const dfa_guard &g2) -> bool {
            if (g1.first != g2.first) return g1.first < g2.first;
            return g1.last < g2.last;
        }
    };

    auto dfa::try_compile(nfa_builder &&nfa, const std::function<state_yield(const state_yield&, const state_yield&)> &conflict_resolver) -> dfa
    {
        // find the goto section states
        for (auto &gs : nfa._state_yields) {
            if (gs.second.goto_section != nullptr) {
                auto f = nfa._sections.find(*gs.second.goto_section);
                assert(f != nfa._sections.end());
                gs.second.goto_section_start = f->second;
            }
        }

#pragma region Create DFA datastructure
        // Create a map for the rest of the processing
        dfa dfa;
        dfa._state_yields = std::move(nfa.state_yields());
        // Build the map
        dfa._tmap.reserve(nfa._next_state);
        for (auto &t : nfa._transitions) {
            auto f = dfa._tmap.find(t.from());
            if (f == dfa._tmap.end()) {
                std::vector<fa_transition> lst;
                lst.emplace_back(t.from(), t.epsilon(), t.first(), t.last(), t.to());
                dfa._tmap.emplace(t.from(), std::move(lst));
            }
            else {
                f->second.emplace_back(t.from(), t.epsilon(), t.first(), t.last(), t.to());
            }
        }
#pragma endregion

#ifdef _DEBUG
        // Clear the nfa so we cannot reuse it
        nfa._patterns.clear();
        nfa._transitions.clear();
        nfa._shared_sections.clear();
#endif

#pragma region Make Deterministic
        std::map<std::set<size_t>, size_t> closures;
        std::vector<size_t> unprocessed;
        unprocessed.push_back(0);
        std::set<size_t> reachable;
        while (!unprocessed.empty()) {
            auto state = unprocessed.back();
            unprocessed.pop_back();
            if (!reachable.emplace(state).second) {
                // already seen this state
                continue;
            }

            // Find the e-closure set of state & transitions
            std::vector<fa_transition> lst;
            std::set<size_t> eclosure_states;
            std::vector<size_t> eclosure_unprocessed;
            eclosure_unprocessed.push_back(state);
            std::vector<state_yield> yields;
            while (!eclosure_unprocessed.empty()) {
                auto s = eclosure_unprocessed.back();
                eclosure_unprocessed.pop_back();
                if (!eclosure_states.emplace(s).second) {
                    // already seen
                    continue;
                }
                auto f = dfa._state_yields.find(s);
                if (f != dfa._state_yields.end()) {
                    yields.push_back(f->second);
                }
                for (auto &t : dfa._tmap[s]) {
                    if (t.epsilon()) {
                        eclosure_unprocessed.push_back(t.to());
                    }
                    else {
                        lst.emplace_back(state, false, t.first(), t.last(), t.to());
                    }
                }
            }
            if (!yields.empty()) {
                auto sy = yields.back();
                yields.pop_back();
                while (!yields.empty()) {
                    sy = conflict_resolver(sy, yields.back());
                    yields.pop_back();
                }
                if (dfa._state_yields.find(state) == dfa._state_yields.end()) {
                    dfa._state_yields.emplace(state, sy);
                }
                else {
                    dfa._state_yields[state] = sy;
                }
            }

            // Split overlapping guards
            auto size = lst.size();
            size_t i = 0;
            while (i != size) {
                // Find the split points for the transition
                std::set<wchar_t> pts;
                for (size_t p = i + 1; p != lst.size(); p++) {
                    if (lst[p].first() > lst[i].first() && lst[p].first() <= lst[i].last()) {
                        pts.emplace(lst[p].first() - 1);
                    }
                    if (lst[p].last() >= lst[i].first() && lst[p].last() < lst[i].last()) {
                        pts.emplace(lst[p].last());
                    }
                }
                // Split at each pts point
                if (!pts.empty()) {
                    wchar_t f = lst[i].first();
                    for (auto &p : pts) {
                        lst.emplace_back(state, false, f, p, lst[i].to());
                        f = p + 1;
                    }
                    lst.emplace_back(state, false, f, lst[i].last(), lst[i].to());
                }
                else {
                    lst.emplace_back(state, false, lst[i].first(), lst[i].last(), lst[i].to());
                }

                // Process next
                i++;
            }
            lst.erase(lst.begin(), lst.begin() + size);

            // Find groups of guards
            std::map<dfa_guard, std::vector<size_t>> groups;
            for (size_t i = 0; i < lst.size(); i++) {
                dfa_guard g;
                g.first = lst[i].first();
                g.last = lst[i].last();
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

            // Create new state to make it deterministic
            std::set<size_t> delete_indexes;
            for (auto &g : groups) {
                if (g.second.size() == 1) {
                    // already deterministic
                    unprocessed.push_back(lst[g.second[0]].to());
                    continue;
                }
                assert(g.second.size() > 1);

                // Create a new state for this guard
                std::set<size_t> closure;
                for (auto &gi : g.second) {
                    closure.emplace(lst[gi].to());
                }

                auto cs = closures.emplace(closure, nfa._next_state);
                if (cs.second) {
                    // new state
                    nfa._next_state++;
                    // copy all 'outbound' transitions of target states
                    for (auto &ts : closure) {
                        for (auto &ot : dfa._tmap[ts]) {
                            dfa._tmap[cs.first->second].emplace_back(cs.first->second, ot.epsilon(), ot.first(), ot.last(), ot.to());
                        }
                    }
                    // enqueue new state for processing
                    unprocessed.push_back(cs.first->second);
                    // Merge all the 'source' state yield to this new state
                    std::vector<state_yield> nyields;
                    for (auto &s : closure) {
                        auto f = dfa._state_yields.find(s);
                        if (f != dfa._state_yields.end()) {
                            nyields.push_back(f->second);
                        }
                    }
                    if (!nyields.empty()) {
                        auto sy = nyields.back();
                        nyields.pop_back();
                        while (!nyields.empty()) {
                            sy = conflict_resolver(sy, nyields.back());
                            nyields.pop_back();
                        }
                        if (dfa._state_yields.find(cs.first->second) == dfa._state_yields.end()) {
                            dfa._state_yields.emplace(cs.first->second, sy);
                        }
                        else {
                            dfa._state_yields[cs.first->second] = sy;
                        }
                    }
                }

                // Setup a transition from s to the closure state
                lst.emplace_back(state, false, g.first.first, g.first.last, cs.first->second);

                // record indexes to delete (later)
                for (auto &gi : g.second) {
                    delete_indexes.emplace(gi);
                }
            }
            // Delete the original transitions (the nfa transitions)
            for (auto di = delete_indexes.rbegin(); di != delete_indexes.rend(); di++) {
                lst.erase(lst.begin() + *di);
            }
            // Replace the state's transitions with this new set
            dfa._tmap[state] = std::move(lst);
        }

#pragma endregion

#pragma region Remove transitions from Unreachable states
        std::vector<size_t> delete_states;
        for (auto i = dfa._tmap.begin(); i != dfa._tmap.end(); i++){
            if (reachable.find(i->first) == reachable.end()) {
                // not reachable - erase
                delete_states.push_back(i->first);
            }
        }
        for (auto &ds : delete_states) {
            dfa._tmap.erase(ds);
            dfa._state_yields.erase(ds);
        }
#pragma endregion

        return dfa;
    }
}