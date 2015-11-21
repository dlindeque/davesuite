#include "stdafx.h"
#include "model.h"

#include "log.h"

namespace davelexer
{
    class re_ast_wformat : public const_re_ast_visitor {
    private:
        std::wostream &_os;
    public:
        re_ast_wformat(std::wostream  &os)
            : _os(os)
        {}
        virtual ~re_ast_wformat() {}
        virtual auto accept(const re_ast_char_set_match* ast) -> void override {
            if (ast->exclude()) {
                _os << L"[^";
            }
            else {
                if (ast->ranges().size() == 1 && ast->ranges()[0].from == 0 && ast->ranges()[0].to == WCHAR_MAX) {
                    _os << L'.';
                }
                if (ast->ranges().size() != 1 || ast->ranges()[0].from != ast->ranges()[0].to) {
                    _os << L'[';
                }
            }
            for (auto &r : ast->ranges()) {
                if (r.from == r.to) {
                    wchar_friendly(r.from, _os);
                }
                else {
                    if (r.from == 0 && r.to == WCHAR_MAX) {
                        _os << L"<any>";
                    }
                    else {
                        wchar_friendly(r.from, _os) << L'-';
                        wchar_friendly(r.to, _os);
                    }
                }
            }
            if (ast->exclude() || ast->ranges().size() != 1 || ast->ranges()[0].from != ast->ranges()[0].to) {
                _os << L']';
            }
            else {
                _os;
            }
        }
        virtual auto accept(const re_ast_reference* ast) -> void override {
            _os << L'{' << ast->name() << L'}';
        }
        virtual auto accept(const re_ast_then* ast) -> void override {
            _os << ast->re1() << ast->re2();
        }
        virtual auto accept(const re_ast_or* ast) -> void override {
            _os << L"((" << ast->re1() << L")|(" << ast->re2() << L"))";
        }
        virtual auto accept(const re_ast_cardinality* ast) -> void override {
            // 0..1
            // 0..n
            // 1..n
            // else
            _os << L'(' << ast->re() << L')';
            switch (ast->min()) {
            case 0:
                switch (ast->max()) {
                case 1:
                    _os << L'?';
                    break;
                case -1:
                    _os << L'*';
                    break;
                default:
                    _os << L"{0," << ast->max() << L'}';
                    break;
                }
                break;
            case 1:
                switch (ast->max()) {
                case 1:
                    _os << "{1}";
                    break;
                case -1:
                    _os << L'+';
                    break;
                default:
                    _os << L"{1," << ast->max() << L'}';
                    break;
                }
                break;
            default:
                if (ast->min() == ast->max()) {
                    _os << L'{' << ast->min() << L'}';
                }
                else {
                    _os << L'{' << ast->min() << L',' << ast->max() << L'}';
                }
                break;
            }
        }
    };

    auto operator << (std::wostream &os, const std::unique_ptr<re_ast> &ast)->std::wostream&
    {
        if (ast == nullptr) {
            return os << "NULL";
        }
        else {
            re_ast_wformat fmt(os);
            ast->accept(&fmt);
            return os;
        }
    }

    class lex_ast_section_item_wformat : public const_lex_ast_section_item_visitor {
    private:
        std::wostream &_os;
    public:
        lex_ast_section_item_wformat(std::wostream  &os)
            : _os(os)
        {}
        virtual ~lex_ast_section_item_wformat() {}
        virtual auto accept(const lex_ast_import* ast) -> void override {
            _os << L"import " << ast->shared_section_to_import();
        }
        virtual auto accept(const lex_ast_token* ast) -> void override {
            _os << L"token " << ast->token_name() << L" = " << ast->ast();
        }
        virtual auto accept(const lex_ast_start* ast) -> void override {
            _os << L"token " << ast->token_name() << L" goto " << ast->section_name() << L" = " << ast->ast();
        }
        virtual auto accept(const lex_ast_return* ast) -> void override {
            _os << L"end " << ast->token_name() << " = " << ast->ast();
        }
    };

    auto operator << (std::wostream &os, const std::unique_ptr<lex_ast_section_item> &ast)->std::wostream&
    {
        if (ast == nullptr) {
            return os << "NULL";
        }
        else {
            lex_ast_section_item_wformat fmt(os);
            ast->accept(&fmt);
            return os;
        }
    }

    class lex_ast_wformat : public const_lex_ast_visitor {
    private:
        std::wostream &_os;
    public:
        lex_ast_wformat(std::wostream  &os)
            : _os(os)
        {}
        virtual ~lex_ast_wformat() {}
        virtual auto accept(const lex_ast_binding* ast) -> void override {
            _os << L"pattern " << ast->name() << L" = " << ast->ast();
        }
        virtual auto accept(const lex_ast_section* ast) -> void override {
            if (ast->is_shared()) _os << "shared ";
            _os << L"section " << ast->name() << L'{' << std::endl;
            for (auto &item : ast->items()) {
                _os << L"  " << item << L';' << std::endl;
            }
            _os << L'}';
        }
    };

    auto operator << (std::wostream &os, const std::unique_ptr<lex_ast> &ast)->std::wostream&
    {
        if (ast == nullptr) {
            return os << "NULL";
        }
        else {
            lex_ast_wformat fmt(os);
            ast->accept(&fmt);
            return os;
        }
    }
}