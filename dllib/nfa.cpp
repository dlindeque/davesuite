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
                _nfa->_transition_table.emplace_back(1, nfa_transition_guard(nfa_transition_guard(0, 0)), 3, std::vector<nfa_transition_action>());
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
        auto tkn = _builder->_nfa->_tokens.find(token_name.value);
        if (tkn == _builder->_nfa->_tokens.end()) {
            log::error::re_token_not_found(_builder->_logger, _builder->_cntr, token_name.spn, token_name.value);
            return false;
        }
        std::vector<nfa_transition_action> actions;
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
        auto tkn = _builder->_nfa->_tokens.find(token_name.value);
        if (tkn == _builder->_nfa->_tokens.end()) {
            log::error::re_token_not_found(_builder->_logger, _builder->_cntr, token_name.spn, token_name.value);
            return false;
        }
        std::vector<nfa_transition_action> actions;
        actions.reserve(2);
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
        auto tkn = _builder->_nfa->_tokens.find(token_name.value);
        if (tkn == _builder->_nfa->_tokens.end()) {
            log::error::re_token_not_found(_builder->_logger, _builder->_cntr, token_name.spn, token_name.value);
            return false;
        }
        std::vector<nfa_transition_action> actions;
        actions.reserve(2);
        actions.emplace_back(false, L"", true, false, false, &(*tkn), 0);
        actions.emplace_back(false, L"", false, true, false, &(*tkn), 0);
        _builder->_nfa->_transition_table.emplace_back(to_state, nfa_transition_guard(), end(), std::move(actions));

        return ast->try_add_transitions(&(*tkn), _builder->_nfa->_named_asts, recurse(), to_state, _builder->_nfa->_transition_table, &ofslogger, _builder->_nfa->_next_state, true);
    }
}


