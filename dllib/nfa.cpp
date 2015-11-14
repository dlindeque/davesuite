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
            _nfa->_transition_table.emplace_back(anchor + 2, nfa_transition_guard(), anchor + 1, std::vector<transition_action>());
            // Add the <eod> transition
            if (anchor == 0) {
                _nfa->_transition_table.emplace_back(1, nfa_transition_guard(nfa_transition_guard(0, 0)), 3, std::vector<transition_action>());
            }
            // Add the epsilon transition from anchor to recurse
            _nfa->_transition_table.emplace_back(anchor, nfa_transition_guard(), anchor + 1, std::vector<transition_action>());
        }
        else {
            anchor = f->second;
        }
        return nfa_section_builder(this, anchor);
    }

    auto nfa_builder::try_add_binding(const std::wstring &binding_name, std::wistream &text, span text_spn) -> bool
    {
        offset_logger ofslogger(_logger, text_spn);
        std::unique_ptr<re_ast> ast;
        if (re_try_parse(_cntr, text, &ofslogger, ast)) {
            _nfa->_named_asts.emplace(binding_name, std::move(ast));
            return true;
        }
        else {
            return false;
        }
    }

    auto nfa_section_builder::try_add_token(const std::wstring &tkn_name, size_t tkn, std::wistream &text, span text_spn)->bool
    {
        offset_logger ofslogger(_builder->_logger, text_spn);
        std::unique_ptr<re_ast> ast;
        if (!re_try_parse(_builder->_cntr, text, &ofslogger, ast)) return false;
        if (ast->null_transition_possible(_builder->_nfa->_named_asts)) {
            log::error::re_must_process_something(_builder->_logger, _builder->_cntr, text_spn, tkn_name);
            return false;
        }

        // All transitions in a section will start at the recurse, then transition to a new state, then to the end reducing the named token

        size_t to_state = _builder->_nfa->_next_state++;

        std::vector<transition_action> actions;
        actions.emplace_back(false, std::wstring(), true, false, false, tkn, 0);
        _builder->_nfa->_transition_table.emplace_back(to_state, nfa_transition_guard(), end(), std::move(actions));
        // add the re (recurse -> to_state)
        return ast->try_add_transitions(tkn, _builder->_nfa->_named_asts, recurse(), to_state, _builder->_nfa->_transition_table, &ofslogger, _builder->_nfa->_next_state, true);
    }

    auto nfa_section_builder::try_add_goto(const std::wstring &tkn_name, size_t tkn, std::wistream &text, span text_spn, const std::wstring &section_name) -> bool
    {
        offset_logger ofslogger(_builder->_logger, text_spn);
        std::unique_ptr<re_ast> ast;
        if (!re_try_parse(_builder->_cntr, text, &ofslogger, ast)) return false;
        if (ast->null_transition_possible(_builder->_nfa->_named_asts)) {
            log::error::re_must_process_something(_builder->_logger, _builder->_cntr, text_spn, tkn_name);
            return false;
        }

        auto sb = _builder->get_section_builder(section_name);
        // recurse ->re-> t -E->(yield,goto) end

        size_t to_state = _builder->_nfa->_next_state++;
        std::vector<transition_action> actions;
        actions.reserve(2);
        actions.emplace_back(false, std::wstring(), true, false, false, tkn, 0);
        actions.emplace_back(false, std::wstring(), false, false, true, tkn, sb.anchor());
        _builder->_nfa->_transition_table.emplace_back(to_state, nfa_transition_guard(), end(), std::move(actions));

        return ast->try_add_transitions(tkn, _builder->_nfa->_named_asts, recurse(), to_state, _builder->_nfa->_transition_table, &ofslogger, _builder->_nfa->_next_state, true);
    }

    auto nfa_section_builder::try_add_return(const std::wstring &tkn_name, size_t tkn, std::wistream &text, span text_spn) -> bool
    {
        offset_logger ofslogger(_builder->_logger, text_spn);
        std::unique_ptr<re_ast> ast;
        if (!re_try_parse(_builder->_cntr, text, &ofslogger, ast)) return false;
        if (ast->null_transition_possible(_builder->_nfa->_named_asts)) {
            log::error::re_must_process_something(_builder->_logger, _builder->_cntr, text_spn, tkn_name);
            return false;
        }

        // recurse ->re-> t -E->(yield,pop) end

        size_t to_state = _builder->_nfa->_next_state++;

        std::vector<transition_action> actions;
        actions.reserve(2);
        actions.emplace_back(false, std::wstring(), true, false, false, tkn, 0);
        actions.emplace_back(false, std::wstring(), false, true, false, tkn, 0);
        _builder->_nfa->_transition_table.emplace_back(to_state, nfa_transition_guard(), end(), std::move(actions));

        return ast->try_add_transitions(tkn, _builder->_nfa->_named_asts, recurse(), to_state, _builder->_nfa->_transition_table, &ofslogger, _builder->_nfa->_next_state, true);
    }
}


