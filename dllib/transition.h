#pragma once

#include <string>

namespace davelexer
{
    class transition_action {
    private:
        bool _output_matched;
        std::wstring _output_alternate;
        bool _yield;
        bool _pop;
        bool _push;
        size_t _yield_token;
        size_t _goto;
    public:
        transition_action() = delete;
        transition_action(const transition_action&c)
            : _output_matched(c._output_matched), _output_alternate(c._output_alternate), _yield(c._yield), _pop(c._pop), _push(c._push), _yield_token(c._yield_token), _goto(c._goto)
        {}
        transition_action(transition_action &&c)
            : _output_matched(c._output_matched), _output_alternate(std::move(c._output_alternate)), _yield(c._yield), _pop(c._pop), _push(c._push), _yield_token(std::move(c._yield_token)), _goto(c._goto)
        {}
        transition_action(bool output_matched, const std::wstring &output_alternate, bool yield, bool pop, bool push, size_t yield_token, size_t goto_)
            : _output_matched(output_matched), _output_alternate(output_alternate), _yield(yield), _pop(pop), _push(push), _yield_token(yield_token), _goto(goto_)
        {}
        transition_action(bool output_matched, std::wstring &&output_alternate, bool yield, bool pop, bool push, size_t yield_token, size_t goto_)
            : _output_matched(output_matched), _output_alternate(std::move(output_alternate)), _yield(yield), _pop(pop), _push(push), _yield_token(yield_token), _goto(goto_)
        {}

        inline auto output_matched() const -> bool { return _output_matched; }
        inline auto output_alternate() const -> const std::wstring&{ return _output_alternate; }
        inline auto yield() const -> bool { return _yield; }
        inline auto pop() const -> bool { return _pop; }
        inline auto push() const -> bool { return _push; }
        inline auto yield_token() const -> size_t { return _yield_token; }
        inline auto goto_state() const -> size_t { return _goto; }

        friend inline auto operator ==(const transition_action &a1, const transition_action &a2) -> bool {
            return a1._yield == a2._yield
                && a1._pop == a2._pop
                && a1._push == a2._push
                && a1._output_matched == a2._output_matched
                && a1._yield_token == a2._yield_token
                && (!a1._push || a1._goto == a2._goto)
                && a1._output_alternate == a2._output_alternate;
        }
        friend inline auto operator !=(const transition_action &a1, const transition_action &a2) -> bool {
            return !(a1 == a2);
        }
        friend inline auto operator <(const transition_action &a1, const transition_action &a2) -> bool {
            if (a1._yield != a2._yield) {
                // return a1._yield < a2._yield (false < true)
                return a2._yield;
            }
            if (a1._pop != a2._pop) {
                return a2._pop;
            }
            if (a1._push != a2._push) {
                return a2._push;
            }
            if (a1._output_matched != a2._output_matched) {
                return a2._output_matched;
            }
            if (a1._yield_token != a2._yield_token) {
                return a1._yield_token < a2._yield_token;
            }
            if (a1._push && a1._goto != a2._goto) {
                return a1._goto < a2._goto;
            }
            return a1._output_alternate < a2._output_alternate;
        }
    };

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

        friend inline auto operator ==(const nfa_transition_guard &g1, const nfa_transition_guard &g2) -> bool {
            return g1._epsilon == g2._epsilon && g1._first == g2._first && g1._last == g2._last;
        }
        friend inline auto operator !=(const nfa_transition_guard &g1, const nfa_transition_guard &g2) -> bool {
            return !(g1 == g2);
        }
        friend inline auto operator <(const nfa_transition_guard &g1, const nfa_transition_guard &g2) -> bool {
            if (g1._epsilon != g2._epsilon) {
                return g2._epsilon;
            }
            if (g1._first == g2._first) {
                return g1._last < g2._last;
            }
            else {
                return g1._first < g2._first;
            }
        }
    };

    class dfa_transition_guard {
    private:
        wchar_t _first;
        wchar_t _last;
    public:
        dfa_transition_guard(const dfa_transition_guard &c)
            : _first(c._first), _last(c._last)
        {}
        dfa_transition_guard(dfa_transition_guard &&c)
            : _first(std::move(c._first)), _last(std::move(c._last))
        {}
        dfa_transition_guard(const wchar_t &first, const wchar_t &last)
            : _first(first), _last(last)
        {}

        inline auto first() const -> wchar_t { return _first; }
        inline auto last() const -> wchar_t { return _last; }

        friend inline auto operator ==(const dfa_transition_guard &g1, const dfa_transition_guard &g2) -> bool {
            return g1._first == g2._first && g1._last == g2._last;
        }
        friend inline auto operator !=(const dfa_transition_guard &g1, const dfa_transition_guard &g2) -> bool {
            return !(g1 == g2);
        }
        friend inline auto operator <(const dfa_transition_guard &g1, const dfa_transition_guard &g2) -> bool {
            if (g1._first == g2._first) {
                return g1._last < g2._last;
            }
            else {
                return g1._first < g2._first;
            }
        }
    };

    template<typename _Guard> class transition {
    private:
        size_t _from;
        _Guard _guard;
        size_t _to;
        std::vector<transition_action> _actions;
    public:
        transition() = delete;
        transition(const transition<_Guard> &c)
            : _from(c._from), _guard(c._guard), _to(c._to), _actions(c._actions)
        {}
        transition(transition<_Guard> &&c)
            : _from(c._from), _guard(std::move(c._guard)), _to(c._to), _actions(std::move(c._actions))
        {}
        transition(size_t from, _Guard &&guard, size_t to, std::vector<transition_action> &&actions)
            : _from(from), _guard(std::move(guard)), _to(to), _actions(std::move(actions))
        {}
        transition(size_t from, const _Guard &guard, size_t to, std::vector<transition_action> &&actions)
            : _from(from), _guard(guard), _to(to), _actions(std::move(actions))
        {}
        transition(size_t from, _Guard &&guard, size_t to, const std::vector<transition_action> &actions)
            : _from(from), _guard(std::move(guard)), _to(to), _actions(actions)
        {}
        transition(size_t from, const _Guard &guard, size_t to, const std::vector<transition_action> &actions)
            : _from(from), _guard(guard), _to(to), _actions(actions)
        {}

        inline auto from() const -> size_t { return _from; }
        inline auto from(size_t value) -> void { _from = value; }
        inline auto to() const -> size_t { return _to; }
        inline auto to(size_t value) -> void { _to = value; }
        inline auto guard() const -> const _Guard&{ return _guard; }
        inline auto actions() const -> const std::vector<transition_action>& { return _actions; }
        inline auto actions() -> std::vector<transition_action>& { return _actions; }

        friend inline auto operator <(const transition<_Guard> &t1, const transition<_Guard> &t2) -> bool {
            if (t1.from() != t2.from()) {
                return t1.from() < t2.from();
            }
            if (t1.to() != t2.to()) {
                return t1.to() < t2.to();
            }
            if (t1.actions().size() == t2.actions().size()) {
                if (t1.guard() != t2.guard()) {
                    return t1.guard() < t2.guard();
                }
                for (size_t i = 0; i < t1.actions().size(); i++) {
                    if (t1.actions()[i] != t2.actions()[i]) {
                        return t1.actions()[i] < t2.actions()[i];
                    }
                }
                return false;
            }
            else {
                return t1.actions().size() < t2.actions().size();
            }
        }
    };

    typedef transition<nfa_transition_guard> nfa_transition;
    typedef transition<dfa_transition_guard> dfa_transition;
}