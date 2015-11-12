#pragma once

#include <istream>
#include <memory>
#include <vector>
#include <map>
#include "re_lexer.h"

#include "..\common\logger.h"
#include "log.h"

using namespace davecommon;

namespace davelexer
{
    class nfa_transition_guard {
    private:
        bool _epsilon;
        wchar_t _first;
        wchar_t _last;
    public:
        nfa_transition_guard(const nfa_transition_guard &c)
            : _epsilon(c._epsilon), _first(c._first), _last(c._last)
        {}
        nfa_transition_guard(nfa_transition_guard &&c)
            : _epsilon(c._epsilon), _first(std::move(c._first)), _last(std::move(c._last))
        {}
        nfa_transition_guard()
            : _epsilon(true)
        {}
        nfa_transition_guard(const wchar_t &first, const wchar_t &last)
            : _epsilon(false), _first(first), _last(last)
        {}

        inline auto epsilon() const -> bool { return _epsilon; }
        inline auto first() const -> wchar_t { return _first; }
        inline auto last() const -> wchar_t { return _last; }
    };

    class nfa_transition_action {
    private:
        bool _output_matched;
        std::wstring _output_alternate;
        bool _reduce;
        bool _pop;
        bool _push;
        const std::wstring* _reduce_token;
        size_t _goto;
    public:
        nfa_transition_action() = delete;
        nfa_transition_action(const nfa_transition_action&c)
            : _output_matched(c._output_matched), _output_alternate(c._output_alternate), _reduce(c._reduce), _pop(c._pop), _push(c._push), _reduce_token(c._reduce_token), _goto(c._goto)
        {}
        nfa_transition_action(nfa_transition_action &&c)
            : _output_matched(c._output_matched), _output_alternate(std::move(c._output_alternate)), _reduce(c._reduce), _pop(c._pop), _push(c._push), _reduce_token(std::move(c._reduce_token)), _goto(c._goto)
        {}
        nfa_transition_action(bool output_matched, const std::wstring &output_alternate, bool reduce, bool pop, bool push, const std::wstring *reduce_token, size_t goto_)
            : _output_matched(output_matched), _output_alternate(output_alternate), _reduce(reduce), _pop(pop), _push(push), _reduce_token(reduce_token), _goto(goto_)
        {}
        nfa_transition_action(bool output_matched, std::wstring &&output_alternate, bool reduce, bool pop, bool push, const std::wstring *reduce_token, size_t goto_)
            : _output_matched(output_matched), _output_alternate(std::move(output_alternate)), _reduce(reduce), _pop(pop), _push(push), _reduce_token(reduce_token), _goto(goto_)
        {}

        inline auto output_matched() const -> bool { return _output_matched; }
        inline auto output_alternate() const -> const std::wstring&{ return _output_alternate; }
        inline auto reduce() const -> bool { return _reduce; }
        inline auto pop() const -> bool { return _pop; }
        inline auto push() const -> bool { return _push; }
        inline auto reduce_token() const -> const std::wstring* { return _reduce_token; }
        inline auto goto_state() const -> size_t { return _goto; }
    };

    class nfa_transition {
    private:
        size_t _from;
        nfa_transition_guard _guard;       
        size_t _to;
        std::vector<nfa_transition_action> _actions;
    public:
        nfa_transition() = delete;
        nfa_transition(const nfa_transition &c)
            : _from(c._from), _guard(c._guard), _to(c._to), _actions(c._actions)
        {}
        nfa_transition(nfa_transition &&c)
            : _from(c._from), _guard(std::move(c._guard)), _to(c._to), _actions(std::move(c._actions))
        {}
        nfa_transition(size_t from, nfa_transition_guard &&guard, size_t to, std::vector<nfa_transition_action> &&actions)
            : _from(from), _guard(std::move(guard)), _to(to), _actions(std::move(actions))
        {}
        nfa_transition(size_t from, const nfa_transition_guard &guard, size_t to, std::vector<nfa_transition_action> &&actions)
            : _from(from), _guard(guard), _to(to), _actions(std::move(actions))
        {}
        nfa_transition(size_t from, nfa_transition_guard &&guard, size_t to, const std::vector<nfa_transition_action> &actions)
            : _from(from), _guard(std::move(guard)), _to(to), _actions(actions)
        {}
        nfa_transition(size_t from, const nfa_transition_guard &guard, size_t to, const std::vector<nfa_transition_action> &actions)
            : _from(from), _guard(guard), _to(to), _actions(actions)
        {}

