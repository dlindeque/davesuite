#pragma once

#include <map>
#include <memory>
#include <vector>
#include "..\common\container.h"
#include "..\common\span.h"

using namespace davecommon;

namespace davelexer
{
    class re_ast;
    class re_ast_char_set_match;
    class re_ast_reference;
    class re_ast_then;
    class re_ast_or;
    class re_ast_cardinality;
    class lex_ast;
    class lex_ast_binding;
    class lex_ast_section;
    class lex_ast_section_item;
    class lex_ast_import;
    class lex_ast_token;
    class lex_ast_start;
    class lex_ast_return;
    class fa_transition;

    class re_ast_visitor;
    class const_re_ast_visitor;
    class lex_ast_visitor;
    class const_lex_ast_visitor;
    class lex_ast_section_item_visitor;
    class const_lex_ast_section_item_visitor;

    class re_ast_visitor abstract {
    public:
        virtual ~re_ast_visitor() {}
        virtual auto accept(re_ast_char_set_match*) -> void = 0;
        virtual auto accept(re_ast_reference*) -> void = 0;
        virtual auto accept(re_ast_then*) -> void = 0;
        virtual auto accept(re_ast_or*) -> void = 0;
        virtual auto accept(re_ast_cardinality*) -> void = 0;
    };

    class const_re_ast_visitor abstract {
    public:
        virtual ~const_re_ast_visitor() {}
        virtual auto accept(const re_ast_char_set_match*) -> void = 0;
        virtual auto accept(const re_ast_reference*) -> void = 0;
        virtual auto accept(const re_ast_then*) -> void = 0;
        virtual auto accept(const re_ast_or*) -> void = 0;
        virtual auto accept(const re_ast_cardinality*) -> void = 0;
    };

    class lex_ast_visitor abstract {
    public:
        virtual ~lex_ast_visitor() {}
        virtual auto accept(lex_ast_binding*) -> void = 0;
        virtual auto accept(lex_ast_section*) -> void = 0;
    };

    class const_lex_ast_visitor abstract {
    public:
        virtual ~const_lex_ast_visitor() {}
        virtual auto accept(const lex_ast_binding*) -> void = 0;
        virtual auto accept(const lex_ast_section*) -> void = 0;
    };

    class lex_ast_section_item_visitor abstract {
    public:
        virtual ~lex_ast_section_item_visitor() {}
        virtual auto accept(lex_ast_import*) -> void = 0;
        virtual auto accept(lex_ast_token*) -> void = 0;
        virtual auto accept(lex_ast_start*) -> void = 0;
        virtual auto accept(lex_ast_return*) -> void = 0;
    };

    class const_lex_ast_section_item_visitor abstract {
    public:
        virtual ~const_lex_ast_section_item_visitor() {}
        virtual auto accept(const lex_ast_import*) -> void = 0;
        virtual auto accept(const lex_ast_token*) -> void = 0;
        virtual auto accept(const lex_ast_start*) -> void = 0;
        virtual auto accept(const lex_ast_return*) -> void = 0;
    };

    class re_ast abstract {
    private:
        span _spn;
    public:
        re_ast() = delete;
        re_ast(const re_ast &c)
            : _spn(c._spn)
        {}
        re_ast(re_ast &&c)
            : _spn(c._spn)
        {}
        re_ast(const span &spn)
            : _spn(spn)
        {}
        virtual ~re_ast() {}

        inline auto spn() const -> const span&{ return _spn; }

        virtual auto accept(re_ast_visitor *visitor) -> void = 0;
        virtual auto accept(const_re_ast_visitor *visitor) const -> void = 0;
    };

    auto operator << (std::wostream &os, const std::unique_ptr<re_ast> &ast)->std::wostream&;

    struct wchar_range {
        wchar_t from;
        wchar_t to;
    };

