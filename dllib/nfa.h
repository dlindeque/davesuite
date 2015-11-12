#pragma once

#include <string>
#include <memory>
#include <ostream>
#include <istream>
#include <map>
#include <set>
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

    class dfa;

    class nfa sealed {
    private:
        std::set<std::wstring> _tokens;
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
        {
            _transition_table.reserve(256);
        }
        nfa(const nfa &) = delete;
        nfa(nfa &&c)
            : _next_state(c._next_state), _transition_table(std::move(c._transition_table)), _section_init_states(std::move(c._section_init_states)), _named_asts(std::move(c._named_asts))
        {}

        inline auto add_token(const std::wstring &token) -> nfa& {
            _tokens.emplace(token);
            return *this;
        }
        inline auto get_builder(container *cntr, logger *logger) -> nfa_builder {
            return nfa_builder(this, cntr, logger);
        }

        inline auto test_add(size_t from, wchar_t first, wchar_t last, size_t to, const std::wstring *tkn) -> void {
            std::vector<nfa_transition_action> actions;
            _transition_table.emplace_back(from, nfa_transition_guard(first, last), to, std::move(actions));
        }

        static auto test(nfa &n) -> void {
            n.add_token(L"x");
            auto tkn = &(*n._tokens.find(L"x"));
            n._next_state = 3;
            n.test_add(0, L'a', L'e', 1, tkn);
            n.test_add(0, L'c', L'g', 2, tkn);
        }

        friend auto operator << (std::wostream &os, const nfa &nfa) -> std::wostream& {
            os << L"digraph nfa{" << std::endl;
            for (auto &t : nfa._transition_table) {
                os << L"  \"" << t.from() << L"\"->\"" << t.to() << L"\" [label=\"";
                if (t.guard().epsilon()) {
                    os << L".";
                }
                else {
                    if (t.guard().first() == 0 && t.guard().last() == WCHAR_MAX) {
                        os << L"<any>";
                    }
                    else if (t.guard().first() == t.guard().last() && t.guard().first() != 0) {
                        os << t.guard().first();
                    }
                    else if (t.guard().first() == t.guard().last() && t.guard().first() == 0) {
                        os << L"<eod>";
                    }
                    else {
                        os << t.guard().first() << L"-" << t.guard().last();
                    }
                }
                std::set<const std::wstring*> tokens;
                for (auto &a : t.actions()) {
                    tokens.emplace(a.reduce_token());
                }
                for (auto &tkn : tokens) {
                    bool got_actions = false;
                    for (auto &a : t.actions()) {
                        if (a.reduce_token() == tkn) {
                            got_actions |= a.pop() || a.push() || a.reduce() || !a.output_matched();
                            if (got_actions) break;
                        }
                    }
                    if (got_actions) {
                        os << L" '" << *tkn << L"'(";
                        for (auto &a : t.actions()) {
                            if (a.reduce_token() == tkn) {
                                if (a.pop()) {
                                    os << L" p";
                                }
                                else if (a.push()) {
                                    os << L" g " << a.goto_state();
                                }
                                else if (a.reduce()) {
                                    os << L" r";
                                }
                                if (!a.output_matched()) {
                                    os << L" o '" << a.output_alternate() << "'";
                                }
                            }
                        }
                        os << L')';
                    }
                }
                os << L"\"]" << std::endl;
            }
            os << L"}" << std::endl;

            return os;
        }

        friend nfa_builder;
        friend nfa_section_builder;
        friend dfa;
    };
}