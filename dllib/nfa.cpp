#include "stdafx.h"

#include <assert.h>

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
            if (anchor == 0) {
                // For the first machine, we also and an ultimate final state, we get there when we see <eod>
                _nfa->_next_state += 4;
            }
            else {
                _nfa->_next_state += 3;
            }
            _nfa->_section_init_states.emplace(name, anchor);
            // Add the epsilon transition from end to recurse (no action)
            _nfa->_transition_table.emplace_back(anchor + 2, nfa_transition_guard(), anchor + 1, std::vector<nfa_transition_action>());
            // Add the <eod> transition
            if (anchor == 0) {
                _nfa->_transition_table.emplace_back(1, nfa_transition_guard(nfa_transition_guard(false, 0, 0)), 3, std::vector<nfa_transition_action>());
            }
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
        auto tkn = _builder->_nfa->_tokens.find(token_name.value);
        if (tkn == _builder->_nfa->_tokens.end()) {
            log::error::re_token_not_found(_builder->_logger, _builder->_cntr, token_name.spn, token_name.value);
            return false;
        }
        actions.emplace_back(false, L"", true, false, false, &(*tkn), 0);
        _builder->_nfa->_transition_table.emplace_back(to_state, nfa_transition_guard(), end(), std::move(actions));
        // add the re (recurse -> to_state)
        return ast->try_add_transitions(&(*tkn), _builder->_nfa->_named_asts, recurse(), to_state, _builder->_nfa->_transition_table, &ofslogger, _builder->_nfa->_next_state, true);
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
        auto tkn = _builder->_nfa->_tokens.find(token_name.value);
        if (tkn == _builder->_nfa->_tokens.end()) {
            log::error::re_token_not_found(_builder->_logger, _builder->_cntr, token_name.spn, token_name.value);
            return false;
        }
        actions.emplace_back(false, L"", true, false, false, &(*tkn), 0);
        actions.emplace_back(false, L"", false, false, true, &(*tkn), sb.anchor());
        _builder->_nfa->_transition_table.emplace_back(to_state, nfa_transition_guard(), end(), std::move(actions));

        return ast->try_add_transitions(&(*tkn), _builder->_nfa->_named_asts, recurse(), to_state, _builder->_nfa->_transition_table, &ofslogger, _builder->_nfa->_next_state, true);
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
        auto tkn = _builder->_nfa->_tokens.find(token_name.value);
        if (tkn == _builder->_nfa->_tokens.end()) {
            log::error::re_token_not_found(_builder->_logger, _builder->_cntr, token_name.spn, token_name.value);
            return false;
        }
        actions.emplace_back(false, L"", true, false, false, &(*tkn), 0);
        actions.emplace_back(false, L"", false, true, false, &(*tkn), 0);
        _builder->_nfa->_transition_table.emplace_back(to_state, nfa_transition_guard(), end(), std::move(actions));

        return ast->try_add_transitions(&(*tkn), _builder->_nfa->_named_asts, recurse(), to_state, _builder->_nfa->_transition_table, &ofslogger, _builder->_nfa->_next_state, true);
    }

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

    auto nfa::try_compile(std::wostream &errors) -> bool
    {
        bool ok = true;

#pragma region Clear Epsilon Transitions Of Actions

        std::vector<size_t> unprocessed;
        for (size_t i = 0; i < _transition_table.size(); i++) {
            if (_transition_table[i].guard().epsilon() && !_transition_table[i].actions().empty()) {
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
            for (size_t i = 0; i < _transition_table.size(); i++) {
                if (&_transition_table[i] != &_transition_table[p] && _transition_table[i].to() == _transition_table[p].to()) {
                    inbound.push_back(i); // include recursive transitions
                }
                if (_transition_table[i].from() == _transition_table[p].to()) {
                    if (_transition_table[i].from() != _transition_table[i].to())
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
                size_t new_state = _next_state++;
                // Change the transition to point to the new state
                _transition_table[ip].to(new_state);
                // Clone the state - copy all outbound transitions
                for (auto &o : outbound) {
                    auto g = _transition_table[o].guard();
                    _transition_table.push_back(nfa_transition(new_state, g, _transition_table[o].to(), _transition_table[o].actions()));
                }
                // Also copy all recursive transitions
                for (auto &r : recursive) {
                    _transition_table.emplace_back(new_state, _transition_table[r].guard(), new_state, _transition_table[r].actions());
                }
            }
            // Move the epsilon transition's action(s) to the outbound transitions
            for (auto &o : outbound) {
                for (auto &a : _transition_table[p].actions()) {
                    _transition_table[o].actions().insert(_transition_table[o].actions().cbegin(), a);
                }
                // check the output transitions, if it's a transition that qualifies for processing, then enqueue it.
                if (_transition_table[o].guard().epsilon() && !_transition_table[o].actions().empty()) {
                    unprocessed.push_back(o);
                }
            }
            _transition_table[p].actions().clear();
        }

        assert_valid_nfa_1(_transition_table);
        assert_valid_nfa_2(_transition_table);

#pragma endregion

#pragma region Delete Epsilon Transitions
        std::vector<size_t> epsilon_transitions;
        for (size_t i = 0; i < _transition_table.size(); i++) {
            if (_transition_table[i].guard().epsilon()) {
                epsilon_transitions.push_back(i);
            }
        }

        size_t i = 0;
        while (i < epsilon_transitions.size()) {
            auto t = epsilon_transitions[i];
            auto &et = _transition_table[t];
            std::vector<nfa_transition> new_txs;
            for (auto &t : _transition_table) {
                if (et.to() == t.from()) {
                    new_txs.emplace_back(et.from(), t.guard(), t.to(), t.actions());
                }
            }
            for (auto &t : new_txs) {
                if (t.guard().epsilon()) {
                    epsilon_transitions.push_back(_transition_table.size());
                }
                _transition_table.push_back(std::move(t));
            }
            i++;
        }

        for (auto it = epsilon_transitions.rbegin(); it != epsilon_transitions.rend(); it++) {
            _transition_table.erase(_transition_table.begin() + *it);
        }

        assert_valid_nfa_3(_transition_table);

#pragma endregion

        return ok;
    }
}