    class re_ast_char_set_match sealed : public re_ast{
    private:
        bool _exclude;
        std::vector<wchar_range> _ranges;
    public:
        re_ast_char_set_match() = delete;
        re_ast_char_set_match(const re_ast_char_set_match &) = delete;
        re_ast_char_set_match(re_ast_char_set_match &&c)
            : re_ast(std::move(c)), _exclude(c._exclude), _ranges(std::move(c._ranges))
        {}
        re_ast_char_set_match(const span &spn, bool exclude, std::vector<wchar_range> &&ranges)
            : re_ast(spn), _exclude(exclude), _ranges(std::move(ranges))
        {}
        virtual ~re_ast_char_set_match() {}

        virtual auto accept(re_ast_visitor *visitor) -> void override { visitor->accept(this); }
        virtual auto accept(const_re_ast_visitor *visitor) const -> void override { visitor->accept(this); }

        inline auto exclude() const -> bool { return _exclude; }
        inline auto exclude(bool value) -> void { _exclude = value; }

        inline auto ranges() const -> const std::vector<wchar_range>& { return _ranges; }
        inline auto ranges() -> std::vector<wchar_range>& { return _ranges; }
    };

    class re_ast_reference sealed : public re_ast{
    private:
        std::wstring _name;
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
        virtual ~re_ast_reference() {}

        inline auto name() const -> const std::wstring&{ return _name; }

        virtual auto accept(re_ast_visitor *visitor) -> void override { visitor->accept(this); }
        virtual auto accept(const_re_ast_visitor *visitor) const -> void override { visitor->accept(this); }
    };

    class re_ast_then sealed : public re_ast{
    private:
        std::unique_ptr<re_ast> _re1;
        std::unique_ptr<re_ast> _re2;
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

        inline auto re1() const -> const std::unique_ptr<re_ast>& { return _re1; }
        inline auto re2() const -> const std::unique_ptr<re_ast>& { return _re2; }

        virtual auto accept(re_ast_visitor *visitor) -> void override { visitor->accept(this); }
        virtual auto accept(const_re_ast_visitor *visitor) const -> void override { visitor->accept(this); }
    };

    class re_ast_or sealed : public re_ast{
    private:
        std::unique_ptr<re_ast> _re1;
        std::unique_ptr<re_ast> _re2;
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

        inline auto re1() const -> const std::unique_ptr<re_ast>& { return _re1; }
        inline auto re2() const -> const std::unique_ptr<re_ast>& { return _re2; }

        virtual auto accept(re_ast_visitor *visitor) -> void override { visitor->accept(this); }
        virtual auto accept(const_re_ast_visitor *visitor) const -> void override { visitor->accept(this); }
    };

    class re_ast_cardinality sealed : public re_ast{
    private:
        std::unique_ptr<re_ast> _re;
        int _min;
        int _max;
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

        inline auto re() const -> const std::unique_ptr<re_ast>& { return _re; }
        inline auto min() const -> int { return _min; }
        inline auto max() const -> int { return _max; }

        virtual auto accept(re_ast_visitor *visitor) -> void override { visitor->accept(this); }
        virtual auto accept(const_re_ast_visitor *visitor) const -> void override { visitor->accept(this); }
    };

    class lex_ast abstract {
    private:
        const container *_cntr;
        span _spn;
    public:
        lex_ast() = delete;
        lex_ast(const lex_ast &c)
            : _cntr(c._cntr), _spn(c._spn)
        {}
        lex_ast(lex_ast &&c)
            : _cntr(c._cntr), _spn(c._spn)
        {}
        lex_ast(const container *cntr, const span &spn)
            : _cntr(cntr), _spn(spn)
        {}
        virtual ~lex_ast(){}

        inline auto ctnr() const -> const container* { return _cntr; }
        inline auto spn() const -> const span&{ return _spn; }

        virtual auto accept(lex_ast_visitor *visitor) -> void = 0;
        virtual auto accept(const_lex_ast_visitor *visitor) const -> void = 0;
    };

