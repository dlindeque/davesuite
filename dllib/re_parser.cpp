#include "stdafx.h"
#include "re_parser.h"
#include "log.h"

#include <assert.h>

namespace davelexer
{
    class value {
    private:
        token _token;
        std::unique_ptr<re_ast> _ast;
    public:
        value() = delete;
        value(const value &) = delete;
        value(value &&c)
            : _token(std::move(c._token)), _ast(std::move(c._ast))
        {}
        value(token &&t)
            : _token(std::move(t)), _ast()
        {}
        value(std::unique_ptr<re_ast> &&ast)
            : _token(), _ast(std::move(ast))
        {}

        inline auto token() const -> const davelexer::token&{ return _token; }
        inline auto token() -> davelexer::token& { return _token; }
        inline auto ast() const -> const std::unique_ptr<re_ast>&{ return _ast; }
        inline auto ast() -> std::unique_ptr<re_ast>& { return _ast; }
    };

    // sx: shift to any state, reduce by rule x
    // rx: goto any state, reduce by rule x
    // Sx: shift to state x
    // Rx: reduce by rule x
    // Gx: goto state x

    inline auto goto_r(std::vector<int> &states) -> void
    {
        switch (states.back()) {
        case 0:
            states.push_back(1);
            break;
        case 1:
        case 2:
        case 8:
        case 10:
            states.push_back(2);
            break;
        case 7:
            states.push_back(8);
            break;
        case 9:
            states.push_back(10);
            break;
        default:
            assert(false);
            break;
        }
    }

    inline auto goto_s(std::vector<int> &states) -> void
    {
        switch (states.back()) {
        case 3:
            states.push_back(4);
            break;
        case 5:
            states.push_back(6);
            break;
        default:
            assert(false);
            break;
        }
    }

    inline auto goto_t(std::vector<int> &states, std::vector<value> &values) -> void
    {
        switch (states.back()) {
        case 3:
        case 5: // r15
            // S -> T
            if (true) {
                // We pop T (re_ast_char_set_match) and push it again, so we just don't do it!
                goto_s(states);
            }
            break;
        case 4:
        case 6: // r16
            // S -> ST
            if (true) {
                states.pop_back();
                auto t = std::move(values.back().ast());
                values.pop_back();
                // We've now got S on the top of the stack - just mutate it in place
                auto s = static_cast<re_ast_char_set_match*>(values.back().ast().get());
                for (auto r : static_cast<re_ast_char_set_match*>(t.get())->ranges()) {
                    s->ranges().push_back(std::move(r));
                }
                goto_s(states);
            }
            break;
        default:
            assert(false);
            break;
        }
    }

    inline auto charset(const token &tkn)->std::vector < char_range > {
        std::vector<char_range> ranges;
        switch (tkn.cs) {
        case re_char_set::any:
            ranges.push_back(char_range{ L'\x0', WCHAR_MAX });
            break;
        case re_char_set::digit:
            ranges.push_back(char_range{ L'0', L'9' });
            break;
        case re_char_set::lalpha:
            ranges.push_back(char_range{ L'a', L'z' });
            break;
        case re_char_set::ualpha:
            ranges.push_back(char_range{ L'A', L'Z' });
            break;
        case re_char_set::space:
            ranges.push_back(char_range{ L' ', L' ' });
            ranges.push_back(char_range{ L'\t', L'\t' });
            ranges.push_back(char_range{ L'\v', L'\v' });
            ranges.push_back(char_range{ L'\n', L'\n' });
            ranges.push_back(char_range{ L'\r', L'\r' });
            ranges.push_back(char_range{ L'\f', L'\f' });
            break;
        case re_char_set::word:
            ranges.push_back(char_range{ L'a', L'z' });
            ranges.push_back(char_range{ L'A', L'Z' });
            break;
        default:
            assert(false);
            break;
        }
        return ranges;
    }

    inline auto chr(wchar_t from, wchar_t to) -> std::vector < char_range > {
        std::vector<char_range> ranges;
        ranges.push_back(char_range{ from, to });
        return ranges;
    }

    inline auto chr(wchar_t ch) -> std::vector < char_range > {
        return chr(ch, ch);
    }

