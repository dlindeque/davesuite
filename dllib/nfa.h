#pragma once

#include <string>
#include <memory>
#include <ostream>
#include <istream>
#include <map>
#include <set>
#include <sstream>
#include "re_parser.h"

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

        auto try_add_token(const std::wstring &tkn_name, size_t tkn, std::wistream &text, span text_spn) -> bool;
        inline auto try_add_token(const std::wstring &tkn_name, size_t tkn, const std::wstring &text, span text_spn) -> bool {
            std::wstringstream stm;
            stm << text;
            stm.seekg(0);
            return try_add_token(tkn_name, tkn, stm, text_spn);
        }
        auto try_add_goto(const std::wstring &tkn_name, size_t tkn, std::wistream &text, span text_spn, const std::wstring &section_name) -> bool;
        inline auto try_add_goto(const std::wstring &tkn_name, size_t tkn, const std::wstring &text, span text_spn, const std::wstring &section_name) -> bool {
            std::wstringstream stm;
            stm << text;
            stm.seekg(0);
            return try_add_goto(tkn_name, tkn, stm, text_spn, section_name);
        }
        auto try_add_return(const std::wstring &tkn_name, size_t tkn, std::wistream &text, span text_spn) -> bool;
        inline auto try_add_return(const std::wstring &tkn_name, size_t tkn, const std::wstring &text, span text_spn) -> bool {
            std::wstringstream stm;
            stm << text;
            stm.seekg(0);
            return try_add_return(tkn_name, tkn, stm, text_spn);
        }

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

        auto try_add_binding(const std::wstring &binding_name, std::wistream &text, span text_spn) -> bool;
        inline auto try_add_binding(const std::wstring &binding_name, const std::wstring &text, span text_spn) -> bool {
            std::wstringstream stm;
            stm << text;
            stm.seekg(0);
            return try_add_binding(binding_name, stm, text_spn);
        }

        friend nfa;
        friend nfa_section_builder;
    };

    class dfa;

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
        {
            _transition_table.reserve(256);
        }
        nfa(const nfa &) = delete;
        nfa(nfa &&c)
            : _next_state(c._next_state), _transition_table(std::move(c._transition_table)), _section_init_states(std::move(c._section_init_states)), _named_asts(std::move(c._named_asts))
        {}

        inline auto get_builder(container *cntr, logger *logger) -> nfa_builder {
            return nfa_builder(this, cntr, logger);
        }

        inline auto test_add(size_t from, wchar_t first, wchar_t last, size_t to, size_t tkn) -> void {
            std::vector<transition_action> actions;
            _transition_table.emplace_back(from, nfa_transition_guard(first, last), to, std::move(actions));
        }

        static auto test(nfa &n) -> void {
            size_t tkn = 1;
            n._next_state = 3;
            n.test_add(0, L'a', L'z', 1, tkn);
            n.test_add(0, L'c', L'd', 2, tkn);
            //n.test_add(0, L'b', L'b', 3, tkn);
            //n.test_add(1, L'c', L'c', 4, tkn);
            //n.test_add(1, L'd', L'd', 5, tkn);
            //n.test_add(2, L'c', L'c', 6, tkn);
            //n.test_add(2, L'e', L'e', 7, tkn);
            //n.test_add(3, L'c', L'c', 8, tkn);
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
                std::set<size_t> tokens;
                for (auto &a : t.actions()) {
                    tokens.emplace(a.yield_token());
                }
                for (auto &tkn : tokens) {
                    bool got_actions = false;
                    for (auto &a : t.actions()) {
                        if (a.yield_token() == tkn) {
                            got_actions |= a.pop() || a.push() || a.yield() || a.output_matched() || !a.output_alternate().empty();
                            if (got_actions) break;
                        }
                    }
                    if (got_actions) {
                        os << L" " << (int)tkn << L"(";
                        for (auto &a : t.actions()) {
                            if (a.yield_token() == tkn) {
                                if (a.pop()) {
                                    os << L" p";
                                }
                                else if (a.push()) {
                                    os << L" g " << a.goto_state();
                                }
                                else if (a.yield()) {
                                    os << L" y";
                                }
                                if (a.output_matched()) {
                                    os << L" m";
                                }
                                else {
                                    if (!a.output_alternate().empty()) {
                                        os << L" o '" << a.output_alternate() << "'";
                                    }
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