    class lex_ast_binding sealed : public lex_ast{
    private:
        std::wstring _name;
        std::unique_ptr<re_ast> _ast;
    public:
        lex_ast_binding() = delete;
        lex_ast_binding(const lex_ast_binding&) = delete;
        lex_ast_binding(lex_ast_binding&& c) 
            : lex_ast(std::move(c)), _name(std::move(c._name)), _ast(std::move(c._ast))
        {}
        lex_ast_binding(const container *cntr, const span &spn, const std::wstring &name, std::unique_ptr<re_ast> &&ast)
            : lex_ast(cntr, spn), _name(name), _ast(std::move(ast))
        {}
        lex_ast_binding(const container *cntr, const span &spn, std::wstring &&name, std::unique_ptr<re_ast> &&ast)
            : lex_ast(cntr, spn), _name(std::move(name)), _ast(std::move(ast))
        {}

        inline auto name() const -> const std::wstring&{ return _name; }
        inline auto name() -> std::wstring&{ return _name; }
        inline auto ast() const -> const std::unique_ptr<re_ast>& { return _ast; }
        inline auto ast() -> std::unique_ptr<re_ast>& { return _ast; }

        virtual auto accept(lex_ast_visitor *visitor) -> void override { visitor->accept(this); }
        virtual auto accept(const_lex_ast_visitor *visitor) const -> void override { visitor->accept(this); }
    };

    class lex_ast_section sealed : public lex_ast{
    private:
        bool _is_shared;
        std::wstring _name;
        std::vector<std::unique_ptr<lex_ast_section_item>> _items;
    public:
        lex_ast_section() = delete;
        lex_ast_section(const lex_ast_section&) = delete;
        lex_ast_section(lex_ast_section&& c)
            : lex_ast(std::move(c)), _name(std::move(c._name)), _items(std::move(c._items))
        {}
        lex_ast_section(const container *cntr, const span &spn, bool is_shared, const std::wstring &name, std::vector<std::unique_ptr<lex_ast_section_item>> &&items)
            : lex_ast(cntr, spn), _is_shared(is_shared), _name(name), _items(std::move(items))
        {}
        lex_ast_section(const container *cntr, const span &spn, bool is_shared, std::wstring &&name, std::vector<std::unique_ptr<lex_ast_section_item>> &&items)
            : lex_ast(cntr, spn), _is_shared(is_shared), _name(std::move(name)), _items(std::move(items))
        {}

        inline auto is_shared() const -> bool { return _is_shared; }
        inline auto name() const -> const std::wstring&{ return _name; }
        inline auto name() -> std::wstring&{ return _name; }
        inline auto items() const -> const std::vector<std::unique_ptr<lex_ast_section_item>>& { return _items; }
        inline auto items() -> std::vector<std::unique_ptr<lex_ast_section_item>>& { return _items; }

        virtual auto accept(lex_ast_visitor *visitor) -> void override { visitor->accept(this); }
        virtual auto accept(const_lex_ast_visitor *visitor) const -> void override { visitor->accept(this); }
    };

    class lex_ast_section_item abstract {
    private:
        span _spn;
    public:
        lex_ast_section_item() = delete;
        lex_ast_section_item(const lex_ast_section_item &c) = delete;
        lex_ast_section_item(lex_ast_section_item &&c)
            : _spn(c._spn)
        {}
        lex_ast_section_item(const span &spn)
            : _spn(spn)
        {}
        virtual ~lex_ast_section_item(){}

        inline auto spn() const -> const span&{ return _spn; }

        virtual auto accept(lex_ast_section_item_visitor *visitor) -> void = 0;
        virtual auto accept(const_lex_ast_section_item_visitor *visitor) const -> void = 0;
    };

    auto operator << (std::wostream &os, const std::unique_ptr<lex_ast_section_item> &ast)->std::wostream&;
    
    class lex_ast_import sealed : public lex_ast_section_item{
    private:
        std::wstring _shared_section_to_import;
    public:
        lex_ast_import() = delete;
        lex_ast_import(const lex_ast_import &c) = delete;
        lex_ast_import(lex_ast_import &&c)
            : lex_ast_section_item(std::move(c))
        {}
        lex_ast_import(const span &spn, const std::wstring &shared_section_to_import)
            : lex_ast_section_item(spn), _shared_section_to_import(shared_section_to_import)
        {}
        lex_ast_import(const span &spn, std::wstring &&shared_section_to_import)
            : lex_ast_section_item(spn), _shared_section_to_import(std::move(shared_section_to_import))
        {}

