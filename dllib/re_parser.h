#pragma once

#include <istream>
#include <memory>
#include <vector>
#include "re_lexer.h"

#include "..\common\logger.h"
#include "log.h"

using namespace davecommon;

namespace davelexer
{
    typedef const std::wstring* token_id;

    enum class nfa_action {
        none,
        reduce_token,
        push_state,
        pop_state
    };

    struct nfa_transition {
        unsigned int from;

        bool epsilon;
        wchar_t first;
        wchar_t last;
        
        unsigned int to;
        
        bool echo_matched;
        std::wstring output;
        
        nfa_action action;
        token_id reduce_token;
    };

    class re_ast abstract {
    private:
        span _spn;
    protected:
        virtual auto write(std::wostream &os) const ->std::wostream& = 0;
    public:
        re_ast() = delete;
        re_ast(const re_ast &) = delete;
        re_ast(re_ast &&c)
            : _spn(std::move(c._spn))
        {}
        re_ast(const span &spn)
            : _spn(spn)
        {}
        re_ast(const span &&spn)
            : _spn(std::move(spn))
        {}
        virtual ~re_ast() {}

        inline auto spn() const -> const span&{ return _spn; }

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

    class re_ast_char_set_match sealed : public re_ast {
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
        re_ast_char_set_match(const span &spn, bool exclude, std::vector<char_range> &&ranges)
            : re_ast(spn), _exclude(exclude), _ranges(std::move(ranges))
        {}
        re_ast_char_set_match(span &&spn, bool exclude, std::vector<char_range> &&ranges)
            : re_ast(std::move(spn)), _exclude(exclude), _ranges(std::move(ranges))
        {}
        virtual ~re_ast_char_set_match() {}

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
        re_ast_reference(const span &spn, const std::wstring &name)
            : re_ast(spn), _name(name)
        {}
        re_ast_reference(const span &spn, std::wstring &&name)
            : re_ast(spn), _name(std::move(name))
        {}
        re_ast_reference(span &&spn, const std::wstring &name)
            : re_ast(std::move(spn)), _name(name)
        {}
        re_ast_reference(span &&spn, std::wstring &&name)
            : re_ast(std::move(spn)), _name(std::move(name))
        {}
        virtual ~re_ast_reference() {}

        friend auto operator << (std::wostream &os, const re_ast_reference &ast) -> std::wostream& {
            return ast.write(os);
        }
    };

    class re_ast_then sealed : public re_ast {
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
        re_ast_then(const span &spn, std::unique_ptr<re_ast> &&re1, std::unique_ptr<re_ast> &&re2)
            : re_ast(spn), _re1(std::move(re1)), _re2(std::move(re2))
        {}
        virtual ~re_ast_then() {}

        friend auto operator << (std::wostream &os, const re_ast_then &ast) -> std::wostream& {
            return ast.write(os);
        }
    };

    class re_ast_or sealed : public re_ast {
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
        re_ast_or(const span &spn, std::unique_ptr<re_ast> &&re1, std::unique_ptr<re_ast> &&re2)
            : re_ast(spn), _re1(std::move(re1)), _re2(std::move(re2))
        {}
        virtual ~re_ast_or() {}

        friend auto operator << (std::wostream &os, const re_ast_or &ast) -> std::wostream& {
            return ast.write(os);
        }
    };

    class re_ast_output sealed : public re_ast {
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
        re_ast_output(const span &spn, std::unique_ptr<re_ast> &&re, std::wstring &&output)
            : re_ast(spn), _re(std::move(re)), _output(std::move(output))
        {}
        virtual ~re_ast_output() {}

        friend auto operator << (std::wostream &os, const re_ast_output &ast) -> std::wostream& {
            return ast.write(os);
        }
    };

    class re_ast_cardinality sealed : public re_ast {
    private:
        std::unique_ptr<re_ast> _re;
        int _min;
        int _max;
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
        re_ast_cardinality(const span &spn, std::unique_ptr<re_ast> &&re, int min, int max)
            : re_ast(spn), _re(std::move(re)), _min(min), _max(max)
        {}
        virtual ~re_ast_cardinality() {}

        friend auto operator << (std::wostream &os, const re_ast_cardinality &ast) -> std::wostream& {
            return ast.write(os);
        }
    };

    auto re_try_parse(
        container *container,
        std::wistream &src,
        logger *logger,
        std::unique_ptr<re_ast> &ast)->bool;
}