    auto re_try_parse(
        container *container,
        std::wistream &src,
        logger *logger,
        std::unique_ptr<re_ast> &ast)->bool
    {
        int end_line = 1, end_column = 1, lex_state = 0;
        bool read = true;
        std::vector<int> states;
        std::vector<value> values;
        states.push_back(0);
        token tkn;
        while (true) {
            if (read) {
                davelexer::re_lex(src, end_line, end_column, lex_state, tkn);
            }
            switch (states.back()) {
            case 0:
            case 7:
            case 9:
                switch (tkn.type) {
                case re_token_type::char_: // s1
                    // R -> c
                    if (true) {
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_char_set_match(tkn.spn, false, chr(tkn.char_))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::char_set: // s2
                    // R -> s
                    if (true) {
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_char_set_match(tkn.spn, false, charset(tkn))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::name: // s3
                    // R -> n
                    if (true) {
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_reference(tkn.spn, std::move(tkn.name_output_whitespace))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::hyphen: // s4
                    // R -> -
                    if (true) {
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_char_set_match(tkn.spn, false, chr(L'-'))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::bracket_left: // S3
                    states.push_back(3);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                case re_token_type::ex_bracket_left: // S5
                    states.push_back(5);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                case re_token_type::parenthesis_left: // S7
                    states.push_back(7);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                default:
                    // Syntax error!
                    if (true) {
                        std::vector<re_token_type> expected;
                        expected.emplace_back(re_token_type::char_);
                        expected.emplace_back(re_token_type::char_set);
                        expected.emplace_back(re_token_type::name);
                        expected.emplace_back(re_token_type::hyphen);
                        expected.emplace_back(re_token_type::bracket_left);
                        expected.emplace_back(re_token_type::ex_bracket_left);
                        expected.emplace_back(re_token_type::parenthesis_left);
                        log::error::syntax_error(logger, container, tkn.spn, expected);
                        return false;
                    }
                    break;
                }
                break;
            case 1:
                switch (tkn.type) {
                case re_token_type::char_: // s1
                    // R -> c
                    if (true) {
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_char_set_match(tkn.spn, false, chr(tkn.char_))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::char_set: // s2
                    // R -> s
                    if (true) {
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_char_set_match(tkn.spn, false, charset(tkn))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::name: // s3
                    // R -> n
                    if (true) {
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_reference(tkn.spn, std::move(tkn.name_output_whitespace))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::hyphen: // s4
                    // R -> -
                    if (true) {
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_char_set_match(tkn.spn, false, chr(L'-'))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::bracket_left: // S3
                    states.push_back(3);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                case re_token_type::ex_bracket_left: // S5
                    states.push_back(5);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                case re_token_type::parenthesis_left: // S7
                    states.push_back(7);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                case re_token_type::pipe: // S9
                    states.push_back(9);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                case re_token_type::output: // s10
                    // R -> Ro
                    if (true) {
                        auto r = std::move(values.back().ast());
                        auto b = r->spn().begin;
                        values.pop_back();
                        states.pop_back();
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_output(span{ b, tkn.spn.end }, std::move(r), std::move(tkn.name_output_whitespace))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::cardinality: // s11
                    // R -> Rd
                    if (true) {
                        if (tkn.cardinality_min == 1 && tkn.cardinality_max == 1) {
                            // We're not actually assigning cardinality (all RE's are {1} by default)
                            states.pop_back();
                            goto_r(states);
                        }
                        else if ((tkn.cardinality_min == 0 && tkn.cardinality_max == 0) || (tkn.cardinality_max < tkn.cardinality_min)) {
                            log::error::invalid_cardinality(logger, container, tkn.spn, tkn.cardinality_min, tkn.cardinality_max);
                            return false;
                        }
                        else {
                            auto r = std::move(values.back().ast());
                            auto b = r->spn().begin;
                            values.pop_back();
                            states.pop_back();
                            values.emplace_back(std::unique_ptr<re_ast>(new re_ast_cardinality(span{ b, tkn.spn.end }, std::move(r), tkn.cardinality_min, tkn.cardinality_max)));
                            goto_r(states);
                        }
                        read = true;
                    }
                    break;
                case re_token_type::eod: // s0
                    // S' -> R$
                    // Accept
                    ast = std::move(values.back().ast());
                    return true;
                default:
                    // Syntax error!
                    if (true) {
                        std::vector<re_token_type> expected;
                        expected.emplace_back(re_token_type::char_);
                        expected.emplace_back(re_token_type::char_set);
                        expected.emplace_back(re_token_type::name);
                        expected.emplace_back(re_token_type::hyphen);
                        expected.emplace_back(re_token_type::bracket_left);
                        expected.emplace_back(re_token_type::ex_bracket_left);
                        expected.emplace_back(re_token_type::parenthesis_left);
                        expected.emplace_back(re_token_type::pipe);
                        expected.emplace_back(re_token_type::output);
                        expected.emplace_back(re_token_type::cardinality);
                        expected.emplace_back(re_token_type::eod);
                        log::error::syntax_error(logger, container, tkn.spn, expected);
                        return false;
                    }
                    break;
                }
                break;
            case 2:
                switch (tkn.type) {
                case re_token_type::char_:
                case re_token_type::char_set:
                case re_token_type::name:
                case re_token_type::bracket_left:
                case re_token_type::ex_bracket_left:
                case re_token_type::parenthesis_left:
                case re_token_type::parenthesis_right:
                case re_token_type::eod: // R8
                    // R -> RR
                    if (true) {
                        read = false;
                        states.pop_back();
                        states.pop_back();
                        auto r2 = std::move(values.back().ast());
                        values.pop_back();
                        auto r1 = std::move(values.back().ast());
                        auto spn = span{ r1->spn().begin, r2->spn().end };
                        values.pop_back();
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_then(spn, std::move(r1), std::move(r2))));
                        goto_r(states);
                    }
                    break;
                case re_token_type::pipe: // S9
                    states.push_back(9);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                case re_token_type::output: // s10
                    // R -> Ro
                    if (true) {
                        auto r = std::move(values.back().ast());
                        auto b = r->spn().begin;
                        values.pop_back();
                        states.pop_back();
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_output(span{ b, tkn.spn.end }, std::move(r), std::move(tkn.name_output_whitespace))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::cardinality: // s11
                    // R -> Rd
                    if (true) {
                        if (tkn.cardinality_min == 1 && tkn.cardinality_max == 1) {
                            // We're not actually assigning cardinality (all RE's are {1} by default)
                            states.pop_back();
                            goto_r(states);
                        }
                        else if ((tkn.cardinality_min == 0 && tkn.cardinality_max == 0) || (tkn.cardinality_max < tkn.cardinality_min)) {
                            log::error::invalid_cardinality(logger, container, tkn.spn, tkn.cardinality_min, tkn.cardinality_max);
                            return false;
                        }
                        else {
                            auto r = std::move(values.back().ast());
                            auto b = r->spn().begin;
                            values.pop_back();
                            states.pop_back();
                            values.emplace_back(std::unique_ptr<re_ast>(new re_ast_cardinality(span{ b, tkn.spn.end }, std::move(r), tkn.cardinality_min, tkn.cardinality_max)));
                            goto_r(states);
                        }
                        read = true;
                    }
                    break;
                default:
                    // Syntax error!
                    if (true) {
                        std::vector<re_token_type> expected;
                        expected.emplace_back(re_token_type::char_);
                        expected.emplace_back(re_token_type::char_set);
                        expected.emplace_back(re_token_type::name);
                        expected.emplace_back(re_token_type::hyphen);
                        expected.emplace_back(re_token_type::bracket_left);
                        expected.emplace_back(re_token_type::ex_bracket_left);
                        expected.emplace_back(re_token_type::parenthesis_left);
                        expected.emplace_back(re_token_type::pipe);
                        expected.emplace_back(re_token_type::output);
                        expected.emplace_back(re_token_type::cardinality);
                        log::error::syntax_error(logger, container, tkn.spn, expected);
                        return false;
                    }
                    break;
                }
                break;
            case 3:
            case 5:
                switch (tkn.type) {
                case re_token_type::char_: // S11
                    states.push_back(11);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                case re_token_type::hyphen: // s12
                    // T -> -
                    if (true) {
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_char_set_match(tkn.spn, false, chr(tkn.char_))));
                        goto_t(states, values);
                        read = true;
                    }
                    break;
                default:
                    // Syntax error!
                    if (true) {
                        std::vector<re_token_type> expected;
                        expected.emplace_back(re_token_type::char_);
                        expected.emplace_back(re_token_type::hyphen);
                        log::error::syntax_error(logger, container, tkn.spn, expected);
                        return false;
                    }
                    break;
                }
                break;
            case 4:
            case 6:
                switch (tkn.type) {
                case re_token_type::char_: // S11
                    states.push_back(11);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                case re_token_type::hyphen: // s12
                    // T -> -
                    if (true) {
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_char_set_match(tkn.spn, false, chr(tkn.char_))));
                        goto_t(states, values);
                        read = true;
                    }
                    break;
                case re_token_type::bracket_right: // s5,s6
                    // s==4 ? R -> [S] : R -> @S]
                    if (true) {
                        auto s = std::move(values.back().ast());
                        static_cast<re_ast_char_set_match*>(s.get())->exclude(states.back() == 6);
                        values.pop_back();
                        values.pop_back();
                        states.pop_back();
                        states.pop_back();
                        values.emplace_back(std::move(s));
                        goto_r(states);
                        read = true;
                    }
                    break;
                default:
                    // Syntax error!
                    if (true) {
                        std::vector<re_token_type> expected;
                        expected.emplace_back(re_token_type::char_);
                        expected.emplace_back(re_token_type::hyphen);
                        expected.emplace_back(re_token_type::bracket_right);
                        log::error::syntax_error(logger, container, tkn.spn, expected);
                        return false;
                    }
                    break;
                }
                break;
            case 8:
                switch (tkn.type) {
                case re_token_type::char_: // s1
                    // R -> c
                    if (true) {
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_char_set_match(tkn.spn, false, chr(tkn.char_))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::char_set: // s2
                    // R -> s
                    if (true) {
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_char_set_match(tkn.spn, false, charset(tkn))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::name: // s3
                    // R -> n
                    if (true) {
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_reference(tkn.spn, std::move(tkn.name_output_whitespace))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::hyphen: // s4
                    // R -> -
                    if (true) {
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_char_set_match(tkn.spn, false, chr(L'-'))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::bracket_left: // S3
                    states.push_back(3);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                case re_token_type::ex_bracket_left: // S5
                    states.push_back(5);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                case re_token_type::parenthesis_left: // S7
                    states.push_back(7);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                case re_token_type::parenthesis_right: // s7
                    // R -> (R)
                    if (true) {
                        auto r = std::move(values.back().ast());
                        values.pop_back();
                        states.pop_back();
                        values.pop_back();
                        states.pop_back();
                        values.push_back(std::move(r));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::pipe: // S9
                    states.push_back(9);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                case re_token_type::output: // s10
                    // R -> Ro
                    if (true) {
                        auto r = std::move(values.back().ast());
                        auto b = r->spn().begin;
                        values.pop_back();
                        states.pop_back();
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_output(span{ b, tkn.spn.end }, std::move(r), std::move(tkn.name_output_whitespace))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::cardinality: // s11
                    // R -> Rd
                    if (true) {
                        if (tkn.cardinality_min == 1 && tkn.cardinality_max == 1) {
                            // We're not actually assigning cardinality (all RE's are {1} by default)
                            states.pop_back();
                            goto_r(states);
                        }
                        else if ((tkn.cardinality_min == 0 && tkn.cardinality_max == 0) || (tkn.cardinality_max < tkn.cardinality_min)) {
                            log::error::invalid_cardinality(logger, container, tkn.spn, tkn.cardinality_min, tkn.cardinality_max);
                            return false;
                        }
                        else {
                            auto r = std::move(values.back().ast());
                            auto b = r->spn().begin;
                            values.pop_back();
                            states.pop_back();
                            values.emplace_back(std::unique_ptr<re_ast>(new re_ast_cardinality(span{ b, tkn.spn.end }, std::move(r), tkn.cardinality_min, tkn.cardinality_max)));
                            goto_r(states);
                        }
                        read = true;
                    }
                    break;
                default:
                    // Syntax error!
                    if (true) {
                        std::vector<re_token_type> expected;
                        expected.emplace_back(re_token_type::char_);
                        expected.emplace_back(re_token_type::char_set);
                        expected.emplace_back(re_token_type::name);
                        expected.emplace_back(re_token_type::hyphen);
                        expected.emplace_back(re_token_type::bracket_left);
                        expected.emplace_back(re_token_type::ex_bracket_left);
                        expected.emplace_back(re_token_type::parenthesis_left);
                        expected.emplace_back(re_token_type::parenthesis_right);
                        expected.emplace_back(re_token_type::pipe);
                        expected.emplace_back(re_token_type::output);
                        expected.emplace_back(re_token_type::cardinality);
                        log::error::syntax_error(logger, container, tkn.spn, expected);
                        return false;
                    }
                    break;
                }
                break;
            case 10:
                switch (tkn.type) {
                case re_token_type::char_:
                case re_token_type::char_set:
                case re_token_type::name:
                case re_token_type::hyphen:
                case re_token_type::bracket_left:
                case re_token_type::ex_bracket_left:
                case re_token_type::parenthesis_left:
                case re_token_type::parenthesis_right:
                case re_token_type::pipe:
                case re_token_type::eod: // R9
                    // R -> R|R
                    if (true) {
                        auto r2 = std::move(values.back().ast());
                        values.pop_back();
                        values.pop_back();
                        auto r1 = std::move(values.back().ast());
                        values.pop_back();
                        states.pop_back();
                        states.pop_back();
                        states.pop_back();
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_or(span{ r1->spn().begin, r2->spn().end }, std::move(r1), std::move(r2))));
                        goto_r(states);
                        read = false;
                    }
                    break;
                case re_token_type::output: // s10
                    // R->Ro
                    if (true) {
                        auto r = std::move(values.back().ast());
                        values.pop_back();
                        states.pop_back();
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_output(span{ r->spn().begin, tkn.spn.end }, std::move(r), std::move(tkn.name_output_whitespace))));
                        goto_r(states);
                        read = true;
                    }
                    break;
                case re_token_type::cardinality: // s11
                    // R -> Rd
                    if (true) {
                        if (tkn.cardinality_min == 1 && tkn.cardinality_max == 1) {
                            // We're not actually assigning cardinality (all RE's are {1} by default)
                            states.pop_back();
                            goto_r(states);
                        }
                        else if ((tkn.cardinality_min == 0 && tkn.cardinality_max == 0) || (tkn.cardinality_max < tkn.cardinality_min)) {
                            log::error::invalid_cardinality(logger, container, tkn.spn, tkn.cardinality_min, tkn.cardinality_max);
                            return false;
                        }
                        else {
                            auto r = std::move(values.back().ast());
                            auto b = r->spn().begin;
                            values.pop_back();
                            states.pop_back();
                            values.emplace_back(std::unique_ptr<re_ast>(new re_ast_cardinality(span{ b, tkn.spn.end }, std::move(r), tkn.cardinality_min, tkn.cardinality_max)));
                            goto_r(states);
                        }
                        read = true;
                    }
                    break;
                default:
                    // Syntax error!
                    if (true) {
                        std::vector<re_token_type> expected;
                        expected.emplace_back(re_token_type::char_);
                        expected.emplace_back(re_token_type::char_set);
                        expected.emplace_back(re_token_type::name);
                        expected.emplace_back(re_token_type::hyphen);
                        expected.emplace_back(re_token_type::bracket_left);
                        expected.emplace_back(re_token_type::ex_bracket_left);
                        expected.emplace_back(re_token_type::parenthesis_left);
                        expected.emplace_back(re_token_type::pipe);
                        expected.emplace_back(re_token_type::output);
                        expected.emplace_back(re_token_type::cardinality);
                        log::error::syntax_error(logger, container, tkn.spn, expected);
                        return false;
                    }
                    break;
                }
                break;
            case 11:
                switch (tkn.type) {
                case re_token_type::hyphen: // S12
                    states.push_back(12);
                    values.emplace_back(std::move(tkn));
                    read = true;
                    break;
                case re_token_type::char_:
                case re_token_type::bracket_right: // R13
                    // T -> c
                    if (true) {
                        auto c = std::move(values.back().token());
                        values.pop_back();
                        states.pop_back();
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_char_set_match(c.spn, false, chr(c.char_))));
                        goto_t(states, values);
                        read = false;
                    }
                    break;
                default:
                    // Syntax error!
                    if (true) {
                        std::vector<re_token_type> expected;
                        expected.emplace_back(re_token_type::hyphen);
                        expected.emplace_back(re_token_type::bracket_right);
                        log::error::syntax_error(logger, container, tkn.spn, expected);
                        return false;
                    }
                    break;
                }
                break;
            case 12:
                switch (tkn.type) {
                case re_token_type::char_: // s14
                    // T -> c-c
                    if (true) {
                        values.pop_back();
                        auto c1 = std::move(values.back().token());
                        if (c1.char_ > tkn.char_) {
                            log::error::invalid_range(logger, container, span{ c1.spn.begin, tkn.spn.end }, c1.char_, tkn.char_);
                            return false;
                        }
                        values.pop_back();
                        states.pop_back();
                        states.pop_back();
                        values.emplace_back(std::unique_ptr<re_ast>(new re_ast_char_set_match(span{ c1.spn.begin, tkn.spn.end }, false, chr(c1.char_, tkn.char_))));
                        goto_t(states, values);
                        read = true;
                    }
                    break;
                default:
                    // Syntax error!
                    if (true) {
                        std::vector<re_token_type> expected;
                        expected.emplace_back(re_token_type::char_);
                        log::error::syntax_error(logger, container, tkn.spn, expected);
                        return false;
                    }
                    break;
                }
                break;
            }
        }
    }
}