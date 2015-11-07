#include "stdafx.h"
#include "nfa.h"
#include "re_lexer.h"
#include "..\common\offset_logger.h"

namespace davelexer
{
    auto nfa_builder::get_section_builder(const std::wstring &name) -> nfa_section_builder {
        // Find the anchor state
        size_t anchor;
        auto f = _nfa->_section_init_states.find(name);
        if (f == _nfa->_section_init_states.end()) {
            anchor = _nfa->_next_state;
            // We take three states, the start state, the 'recurse' state and the end state
            _nfa->_next_state += 3;
            _nfa->_section_init_states.emplace(name, anchor);
            // Add the epsilon transition from end to recurse (no action)
            _nfa->_transition_table.emplace_back(anchor + 2, nfa_transition_guard(), anchor + 1, std::vector<nfa_transition_action>());
            // Add the epsilon transition from anchor to recurse
            _nfa->_transition_table.emplace_back(anchor, nfa_transition_guard(), anchor + 1, std::vector<nfa_transition_action>());
        }
        else {
            anchor = f->second;
        }
        return nfa_section_builder(this, anchor);
    }

    auto nfa_builder::try_add_binding(const token &binding_name, const token &binding_value) -> bool
    {
        offset_logger ofslogger(_logger, binding_value.spn);
        std::wstringstream stm;
        stm << binding_value.value;
        stm.seekg(0);
        std::unique_ptr<re_ast> ast;
        if (re_try_parse(_cntr, stm, &ofslogger, ast)) {
            _nfa->_named_asts.emplace(binding_name.value, std::move(ast));
            return true;
        }
        else {
            return false;
        }
    }

    auto nfa_section_builder::try_add_token(const token &token_name, const token &token_value)->bool
    {
        offset_logger ofslogger(_builder->_logger, token_value.spn);
        std::wstringstream stm;
        stm << token_value.value;
        stm.seekg(0);
        std::unique_ptr<re_ast> ast;
        if (!re_try_parse(_builder->_cntr, stm, &ofslogger, ast)) return false;
        if (ast->null_transition_possible(_builder->_nfa->_named_asts)) {
            log::error::re_must_process_something(_builder->_logger, _builder->_cntr, token_value.spn, token_name.value);
            return false;
        }

        // All transitions in a section will start at the recurse, then transition to a new state, then to the end reducing the named token

        size_t to_state = _builder->_nfa->_next_state++;

        // add the reduce action (to_state -> end)
        std::vector<nfa_transition_action> actions;
        actions.emplace_back(false, L"", true, false, false, token_name.value, 0);
        _builder->_nfa->_transition_table.emplace_back(to_state, nfa_transition_guard(), end(), std::move(actions));
        // add the re (recurse -> to_state)
        return ast->try_add_transitions(_builder->_nfa->_named_asts, recurse(), to_state, _builder->_nfa->_transition_table, &ofslogger, _builder->_nfa->_next_state);
    }

    auto nfa_section_builder::try_add_goto(const token &token_name, const token &token_value, const std::wstring &section_name) -> bool
    {
        offset_logger ofslogger(_builder->_logger, token_value.spn);
        std::wstringstream stm;
        stm << token_value.value;
        stm.seekg(0);
        std::unique_ptr<re_ast> ast;
        if (!re_try_parse(_builder->_cntr, stm, &ofslogger, ast)) return false;
        if (ast->null_transition_possible(_builder->_nfa->_named_asts)) {
            log::error::re_must_process_something(_builder->_logger, _builder->_cntr, token_value.spn, token_name.value);
            return false;
        }

        auto sb = _builder->get_section_builder(section_name);
        // recurse ->re-> t -E->(reduce,goto) end

        size_t to_state = _builder->_nfa->_next_state++;
        std::vector<nfa_transition_action> actions;
        actions.emplace_back(false, L"", true, false, false, token_name.value, 0);
        actions.emplace_back(false, L"", false, false, true, L"", sb.anchor());
        _builder->_nfa->_transition_table.emplace_back(to_state, nfa_transition_guard(), end(), std::move(actions));

        return ast->try_add_transitions(_builder->_nfa->_named_asts, recurse(), to_state, _builder->_nfa->_transition_table, &ofslogger, _builder->_nfa->_next_state);
    }