        inline auto shared_section_to_import() const -> const std::wstring&{ return _shared_section_to_import; }

        virtual auto accept(lex_ast_section_item_visitor *visitor) -> void override { visitor->accept(this); }
        virtual auto accept(const_lex_ast_section_item_visitor *visitor) const -> void override { visitor->accept(this); }
    };

    class lex_ast_section_item_token abstract : public lex_ast_section_item {
    private:
        std::wstring _token_name;
        span _token_name_spn;
        std::unique_ptr<re_ast> _ast;
    public:
        lex_ast_section_item_token() = delete;
        lex_ast_section_item_token(const lex_ast_section_item_token &c) = delete;
        lex_ast_section_item_token(lex_ast_section_item_token &&c)
            : lex_ast_section_item(std::move(c)), _token_name(std::move(c._token_name)), _token_name_spn(c._token_name_spn), _ast(std::move(c._ast))
        {}
        lex_ast_section_item_token(const span &spn, const std::wstring &token_name, const span &token_name_spn, std::unique_ptr<re_ast> &&ast)
            : lex_ast_section_item(spn), _token_name(token_name), _token_name_spn(token_name_spn), _ast(std::move(ast))
        {}
        lex_ast_section_item_token(const span &spn, std::wstring &&token_name, const span &token_name_spn, std::unique_ptr<re_ast> &&ast)
            : lex_ast_section_item(spn), _token_name(std::move(token_name)), _token_name_spn(token_name_spn), _ast(std::move(ast))
        {}
        virtual ~lex_ast_section_item_token(){}

        inline auto token_name() const -> const std::wstring&{ return _token_name; }
        inline auto token_name_spn() const -> const span&{ return _token_name_spn; }
        inline auto ast() const -> const std::unique_ptr<re_ast>& { return _ast; }

        virtual auto accept(lex_ast_section_item_visitor *visitor) -> void = 0;
        virtual auto accept(const_lex_ast_section_item_visitor *visitor) const -> void = 0;
    };

    class lex_ast_token sealed : public lex_ast_section_item_token{
    public:
        lex_ast_token() = delete;
        lex_ast_token(const lex_ast_token &c) = delete;
        lex_ast_token(lex_ast_token &&c)
            : lex_ast_section_item_token(std::move(c))
        {}
        lex_ast_token(const span &spn, const std::wstring &token_name, const span &token_name_spn, std::unique_ptr<re_ast> &&ast)
            : lex_ast_section_item_token(spn, token_name, token_name_spn, std::move(ast))
        {}
        lex_ast_token(const span &spn, std::wstring &&token_name, const span &token_name_spn, std::unique_ptr<re_ast> &&ast)
            : lex_ast_section_item_token(spn, std::move(token_name), token_name_spn, std::move(ast))
        {}

        virtual auto accept(lex_ast_section_item_visitor *visitor) -> void override { visitor->accept(this); }
        virtual auto accept(const_lex_ast_section_item_visitor *visitor) const -> void override { visitor->accept(this); }
    };

    class lex_ast_start sealed : public lex_ast_section_item_token{
    private:
        std::wstring _section_name;
        span _section_name_spn;
    public:
        lex_ast_start() = delete;
        lex_ast_start(const lex_ast_start &c) = delete;
        lex_ast_start(lex_ast_start &&c)
            : lex_ast_section_item_token(std::move(c))
        {}
        lex_ast_start(const span &spn, const std::wstring &token_name, const span &token_name_spn, std::unique_ptr<re_ast> &&ast, const std::wstring &section_name, const span &section_name_spn)
            : lex_ast_section_item_token(spn, token_name, token_name_spn, std::move(ast)), _section_name(section_name), _section_name_spn(section_name_spn)
        {}
        lex_ast_start(const span &spn, std::wstring &&token_name, const span &token_name_spn, std::unique_ptr<re_ast> &&ast, const std::wstring &section_name, const span &section_name_spn)
            : lex_ast_section_item_token(spn, std::move(token_name), token_name_spn, std::move(ast)), _section_name(section_name), _section_name_spn(section_name_spn)
        {}
        lex_ast_start(const span &spn, const std::wstring &token_name, const span &token_name_spn, std::unique_ptr<re_ast> &&ast, std::wstring &&section_name, const span &section_name_spn)
            : lex_ast_section_item_token(spn, token_name, token_name_spn, std::move(ast)), _section_name(std::move(section_name)), _section_name_spn(section_name_spn)
        {}
        lex_ast_start(const span &spn, std::wstring &&token_name, const span &token_name_spn, std::unique_ptr<re_ast> &&ast, std::wstring &&section_name, const span &section_name_spn)
            : lex_ast_section_item_token(spn, std::move(token_name), token_name_spn, std::move(ast)), _section_name(std::move(section_name)), _section_name_spn(section_name_spn)
        {}