        inline auto from() const -> size_t { return _from; }
        inline auto from(size_t value) -> void { _from = value; }
        inline auto to() const -> size_t { return _to; }
        inline auto to(size_t value) -> void { _to = value; }
        inline auto guard() const -> const nfa_transition_guard& { return _guard; }
        inline auto actions() const -> const std::vector<nfa_transition_action>& { return _actions; }
        inline auto actions() -> std::vector<nfa_transition_action>& { return _actions; }
    };

    class re_ast abstract {
    private:
        const container *_cntr;
        span _spn;
    protected:
        bool _output = true;
        virtual auto write(std::wostream &os) const->std::wostream& = 0;
    public:
        re_ast() = delete;
        re_ast(const re_ast &) = delete;
        re_ast(re_ast &&c)
            : _spn(std::move(c._spn))
        {}
        re_ast(const container *cntr, const span &spn)
            : _cntr(cntr), _spn(spn)
        {}
        re_ast(const container *cntr, const span &&spn)
            : _cntr(cntr), _spn(std::move(spn))
        {}
        virtual ~re_ast() {}

        inline auto spn() const -> const span&{ return _spn; }
        inline auto cntr() const -> const container*{ return _cntr; }

        inline auto remove_output() -> void {
            _output = false;
        }

        virtual auto try_add_transitions(const std::wstring* token, const std::map<std::wstring, std::unique_ptr<re_ast>> &named, size_t from_state, size_t to_state, std::vector<nfa_transition> &table, logger *logger, size_t &next_state, bool allow_output) -> bool = 0;

        virtual auto null_transition_possible(const std::map<std::wstring, std::unique_ptr<re_ast>> &named) const -> bool = 0;

        friend auto operator << (std::wostream &os, const re_ast &ast) -> std::wostream& {
            return ast.write(os);
        }
        friend auto operator << (std::wostream &os, const std::unique_ptr<re_ast> &ast) -> std::wostream& {
            if (ast == nullptr) {
                return os << L"NULL";
            }
            else {
                return ast->write(os);
            }
        }
    };

    struct char_range {
        wchar_t from;
        wchar_t to;
    };

    class re_ast_char_set_match sealed : public re_ast{
    private:
        bool _exclude;
        std::vector<char_range> _ranges;
    protected:
        virtual auto write(std::wostream &os) const ->std::wostream& override {
            if (_exclude) {
                os << L"[^";
            }
            else {
                if (_ranges.size() == 1 && _ranges[0].from == 0 && _ranges[0].to == WCHAR_MAX) {
                    return os << L'.';
                }
                if (_ranges.size() != 1 || _ranges[0].from != _ranges[0].to) {
                    os << L'[';
                }
            }
            for (auto &r : _ranges) {
                if (r.from == r.to) {
                    char_friendly(r.from, os);
                }
                else {
                    if (r.from == 0 && r.to == WCHAR_MAX) {
                        os << L"<any>";
                    }
                    else {
                        char_friendly(r.from, os) << L'-';
                        char_friendly(r.to, os);
                    }
                }
            }
            if (_exclude || _ranges.size() != 1 || _ranges[0].from != _ranges[0].to) {
                return os << L']';
            }
            else {
                return os;
            }
        }
    public:
        re_ast_char_set_match() = delete;
        re_ast_char_set_match(const re_ast_char_set_match &) = delete;
        re_ast_char_set_match(re_ast_char_set_match &&c)
            : re_ast(std::move(c)), _exclude(c._exclude), _ranges(std::move(c._ranges))
        {}
        re_ast_char_set_match(const container *cntr, const span &spn, bool exclude, std::vector<char_range> &&ranges)
            : re_ast(cntr, spn), _exclude(exclude), _ranges(std::move(ranges))
        {}
        re_ast_char_set_match(const container *cntr, span &&spn, bool exclude, std::vector<char_range> &&ranges)
            : re_ast(cntr, std::move(spn)), _exclude(exclude), _ranges(std::move(ranges))
        {}
        virtual ~re_ast_char_set_match() {}

