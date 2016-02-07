#include "dfa.h"
#include "log.h"

#include <assert.h>

namespace dc
{
	typedef std::pair<wchar_t, wchar_t> dfa_guard;
}

namespace std
{
	template<> struct hash<dc::dfa_guard> {
		inline auto operator()(const dc::dfa_guard &v) const -> size_t {
            return hash<wchar_t>()(v.first) + hash<wchar_t>()(v.second);
        }
	};

	template<> struct hash<std::set<size_t>> {
		inline auto operator()(const std::set<size_t> &v) const -> size_t {
			size_t hc = 55435;
			for(auto &x : v) {
				hc += hash<size_t>()(x);
			}
            return hc;
        }
	};
}

namespace dc
{
	inline auto find_eclosure(size_t state, const std::unordered_multimap<size_t, Transition> &outbound_transitions, std::vector<Transition> &lst, std::vector<size_t> &final_states) -> void
	{
		std::vector<size_t> unprocessed;
		unprocessed.push_back(state);
		std::set<size_t> seen;
		while(!unprocessed.empty()) {
			auto s = unprocessed.back();
			unprocessed.pop_back();
			if (!seen.emplace(s).second) continue;

			auto f = outbound_transitions.equal_range(s);
			for(auto i = f.first; i != f.second; i++) {
				if (i->second.IsEpsilon) {
					unprocessed.push_back(i->second.ToState);
				} 
				else if (i->second.First == L'\x0' && i->second.Last == L'\x0') {
					// This is a transition to indicate that the 'FromState' was the token final state
					final_states.push_back(i->second.FromState);
				}
				else {
					lst.push_back(i->second);
				}
			}
		}
	}

	inline auto split_overlapping_guards(std::vector<Transition> &transitions) -> void
	{
		auto size = transitions.size();
        size_t i = 0;
        while (i != size) {
            // Find the split points for the transition
            std::set<wchar_t> pts;
            for (size_t p = i + 1; p != transitions.size(); p++) {
                if (transitions[p].First > transitions[i].First && transitions[p].First <= transitions[i].Last) {
                    pts.emplace(transitions[p].First - 1);
                }
                if (transitions[p].Last >= transitions[i].First && transitions[p].Last < transitions[i].Last) {
                    pts.emplace(transitions[p].Last);
                }
            }
            // Split at each pts point
            if (!pts.empty()) {
            	// Create new transitions split at the split points
                wchar_t f = transitions[i].First;
                for (auto &p : pts) {
                    transitions.emplace_back(transitions[i].FromState, false, f, p, transitions[i].ToState);
                    f = p + 1;
                }
                transitions.emplace_back(transitions[i].FromState, false, f, transitions[i].Last, transitions[i].ToState);
            }
            else {
            	// No overlapping
                transitions.push_back(std::move(transitions[i]));
            }

            // Process next
            i++;
        }
        // Erase all the original transitions
        transitions.erase(transitions.begin(), transitions.begin() + size);
	}