        inline auto section_name() const -> const std::wstring&{ return _section_name; }
        inline auto section_name_spn() const -> const span&{ return _section_name_spn; }

        virtual auto accept(lex_ast_section_item_visitor *visitor) -> void override { visitor->accept(this); }
        virtual auto accept(const_lex_ast_section_item_visitor *visitor) const -> void override { visitor->accept(this); }
    };

    class lex_ast_return sealed : public lex_ast_section_item_token{
    public:
        lex_ast_return() = delete;
        lex_ast_return(const lex_ast_return &c) = delete;
        lex_ast_return(lex_ast_return &&c)
            : lex_ast_section_item_token(std::move(c))
        {}
        lex_ast_return(const span &spn, const std::wstring &token_name, const span &token_name_spn, std::unique_ptr<re_ast> &&ast)
            : lex_ast_section_item_token(spn, token_name, token_name_spn, std::move(ast))
        {}
        lex_ast_return(const span &spn, std::wstring &&token_name, const span &token_name_spn, std::unique_ptr<re_ast> &&ast)
            : lex_ast_section_item_token(spn, std::move(token_name), token_name_spn, std::move(ast))
        {}

        virtual auto accept(lex_ast_section_item_visitor *visitor) -> void override { visitor->accept(this); }
        virtual auto accept(const_lex_ast_section_item_visitor *visitor) const -> void override { visitor->accept(this); }
    };

    class fa_transition sealed {
    private:
        size_t _from;
        bool _epsilon;
        bool _eod;
        wchar_t _first;
        wchar_t _last;
        size_t _to;
        size_t _yield;
    public:
        fa_transition() = delete;
        fa_transition(const fa_transition &c)
            : _from(c._from), _epsilon(c._epsilon), _eod(c._eod), _first(c._first), _last(c._last), _to(c._to), _yield(c._yield)
        {}
        fa_transition(fa_transition &&c)
            : _from(c._from), _epsilon(c._epsilon), _eod(c._eod), _first(c._first), _last(c._last), _to(c._to), _yield(c._yield)
        {}
        fa_transition(size_t from, bool epsilon, bool eod, wchar_t first, wchar_t last, size_t to, size_t yield)
            : _from(from), _epsilon(epsilon), _eod(eod), _first(first), _last(last), _to(to), _yield(yield)
        {}

        inline auto from() const -> size_t { return _from; }
        inline auto epsilon() const -> bool { return _epsilon; }
        inline auto eod() const -> bool { return _eod; }
        inline auto first() const -> wchar_t { return _first; }
        inline auto last() const -> wchar_t { return _last; }
        inline auto to() const -> size_t { return _to; }
        inline auto yield() const -> size_t { return _yield; }

        inline auto to(size_t value) -> void { _to = value; }
        inline auto yield(size_t value) -> void { _yield = value; }

        friend inline auto operator <(const fa_transition &t1, const fa_transition &t2) -> bool {
            if (t1.from() != t2.from()) return t1.from() < t2.from();
            if (t1.epsilon() != t2.epsilon()) return t2.epsilon();
            if (t1.eod() != t2.eod()) return t2.eod();
            if (t1.first() != t2.first()) return t1.first() < t2.first();
            if (t1.last() != t2.last()) return t1.last() < t2.last();
            if (t1.to() != t2.to()) return t1.to() < t2.to();
            return t1.yield() < t2.yield();
        }
    };
}