        virtual auto try_add_transitions(const std::wstring* token, const std::map<std::wstring, std::unique_ptr<re_ast>> &named, size_t from_state, size_t to_state, std::vector<nfa_transition> &table, logger *logger, size_t &next_state, bool allow_output) -> bool override {
            for (auto &range : _ranges) {
                std::vector<nfa_transition_action> actions;
                actions.emplace_back(_output && allow_output , L"", false, false, false, token, 0);
                if (_exclude) {
                    // if we exclude all chars, then it means we cannot make this transition - just ignore it.
                    if (range.from != 0 || range.to != WCHAR_MAX) {
                        // from->to
                        // 1. exclude 0->t ::= include (t+1)->M
                        // 2. exclude f->M ::= include 0->(f-1)
                        // 3. exclude f->t ::= include 0->(f-1) & (t+1)->M
                        if (range.from == 0) {
                            table.emplace_back(from_state, nfa_transition_guard(range.to + 1, WCHAR_MAX), to_state, std::move(actions));
                        }
                        else {
                            if (range.to == WCHAR_MAX) {
                                table.emplace_back(from_state, nfa_transition_guard(0, range.from - 1), to_state, std::move(actions));
                            }
                            else {
                                table.emplace_back(from_state, nfa_transition_guard(0, range.from - 1), to_state, std::move(actions));
                                table.emplace_back(from_state, nfa_transition_guard(range.to + 1, WCHAR_MAX), to_state, std::move(actions));
                            }
                        }
                    }
                }
                else {
                    table.emplace_back(from_state, nfa_transition_guard(range.from, range.to), to_state, std::move(actions));
                }
            }
            return true;
        }

        virtual auto null_transition_possible(const std::map<std::wstring, std::unique_ptr<re_ast>> &named) const -> bool override {
            return false;
        }

        inline auto exclude() const -> bool { return _exclude; }
        inline auto exclude(bool value) -> void { _exclude = value; }

        inline auto ranges() const -> const std::vector<char_range>& { return _ranges; }
        inline auto ranges() -> std::vector<char_range>& { return _ranges; }

        friend auto operator << (std::wostream &os, const re_ast_char_set_match &ast) -> std::wostream& {
            return ast.write(os);
        }
    };

    class re_ast_reference sealed : public re_ast{
    private:
        std::wstring _name;
        
    protected:
        virtual auto write(std::wostream &os) const ->std::wostream& override {
            return os << L'{' << _name << L'}';
        }
    public:
        re_ast_reference() = delete;
        re_ast_reference(const re_ast_reference&) = delete;
        re_ast_reference(re_ast_reference &&c)
            : re_ast(std::move(c)), _name(std::move(c._name))
        {}
        re_ast_reference(const container *cntr, const span &spn, const std::wstring &name)
            : re_ast(cntr, spn), _name(name)
        {}
        re_ast_reference(const container *cntr, const span &spn, std::wstring &&name)
            : re_ast(cntr, spn), _name(std::move(name))
        {}
        re_ast_reference(const container *cntr, span &&spn, const std::wstring &name)
            : re_ast(cntr, std::move(spn)), _name(name)
        {}
        re_ast_reference(const container *cntr, span &&spn, std::wstring &&name)
            : re_ast(cntr, std::move(spn)), _name(std::move(name))
        {}
        virtual ~re_ast_reference() {}

        virtual auto try_add_transitions(const std::wstring* token, const std::map<std::wstring, std::unique_ptr<re_ast>> &named, size_t from_state, size_t to_state, std::vector<nfa_transition> &table, logger *logger, size_t &next_state, bool allow_output) -> bool override {
            auto f = named.find(_name);
            if (f == named.end()) {
                log::error::expression_not_found(logger, cntr(), spn(), _name);
                return false;
            }
            else {
                return f->second->try_add_transitions(token, named, from_state, to_state, table, logger, next_state, _output && allow_output);
            }
        }

        virtual auto null_transition_possible(const std::map<std::wstring, std::unique_ptr<re_ast>> &named) const -> bool override {
            auto f = named.find(_name);
            if (f == named.end()) {
                return true;
            }
            else {
                return f->second->null_transition_possible(named);
            }
        }

        friend auto operator << (std::wostream &os, const re_ast_reference &ast) -> std::wostream& {
            return ast.write(os);
        }
    };

    class re_ast_then sealed : public re_ast{
    private:
        std::unique_ptr<re_ast> _re1;
        std::unique_ptr<re_ast> _re2;
    protected:
        virtual auto write(std::wostream &os) const ->std::wostream& override {
            return os << _re1 << _re2;
        }
    public:
        re_ast_then() = delete;
        re_ast_then(const re_ast_then&) = delete;
        re_ast_then(re_ast_then &&c)
            : re_ast(std::move(c)), _re1(std::move(c._re1)), _re2(std::move(c._re2))
        {}
        re_ast_then(const container *cntr, const span &spn, std::unique_ptr<re_ast> &&re1, std::unique_ptr<re_ast> &&re2)
            : re_ast(cntr, spn), _re1(std::move(re1)), _re2(std::move(re2))
        {}
        virtual ~re_ast_then() {}