	auto build_dfa(logger *logger, const nfa &nfa) -> dfa
	{
        auto next_state = nfa.next_state;
		// Build a lookup of transitions. state->transition[]
		std::unordered_multimap<size_t, Transition> outbound_transitions;
		for(auto &t : nfa.transitions) {
			outbound_transitions.emplace(t.FromState, t);
		}

		std::unordered_map<size_t, std::set<NfaAction, NfaActionLess>> actions;
		dfa dfa;
        dfa.automataspns = nfa.automataspns;

		// The list of unprocessed states
		std::vector<size_t> unprocessed_states;
		unprocessed_states.push_back(0);
		std::set<size_t> seen;
		std::unordered_map<std::set<size_t>, size_t> composite_states;

		while(!unprocessed_states.empty()) {
			// Get the next state to process
			auto state = unprocessed_states.back();
			unprocessed_states.pop_back();
			if (!seen.emplace(state).second) continue;
            
            auto af = nfa.actions.find(state);
            if (af != nfa.actions.end()) {
                auto hf = actions.emplace(state, std::set<NfaAction, NfaActionLess>());
                for(auto a : af->second) {
                    hf.first->second.emplace(a);
                }
            }
            
            std::vector<size_t> final_states;

			// Find the e-closure outbound transitions
			std::vector<Transition> eclosure;
            find_eclosure(state, outbound_transitions, eclosure, final_states);

            // Add all the actions from the final states found to this state's actions
            for(auto &fs : final_states) {
                auto f = nfa.actions.find(fs);
                if (f != nfa.actions.end()) {
                	auto nf = actions.emplace(state, std::set<NfaAction, NfaActionLess>());
                    for(auto &a : f->second) {
                        nf.first->second.emplace(a);
                        if (a.IsGoto) {
	                    	unprocessed_states.push_back(a.GotoAutomata);
	                    }
                    }
                }
            }

            // Split transitions with overlapping guards
            split_overlapping_guards(eclosure);

            // Group transitions by guards (destroy the eclosure vector elements)
            std::unordered_map<dfa_guard, std::vector<Transition>> groups;
            for(auto &transition : eclosure) {
            	auto f = groups.emplace(dfa_guard(transition.First, transition.Last), std::vector<Transition>());
            	f.first->second.push_back(std::move(transition));
            }

            // Create new states for indeterministic transitions
            for(auto &g : groups) {
            	// At this point, each group will have same FromState, First & Last
            	// We need to group by ToState and aggregate the references so we don't get duplicates
            	std::unordered_map<size_t, Transition> grp2;
            	for(auto &item : g.second) {
            		grp2.emplace(item.ToState, item);
            	}

            	if (grp2.size() == 1) {
            		// Already deterministic. Enqueue the destination state for processing
            		unprocessed_states.push_back(grp2.begin()->second.ToState);

            		// Add to output
            		auto dh = dfa.transitions.emplace(state, std::vector<Transition>()); // References
                    dh.first->second.emplace_back(state, // FromState
                                                             false, // IsEpsilon
                                                             g.first.first, // First
                                                             g.first.second,  // Last
                                                             grp2.begin()->second.ToState); // ToState
            	}
            	else {
            		// Create the composite state
            		std::set<size_t> composite_state;
            		for(auto &t : grp2) {
            			composite_state.emplace(t.second.ToState);
            		}
            		size_t target_state;
            		auto sf = composite_states.emplace(composite_state, next_state);
            		if (sf.second) {
	            		// Create a new state
	            		target_state = next_state++;

	            		// Add the composite state's outbound transitions to the outbound transitions map
	            		std::vector<Transition> new_txs;
	            		for(auto &t : grp2) {
	            			// record the actions for the composite state
	            			auto af = nfa.actions.find(t.second.ToState);
                            if (af != nfa.actions.end()) {
                                for(auto &a : af->second) {
                                    if (a.IsGoto) {
                                        unprocessed_states.push_back(a.GotoAutomata);
                                    }
                                }
                                actions.emplace(target_state, af->second);
                            }
	            			// add the transitions from the composite state
	            			auto f = outbound_transitions.equal_range(t.second.ToState);
	            			for(auto i = f.first; i != f.second; i++) {
								new_txs.push_back(i->second);
	            			}
	            		}
	            		for(auto &t : new_txs) {
	            			outbound_transitions.emplace(target_state, std::move(t));
	            		}

	            		// Enqueue the new state for processing
	            		unprocessed_states.push_back(target_state);
	            	}
	            	else {
	            		target_state = sf.first->second;
	            	}
                    
            		// Create new transition for output
                    auto df = dfa.transitions.emplace(state, std::vector<Transition>());
                    df.first->second.emplace_back(state, false, g.first.first, g.first.second, target_state);
            	}
            }
		}
        
        // Create the list of all actions. action -> precedingAction[]
        std::map<NfaAction, std::vector<NfaAction>, NfaActionLess> all_actions;
        for(auto &s : actions) {
            for(auto &a : s.second) {
                all_actions.emplace(a, std::vector<NfaAction>());
            }
        }
        
        for(auto &s : actions) {
            // Use the precedence to find the best yield token
            const NfaAction *best_action = nullptr;
            bool first = true;
            for(auto &a : s.second) {
                if (first) {
                    best_action = &a;
                    first = false;
                }
                else {
                    if (a.Precedence < best_action->Precedence) {
                        best_action = &a;
                    }
                }
            }
            if (best_action != nullptr) {
                auto f = all_actions.find(*best_action);
                if (f != all_actions.end()) {
                    all_actions.erase(f);
                }
                for(auto &a : s.second) {
                	if (best_action != &a) {
                		f = all_actions.find(a);
                		if (f != all_actions.end()) {
                			f->second.push_back(*best_action);
                		}
                	}
                }
            }
            //dfa.actions.emplace(s.first, DfaAction { true, *best_action, 0, NfaAction(), false });
            dfa.actions.emplace(s.first, DfaAction { true, *best_action });
        }

        // Report the lost tokens
        for(auto &a : all_actions) {
            log::warning::TokenLost(logger, a.first, a.second);
        }
        
        return dfa;
	}

