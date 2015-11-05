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
            // We take two states, the start state and the end state
            _nfa->_next_state += 2;
            _nfa->_section_init_states.emplace(name, anchor);
            // Add the epsilon transition from end to start (no action)
            _nfa->_transition_table.emplace_back(anchor + 1, nfa_transition_guard(), anchor, std::vector<nfa_transition_action>());
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

        // All transitions in a section will start at the anchor, then transition to a new state, then to the anchor+1 reducing the named token

        size_t to_state = _builder->_nfa->_next_state++;
        std::vector<nfa_transition_action> actions;
        actions.emplace_back(false, L"", true, false, false, token_name.value, 0);
        _builder->_nfa->_transition_table.emplace_back(to_state, nfa_transition_guard(), _anchor + 1, std::move(actions));
        
        return ast->try_add_transitions(_builder->_nfa->_named_asts, _anchor, to_state, _builder->_nfa->_transition_table, &ofslogger, _builder->_nfa->_next_state);
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
        // anchor ->re-> t -E->(reduce,goto) anchor+1

        size_t to_state = _builder->_nfa->_next_state++;
        std::vector<nfa_transition_action> actions;
        actions.emplace_back(false, L"", true, false, false, token_name.value, 0);
        actions.emplace_back(false, L"", false, false, true, L"", sb.anchor());
        _builder->_nfa->_transition_table.emplace_back(to_state, nfa_transition_guard(), _anchor + 1, std::move(actions));

        return ast->try_add_transitions(_builder->_nfa->_named_asts, _anchor, to_state, _builder->_nfa->_transition_table, &ofslogger, _builder->_nfa->_next_state);
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

        // anchor ->re-> t -E->(reduce,pop) anchor+1

        size_t to_state = _builder->_nfa->_next_state++;
        std::vector<nfa_transition_action> actions;
        actions.emplace_back(false, L"", true, false, false, token_name.value, 0);
        actions.emplace_back(false, L"", false, true, false, L"", 0);
        _builder->_nfa->_transition_table.emplace_back(to_state, nfa_transition_guard(), _anchor + 1, std::move(actions));

        return ast->try_add_transitions(_builder->_nfa->_named_asts, _anchor, to_state, _builder->_nfa->_transition_table, &ofslogger, _builder->_nfa->_next_state);
    }

    auto nfa::try_compile(bool &ok, std::wostream &errors) -> dfa {
        throw std::exception("not implemented");

        // 1. Split states so epsilon transition 'to state' have exits only (no inbound transitions must exist)
        // 2. Copy all epsilon transition's actions to the next transition's as a pre-action
        // 3. Build the DFA
    }

    auto nfa::strip_actions()->nfa
    {
        nfa n(_transition_table);

        //bool carry_on = true;
        //while (carry_on) {
        //    // Find an offending transition
        //    auto t = n._transition_table.begin();
        //    auto e = n._transition_table.end();
        //    carry_on = false;
        //    while (t != e) {
        //        if (t->guard().epsilon() && !t->actions().empty()) {
        //            // See whether this 'to state' has inbound transitions
        //            std::vector<
        //            for (auto &t2 : n._transition_table) {
        //                if (t2.to() == t->from()) {
        //                    has_inbound = true;
        //                }
        //            }
        //            // Found an offending transition
        //            carry_on = true;
        //            break;
        //        }
        //    }
        //}

        return n;
    }
}