        virtual auto try_add_transitions(const std::wstring* token, const std::map<std::wstring, std::unique_ptr<re_ast>> &named, size_t from_state, size_t to_state, std::vector<nfa_transition> &table, logger *logger, size_t &next_state, bool allow_output) -> bool override {
            size_t s = next_state++;
            if (!_re1->try_add_transitions(token, named, from_state, s, table, logger, next_state, _output && allow_output)) {
                return false;
            }
            else {
                return _re2->try_add_transitions(token, named, s, to_state, table, logger, next_state, _output && allow_output);
            }
        }

        virtual auto null_transition_possible(const std::map<std::wstring, std::unique_ptr<re_ast>> &named) const -> bool override {
            return _re1->null_transition_possible(named) && _re2->null_transition_possible(named);
        }

        friend auto operator << (std::wostream &os, const re_ast_then &ast) -> std::wostream& {
            return ast.write(os);
        }
    };

    class re_ast_or sealed : public re_ast{
    private:
        std::unique_ptr<re_ast> _re1;
        std::unique_ptr<re_ast> _re2;
    protected:
        virtual auto write(std::wostream &os) const ->std::wostream& override {
            return os << L"((" << _re1 << L")|(" << _re2 << L"))";
        }
    public:
        re_ast_or() = delete;
        re_ast_or(const re_ast_or &) = delete;
        re_ast_or(re_ast_or &&c)
            : re_ast(std::move(c)), _re1(std::move(c._re1)), _re2(std::move(c._re2))
        {}
        re_ast_or(const container *cntr, const span &spn, std::unique_ptr<re_ast> &&re1, std::unique_ptr<re_ast> &&re2)
            : re_ast(cntr, spn), _re1(std::move(re1)), _re2(std::move(re2))
        {}
        virtual ~re_ast_or() {}

        virtual auto try_add_transitions(const std::wstring* token, const std::map<std::wstring, std::unique_ptr<re_ast>> &named, size_t from_state, size_t to_state, std::vector<nfa_transition> &table, logger *logger, size_t &next_state, bool allow_output) -> bool override {
            if (!_re1->try_add_transitions(token, named, from_state, to_state, table, logger, next_state, _output && allow_output)) {
                return false;
            }
            return _re2->try_add_transitions(token, named, from_state, to_state, table, logger, next_state, _output && allow_output);
        }

        virtual auto null_transition_possible(const std::map<std::wstring, std::unique_ptr<re_ast>> &named) const -> bool override {
            return _re1->null_transition_possible(named) || _re2->null_transition_possible(named);
        }

        friend auto operator << (std::wostream &os, const re_ast_or &ast) -> std::wostream& {
            return ast.write(os);
        }
    };

    class re_ast_output sealed : public re_ast{
    private:
        std::unique_ptr<re_ast> _re;
        std::wstring _output;
    protected:
        virtual auto write(std::wostream &os) const ->std::wostream& override {
            return os << _re << L"{>" << _output << L'}';
        }
    public:
        re_ast_output() = delete;
        re_ast_output(const re_ast_output&) = delete;
        re_ast_output(re_ast_output &&c)
            : re_ast(std::move(c)), _re(std::move(c._re)), _output(std::move(c._output))
        {}
        re_ast_output(const container *cntr, const span &spn, std::unique_ptr<re_ast> &&re, std::wstring &&output)
            : re_ast(cntr, spn), _re(std::move(re)), _output(std::move(output))
        {}
        virtual ~re_ast_output() {}

        virtual auto try_add_transitions(const std::wstring* token, const std::map<std::wstring, std::unique_ptr<re_ast>> &named, size_t from_state, size_t to_state, std::vector<nfa_transition> &table, logger *logger, size_t &next_state, bool allow_output) -> bool override {
            // from -> re -> e(output) -> to
            if (!re_ast::_output || !allow_output) {
                // If we're not outputting anything, we might just as well delegate to the underlying re
                return _re->try_add_transitions(token, named, from_state, to_state, table, logger, next_state, false);
            }
            else {
                size_t s = next_state++;
                if (!_re->try_add_transitions(token, named, from_state, s, table, logger, next_state, false)) {
                    return false;
                }
                std::vector<nfa_transition_action> actions;
                actions.emplace_back(false, std::move(_output), false, false, false, token, 0);
                table.emplace_back(s, nfa_transition_guard(), to_state, std::move(actions));
                return true;
            }
        }