    auto nfa_section_builder::try_add_return(const token &token_name, const token &token_value) -> bool
    {
        offset_logger ofslogger(_builder->_logger, token_value.spn);
        std::wstringstream stm;
        stm << token_value.value;
        stm.seekg(0);
        std::unique_ptr<re_ast> ast;
        if (!re_try_parse(_builder->_cntr, stm, &ofslogger, ast)) return false;
        if (ast->null_transition_possible(_builder->_nfa->_named_asts)) {
            log::error::re_must_process_something(_builder->_logger, _builder->_cntr, token_value.spn, token_name.value);
            return false;
        }

        // recurse ->re-> t -E->(reduce,pop) end

        size_t to_state = _builder->_nfa->_next_state++;
        std::vector<nfa_transition_action> actions;
        actions.emplace_back(false, L"", true, false, false, token_name.value, 0);
        actions.emplace_back(false, L"", false, true, false, L"", 0);
        _builder->_nfa->_transition_table.emplace_back(to_state, nfa_transition_guard(), end(), std::move(actions));

        return ast->try_add_transitions(_builder->_nfa->_named_asts, recurse(), to_state, _builder->_nfa->_transition_table, &ofslogger, _builder->_nfa->_next_state);
    }

    auto nfa::try_compile(bool &ok, std::wostream &errors) -> dfa {
        throw std::exception("not implemented");

        // 1. Split states so epsilon transition 'to state' have exits only (no inbound transitions must exist)
        // 2. Copy all epsilon transition's actions to the next transition's as a pre-action
        // 3. Build the DFA
    }

#ifdef _DEBUG
    auto assert_valid_nfa(const std::vector<nfa_transition> &transitions) -> void
    {
        // Ensure we don't have any recursive epsilon transitions
        std::set<size_t> states;
        for(auto &t : transitions) {
            states.emplace(t.from());
        }
        for (auto &s : states) {
        }
    }
#else
    inline auto assert_valid_nfa(const std::vector<nfa_transition>&) -> void {}
#endif

    auto nfa::remove_epsilon_actions()->nfa
    {
        assert_valid_nfa(_transition_table);
        nfa n(_transition_table);
        n._next_state = _next_state;

        std::vector<size_t> unprocessed;
        for (size_t i = 0; i < n._transition_table.size();i++) {
            if (n._transition_table[i].guard().epsilon() && !n._transition_table[i].actions().empty()) {
                unprocessed.push_back(i);
            }
        }

        while (!unprocessed.empty()) {
            auto p = unprocessed.back();
            unprocessed.pop_back();

            std::vector<size_t> inbound;
            inbound.reserve(10);
            for (size_t i = 0; i < n._transition_table.size(); i++) {
                if (&n._transition_table[i] != &n._transition_table[p] && n._transition_table[i].to() == n._transition_table[p].to()) {
                    inbound.push_back(i);
                }
            }

            if (!inbound.empty()) {
                // Found an epsilon transition with some actions and some inbound transitions (all states will always have at least one outbound transition)
                auto state = n._transition_table[p].to();
                auto &actions = n._transition_table[p].actions();
                std::vector<nfa_transition> new_txs;
                while (!inbound.empty()) {
                    auto p = inbound.back();
                    inbound.pop_back();
                    // Clone the state - copy all transitions from the original state
                    size_t new_state = n._next_state++;
                    for (auto &ct : n._transition_table) {
                        if (ct.from() == n._transition_table[p].to()) {
                            // ct is a transition from the state in question to some other, or same state
                            if (ct.from() == ct.to()) {
                                // recursive transition - copy the while thing
                                new_txs.emplace_back(new_state, ct.guard(), new_state, ct.actions());
                            }
                            else {
                                // not a recursive state - copy only the the 'to'
                                new_txs.emplace_back(new_state, ct.guard(), ct.to(), ct.actions());
                            }
                        }
                    }
                    // Setup a new transition
                    n._transition_table[p].to(new_state);
                }
                // Move the epsilon transition's action(s) to the outbound transitions
                for (auto &o : n._transition_table) {
                    if (o.from() == state) {
                        for (auto &ea : actions) {
                            o.actions().insert(o.actions().cbegin(), ea);
                        }
                    }
                }
                actions.clear();
                for (auto &ct : new_txs) {
                    n._transition_table.push_back(std::move(ct));
                }
                break;
            }
            else {
                t++;
            }
        }


        return n;
    }
}