    inline auto get_range_char(wchar_t from, wchar_t to, const Transition &t, std::wstring &dest) -> bool {
        if (to < t.First) return false;
        if (from > t.Last) return false;
        if (from < t.First) {
            dest += t.First;
        }
        else {
            dest += from;
        }
        return true;
    }

    inline auto get_char_from(const std::wstring &chars, const Transition &t, std::wstring &dest) -> bool {
        for(auto &ch : chars) {
            if (get_range_char(ch, ch, t, dest)) return true;
        }
        return false;
    }

    inline auto get_char_from(wchar_t ch, const std::wstring &desc, const Transition &t, std::wstring &dest) -> bool {
        if (t.First <= ch || t.Last >= ch) {
            dest += desc;
            return true;
        }
        else {
            return false;
        }
    }
    
    inline auto get_sample(std::wstring &sample, const std::vector<Transition> &options) -> std::wstring {
        // All the options lead to the same state, we need to find the transition with the best printable representation
        std::wstring s(sample);
        // see whether we can find a..z
        for(auto &t : options) {
            if (get_range_char(L'a', L'z', t, s)) return s;    
        }
        // see whether we can find A..Z
        for(auto &t : options) {
            if (get_range_char(L'A', L'Z', t, s)) return s;    
        }
        // see whether we can find 0..9
        for(auto &t : options) {
            if (get_range_char(L'0', L'9', t, s)) return s;    
        }
        // see whether we can find !@#£$%^&*()_-+={[}]:;"'|\~`<,>.?/
        for(auto &t : options) {
            if (get_char_from(L"!@#£$%^&*()_-+={[}]:;\"'|\\~`<,>.?/", t, s)) return s;    
        }
        // see whether we can find ' ' \t \n \r \f \v \b
        for(auto &t : options) {
            if (get_char_from(L' ', L" ", t, s)) return s;
            if (get_char_from(L'\t', L"\\t", t, s)) return s;
            if (get_char_from(L'\n', L"\\n", t, s)) return s;
            if (get_char_from(L'\r', L"\\r", t, s)) return s;
            if (get_char_from(L'\f', L"\\f", t, s)) return s;
            if (get_char_from(L'\v', L"\\v", t, s)) return s;
            if (get_char_from(L'\b', L"\\b", t, s)) return s;
        }
        // report it as \xXXXX (min)
        s.append(L"\\x");
        s.append(std::to_wstring((int)(*options.begin()).First));
        return s;
    }

    inline auto find_gaps_in_outbound_transitions(const std::vector<Transition> &transitions, std::vector<std::pair<wchar_t, wchar_t>> &gaps) -> void 
    {
        gaps.emplace_back((wchar_t)0, (wchar_t)WCHAR_MAX);
        for(auto &t : transitions) {
            exclude_char_range(t.First, t.Last, gaps);    
        }
    }