        virtual auto null_transition_possible(const std::map<std::wstring, std::unique_ptr<re_ast>> &named) const -> bool override {
            return _re->null_transition_possible(named);
        }

        friend auto operator << (std::wostream &os, const re_ast_output &ast) -> std::wostream& {
            return ast.write(os);
        }
    };

    class re_ast_cardinality sealed : public re_ast{
    private:
        std::unique_ptr<re_ast> _re;
        size_t _min;
        size_t _max;
    protected:
        virtual auto write(std::wostream &os) const ->std::wostream& override {
            // 0..1
            // 0..n
            // 1..n
            // else
            os << L'(' << _re << L')';
            switch (_min) {
            case 0:
                switch (_max) {
                case 1:
                    return os << L'?';
                case -1:
                    return os << L'*';
                default:
                    return os << L"{0," << _max << L'}';
                }
                break;
            case 1:
                switch (_max) {
                case 1:
                    return os << "{1}";
                case -1:
                    return os << L'+';
                default:
                    return os << L"{1," << _max << L'}';
                }
                break;
            default:
                if (_min == _max) {
                    return os << L'{' << _min << L'}';
                }
                else {
                    return os << L'{' << _min << L',' << _max << L'}';
                }
                break;
            }
        }
    public:
        re_ast_cardinality() = delete;
        re_ast_cardinality(const re_ast_cardinality&) = delete;
        re_ast_cardinality(re_ast_cardinality &&c)
            : re_ast(std::move(c)), _re(std::move(c._re)), _min(c._min), _max(c._max)
        {}
        re_ast_cardinality(const container *cntr, const span &spn, std::unique_ptr<re_ast> &&re, int min, int max)
            : re_ast(cntr, spn), _re(std::move(re)), _min(min), _max(max)
        {}
        virtual ~re_ast_cardinality() {}

        virtual auto try_add_transitions(const std::wstring* token, const std::map<std::wstring, std::unique_ptr<re_ast>> &named, size_t from_state, size_t to_state, std::vector<nfa_transition> &table, logger *logger, size_t &next_state, bool allow_output) -> bool override {
            // X -E-> X --min*re--> X -E-> X
            //                      X --min+1--> X
            //                      X --min+2--> X
            //                      ...
            //                      X --max-min--> X

            // re{2-4}: FROM -E-> S0 -re-> S1 -re-> S2 -E->           TO
            //                                         -re->          TO
            //                                         -re-> S3 -re-> TO
            auto s = from_state;
            // Add the '_min' transitions
            for (size_t i = 0; i < _min; i++) {
                auto t = next_state++;
                if (!_re->try_add_transitions(token, named, s, t, table, logger, next_state, _output && allow_output)) return false;
                s = t;
            }
            // If the max is infinate, then we recurse on the current state
            if (_min == _max) {
                // add an epsilon s -E-> to_state (no action)
                table.emplace_back(s, nfa_transition_guard(), to_state, std::vector<nfa_transition_action>());
            }
            else if (_max == -1) {
                // s-E->t1-re->t2-E->s-E->to_state
                auto t1 = next_state++;
                table.emplace_back(s, nfa_transition_guard(), t1, std::vector<nfa_transition_action>());
                auto t2 = next_state++;
                if (!_re->try_add_transitions(token, named, t1, t2, table, logger, next_state, _output && allow_output)) return false;
                table.emplace_back(t2, nfa_transition_guard(), s, std::vector<nfa_transition_action>());
                table.emplace_back(s, nfa_transition_guard(), to_state, std::vector<nfa_transition_action>());
                return true;
            }
            else {
                // Create _max-_min 'optional' transitions
                table.emplace_back(s, nfa_transition_guard(), to_state, std::vector<nfa_transition_action>());
                for (size_t i = _min; i < _max; i++) {
                    auto t = next_state++;
                    if (!_re->try_add_transitions(token, named, s, t, table, logger, next_state, _output && allow_output)) return false;
                    s = t;
                    table.emplace_back(s, nfa_transition_guard(), to_state, std::vector<nfa_transition_action>());
                }
            }

            return true;
        }

        virtual auto null_transition_possible(const std::map<std::wstring, std::unique_ptr<re_ast>> &named) const -> bool override {
            return _min == 0 || _re->null_transition_possible(named);
        }

        friend auto operator << (std::wostream &os, const re_ast_cardinality &ast) -> std::wostream& {
            return ast.write(os);
        }
    };

    auto re_try_parse(
        container *cntr,
        std::wistream &src,
        logger *logger,
        std::unique_ptr<re_ast> &ast)->bool;
}
