﻿#pragma once

#include <string>
#include <memory>
#include <ostream>
#include <istream>
#include <map>
#include <set>
#include "dfa.h"
#include "re_parser.h"
#include "lexer.h"

namespace davelexer
{
    class nfa_builder;

    class nfa_section_builder sealed {
    private:
        nfa_builder *_builder;
        size_t _anchor;
        nfa_section_builder(nfa_builder *builder, const size_t &anchor)
            : _builder(builder), _anchor(anchor)
        {}
    public:
        nfa_section_builder() = delete;
        nfa_section_builder(const nfa_section_builder &c)
            : _builder(c._builder), _anchor(c._anchor)
        {}
        nfa_section_builder(nfa_section_builder &&c)
            : _builder(c._builder), _anchor(c._anchor)
        {}

        inline auto anchor() const -> size_t { return _anchor; }
        inline auto recurse() const->size_t{ return _anchor + 1; }
        inline auto end() const -> size_t{ return _anchor + 2; }

        auto try_add_token(const token &token_name, const token &token_value) -> bool;
        auto try_add_goto(const token &token_name, const token &token_value, const std::wstring &section_name) -> bool;
        auto try_add_return(const token &token_name, const token &token_value) -> bool;

        friend nfa_builder;
    };

    class nfa;

    class nfa_builder sealed {
    private:
        nfa *_nfa;
        container *_cntr;
        logger *_logger;
        nfa_builder(nfa *nfa, container *cntr, logger *logger)
            : _nfa(nfa), _cntr(cntr), _logger(logger)
        {}
    public:
        nfa_builder() = delete;
        nfa_builder(const nfa_builder &c)
            : _nfa(c._nfa), _cntr(c._cntr), _logger(c._logger)
        {}
        nfa_builder(nfa_builder &&c)
            : _nfa(c._nfa), _cntr(c._cntr), _logger(c._logger)
        {}

        auto get_section_builder(const std::wstring &name)->nfa_section_builder;

        auto try_add_binding(const token &binding_name, const token &binding_value) -> bool;

        friend nfa;
        friend nfa_section_builder;
    };

    class nfa sealed {
    private:
        std::vector<nfa_transition> _transition_table;
        std::map<std::wstring, size_t> _section_init_states;
        size_t _next_state;
        std::map<std::wstring, std::unique_ptr<re_ast>> _named_asts;
        nfa(const std::vector<nfa_transition> &transition_table)
            : _transition_table(transition_table)
        {}
    public:
        nfa()
            : _next_state(0)
        {}
        nfa(const nfa &) = delete;
        nfa(nfa &&c)
            : _next_state(c._next_state), _transition_table(std::move(c._transition_table)), _section_init_states(std::move(c._section_init_states)), _named_asts(std::move(c._named_asts))
        {}

        auto remove_epsilon_actions()->nfa;

        auto try_compile(bool &good, std::wostream &errors)->dfa;

        inline auto get_builder(container *cntr, logger *logger) -> nfa_builder {
            return nfa_builder(this, cntr, logger);
        }

        friend auto operator << (std::wostream &os, const nfa &nfa) -> std::wostream& {
            os << L"digraph nfa{" << std::endl;
            for (auto &t : nfa._transition_table) {
                os << L"  \"" << t.from() << L"\"->\"" << t.to() << L"\" [label=\"";
                if (t.guard().epsilon()) {
                    os << L".";
                }
                else {
                    if (t.guard().exclude()) {
                        os << L"- ";
                    }
                    if (t.guard().first() == 0 && t.guard().last() == WCHAR_MAX) {
                        os << L"<any>";
                    }
                    else if (t.guard().first() == t.guard().last()) {
                        os << t.guard().first();
                    }
                    else {
                        os << t.guard().first() << L"-" << t.guard().last();
                    }
                }
                bool got_actions = false;
                for (auto &a : t.actions()) {
                    got_actions |= a.pop() || a.push() || a.reduce() || !a.output_matched();
                    if (got_actions) break;
                }
                if (got_actions) {
                    os << L" (";
                    for (auto &a : t.actions()) {
                        if (a.pop()) {
                            os << L" p";
                        }
                        else if (a.push()) {
                            os << L" g " << a.goto_state();
                        }
                        else if (a.reduce()) {
                            os << L" r '" << a.reduce_token() << "'";
                        }
                        if (!a.output_matched()) {
                            os << L" o '" << a.output_alternate() << "'";
                        }
                    }
                    os << L')';
                }
                os << L"\"]" << std::endl;
            }
            os << L"}" << std::endl;

            return os;
        }

        friend nfa_builder;
        friend nfa_section_builder;

        static inline auto test() -> nfa {
            nfa n;
            std::vector<nfa_transition_action> actions;
            actions.emplace_back(false, L"a", false, false, false, L"", 0);
            n._transition_table.emplace_back(0, nfa_transition_guard(), 1, std::move(actions));
            actions.emplace_back(false, L"b", false, false, false, L"", 0);
            n._transition_table.emplace_back(2, nfa_transition_guard(false, L'b', L'b'), 1, std::move(actions));
            actions.emplace_back(false, L"c", false, false, false, L"", 0);
            n._transition_table.emplace_back(3, nfa_transition_guard(false, L'c', L'c'), 1, std::move(actions));
            actions.emplace_back(false, L"d", false, false, false, L"", 0);
            n._transition_table.emplace_back(1, nfa_transition_guard(false, L'd', L'd'), 1, std::move(actions));
            actions.emplace_back(false, L"e", false, false, false, L"", 0);
            n._transition_table.emplace_back(1, nfa_transition_guard(false, L'e', L'e'), 1, std::move(actions));
            actions.emplace_back(false, L"f", false, false, false, L"", 0);
            n._transition_table.emplace_back(1, nfa_transition_guard(false, L'f', L'f'), 4, std::move(actions));
            actions.emplace_back(false, L"g", false, false, false, L"", 0);
            n._transition_table.emplace_back(1, nfa_transition_guard(false, L'g', L'g'), 5, std::move(actions));
            n._next_state = 6;
            return n;
        }
    };
}