    auto valid_and_find_default_actions(logger *logger, dfa &dfa) -> bool
    {
        // Find the 'absolute final' states, and all state that can reach one of these states
        std::unordered_map<size_t, std::vector<std::pair<wchar_t, wchar_t>>> state_gaps;

        std::vector<size_t> absolute_final_unprocessed;
        std::unordered_multimap<size_t, size_t> inbound_states; // dest->sources
        for(auto &m : dfa.transitions) {
            // see whether this state is an absolute final
            std::vector<std::pair<wchar_t, wchar_t>> gaps;
            find_gaps_in_outbound_transitions(m.second, gaps);
            auto yield = dfa.actions.find(m.first);
            if (yield != dfa.actions.end() && yield->second.CanYield && !gaps.empty()) {
                // We're on a state that can yield, and there's gaps in the outbound, so some chars exist that will yield
                absolute_final_unprocessed.push_back(m.first);
                //std::wcout << L"State " << m.first << L" is absolute final" << std::endl;
                //yield->second.IsAbsoluteFinalState = true;
            }

            // record the gaps for later use
            state_gaps.emplace(m.first, std::move(gaps));

            // record the inbound states
            for(auto &t : m.second) {
                inbound_states.emplace(t.ToState, t.FromState);

                // See whether the ToState has any outbounds
                if (dfa.transitions.find(t.ToState) == dfa.transitions.end()) {
                    // No outbounds - one big gap
                    std::vector<std::pair<wchar_t, wchar_t>> gaps;
                    gaps.emplace_back((wchar_t)0, (wchar_t)WCHAR_MAX);
                    state_gaps.emplace(t.ToState, std::move(gaps));
                    auto y2 = dfa.actions.find(t.ToState);
                    if (y2 != dfa.actions.end() && y2->second.CanYield) {
                        absolute_final_unprocessed.push_back(t.ToState);
                        //std::wcout << L"State " << t.ToState << L" is absolute final" << std::endl;
                        //y2->second.IsAbsoluteFinalState = true;
                    }
                }
            }
        }

        std::set<size_t> absolute_final_reachable;
        while(!absolute_final_unprocessed.empty()) {
            auto s = absolute_final_unprocessed.back();
            absolute_final_unprocessed.pop_back();
            if (!absolute_final_reachable.emplace(s).second) continue;
            auto f = inbound_states.equal_range(s);
            for(auto i = f.first; i != f.second; i++) {
                absolute_final_unprocessed.push_back(i->second);
            }
        }

        struct state_details {
            size_t state;
            //int rewinds;
            //NfaAction rewind_action;
            std::wstring sample;
            containerspan *automata;
        };

        std::vector<state_details> unprocessed_states;
        unprocessed_states.push_back(state_details { 0, L"", &dfa.automataspns[0] });
        std::set<size_t> seen;

        bool ok = true;

        while(!unprocessed_states.empty()) {
            auto state = unprocessed_states.back();
            unprocessed_states.pop_back();
            if (!seen.emplace(state.state).second) continue;
            
            // See whether this is a 'trap' state (i.e.: cannot reach an 'absolute final state' from here
            if (absolute_final_reachable.find(state.state) == absolute_final_reachable.end()) {
                log::error::TrapState(logger, state.automata->cntr, state.automata->spn, state.sample);
                return false;
            }

            // See whether we've got a yield - if not, this is an error
            auto yield = dfa.actions.find(state.state);
            if (yield == dfa.actions.end()) {
                // There is no yield from this state.
                // If we can find gaps in the options out of this state, then
                // If we've already seen a yield (rewinds != -1) then we can rewind to that yield
                // If not, it's an error.
                auto f = dfa.transitions.find(state.state);

                // Find the dest states
                std::unordered_map<size_t, std::vector<Transition>> dest;
                if (f != dfa.transitions.end()) {
                    for(auto  &t : f->second) {
                        auto x = dest.emplace(t.ToState, std::vector<Transition>());
                        x.first->second.push_back(t);
                    }
                }

                // See what our state is
                    // We've got no state to rewind to - if there's gaps in the outbound then we've got an error
                    auto gf = state_gaps.find(f->first);
                    if (gf != state_gaps.end() && !gf->second.empty()) {
                        // We've got gaps
                        log::error::AutomataOutboundGaps(logger, state.automata->cntr, state.automata->spn, state.sample, gf->second);
                        ok = false;
                    }

                    for(auto &d : dest) {
                        unprocessed_states.push_back(state_details { d.first, get_sample(state.sample, d.second), state.automata });
                    }
            }
            else {
                // If the nfa action indicates a goto - then we need to process that automata also
                if (yield->second.YieldAction.IsGoto) {
                    unprocessed_states.push_back(state_details { yield->second.YieldAction.GotoAutomata, state.sample, &dfa.automataspns[yield->second.YieldAction.GotoAutomata] });
                }
                
                // Carry on to the next states
                auto f = dfa.transitions.find(state.state);
                std::unordered_map<size_t, std::vector<Transition>> dest;
                if (f != dfa.transitions.end()) {
                    for(auto  &t : f->second) {
                        auto x = dest.emplace(t.ToState, std::vector<Transition>());
                        x.first->second.push_back(t);
                    }
                    for(auto &d : dest) {
                        unprocessed_states.push_back(state_details { d.first, get_sample(state.sample, d.second), state.automata });
                    }
                }
            }
        }

        return ok;
    }
}




