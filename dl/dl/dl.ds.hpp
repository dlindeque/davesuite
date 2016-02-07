//
//  dl.ds.hpp
//  test2
//
//  Created by David Lindeque on 14/12/2015.
//  Copyright © 2015 David Lindeque. All rights reserved.
//

#ifndef dl_ds_hpp
#define dl_ds_hpp

#include <stdio.h>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <assert.h>

#include "../../common/container.h"
#include "../../common/span.h"
#include "../../common/logger.h"
#include "../../common/symboltable.h"

namespace davelexer {
    
    template<typename T> struct AstToken {
        AstToken()
        { }
        AstToken(const davecommon::span &spn, const T &value)
        : Spn(spn), Value(value)
        {}
        AstToken(const davecommon::span &spn, T &&value)
        : Spn(spn), Value(std::move(value))
        {}
        
        T Value;
        davecommon::span Spn;
        
        friend inline auto operator ==(const AstToken<T> &v1, const AstToken<T> &v2) -> bool {
            return v1.Spn == v2.Spn && v1.Value == v2.Value;
        }
    };
    
    class Ast {
    public:
        Ast(const davecommon::span &spn)
        : Spn(spn)
        {}
        davecommon::span Spn;
    };
    
    class StartAutomataAst;
    class NamespaceAst;
    class ImportAst;
    
    class DocumentAstVisitor {
    public:
        virtual auto visit(const StartAutomataAst*) -> void = 0;
        virtual auto visit(const NamespaceAst*) -> void = 0;
        virtual auto visit(const ImportAst*) -> void = 0;
    };
    
    class DocumentAst : public Ast {
    public:
        DocumentAst(const davecommon::span &spn)
        : Ast(spn)
        {}
        virtual auto accept(DocumentAstVisitor*) const -> void = 0;
    };
    
    class StartAutomataAst : public DocumentAst {
    public:
        StartAutomataAst(const davecommon::span &spn, std::vector<AstToken<std::wstring>> &&document)
        : DocumentAst(spn), Document(std::move(document))
        {}
        
        std::vector<AstToken<std::wstring>> Document;
        virtual auto accept(DocumentAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class ImportAst : public DocumentAst {
    public:
        ImportAst(const davecommon::span &spn, AstToken<std::wstring> &&document)
        : DocumentAst(spn), Document(document)
        {}
        AstToken<std::wstring> Document;
        virtual auto accept(DocumentAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class NamespaceItemAst;
    
    class NamespaceAst : public DocumentAst {
    public:
        NamespaceAst(const davecommon::span &spn, std::vector<AstToken<std::wstring>> &&name, std::vector<std::shared_ptr<NamespaceItemAst>> &&items)
        : DocumentAst(spn), Name(std::move(name)), Items(std::move(items))
        {}
        
        std::vector<AstToken<std::wstring>> Name;
        std::vector<std::shared_ptr<NamespaceItemAst>> Items;
        virtual auto accept(DocumentAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class PatternAst;
    class SetAst;
    class AutomataAst;
    class EnumAst;
    
    class NamespaceItemAstVisitor {
    public:
        virtual auto visit(const PatternAst*) -> void = 0;
        virtual auto visit(const SetAst*) -> void = 0;
        virtual auto visit(const AutomataAst*) -> void = 0;
        virtual auto visit(const EnumAst*) -> void = 0;
    };
    
    class NamespaceItemAst : public Ast {
    public:
        NamespaceItemAst(const davecommon::span &spn)
        : Ast(spn)
        { }
        
        virtual auto accept(NamespaceItemAstVisitor *visitor) const -> void = 0;
    };
    
    class ReAst;
    
    class PatternAst : public NamespaceItemAst {
    public:
        PatternAst(const davecommon::span &spn, AstToken<std::wstring> &&name, std::shared_ptr<ReAst> &&value)
        : NamespaceItemAst(spn), Name(std::move(name)), Value(std::move(value))
        { }
        AstToken<std::wstring> Name;
        std::shared_ptr<ReAst> Value;
        virtual auto accept(NamespaceItemAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class EnumAst : public NamespaceItemAst {
    public:
        EnumAst(const davecommon::span &spn, AstToken<std::wstring> &&name, std::vector<AstToken<std::wstring>> &&items)
        : NamespaceItemAst(spn), Name(std::move(name)), Items(std::move(items))
        {}
        AstToken<std::wstring> Name;
        std::vector<AstToken<std::wstring>> Items;
        virtual auto accept(NamespaceItemAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class SetItemAstVisitor;
    class SetItemAst : public Ast {
    public:
        SetItemAst(const davecommon::span &spn, bool isReturn, bool isGoto, std::vector<AstToken<std::wstring>> &&gotoLabel)
        : Ast(spn), IsReturn(isReturn), IsGoto(isGoto), GotoLabel(std::move(gotoLabel))
        { }
        
        bool IsReturn;
        bool IsGoto;
        std::vector<AstToken<std::wstring>> GotoLabel;
        virtual auto accept(SetItemAstVisitor *) const -> void = 0;
    };
    
    class MatchDefinitionAst;
    class IncludeSetAst;
    
    class SetItemAstVisitor {
    public:
        virtual auto visit(const MatchDefinitionAst*) -> void = 0;
        virtual auto visit(const IncludeSetAst*) -> void = 0;
    };
    
    class MatchDefinitionAst : public SetItemAst {
    public:
        MatchDefinitionAst(const davecommon::span &spn, std::shared_ptr<ReAst> && value, bool isReturn, bool isGoto, std::vector<AstToken<std::wstring>> &&gotoLabel, AstToken<std::wstring> &&functionName, std::vector<AstToken<std::wstring>> &&tokenName)
        : SetItemAst(spn, isReturn, isGoto, std::move(gotoLabel)), Value(std::move(value)), FunctionName(std::move(functionName)), TokenName(std::move(tokenName))
        {}
        
        std::shared_ptr<ReAst> Value;
        AstToken<std::wstring> FunctionName;
        std::vector<AstToken<std::wstring>> TokenName;
        virtual auto accept(SetItemAstVisitor *visitor) const -> void { visitor->visit(this); }
    };
    
    class IncludeSetAst : public SetItemAst {
    public:
        IncludeSetAst(const davecommon::span &spn, std::vector<AstToken<std::wstring>> &&name, bool isReturn, bool isGoto, std::vector<AstToken<std::wstring>> &&gotoLabel)
        : SetItemAst(spn, isReturn, isGoto, std::move(gotoLabel)), Name(std::move(name))
        {}
        
        std::vector<AstToken<std::wstring>> Name;
        virtual auto accept(SetItemAstVisitor *visitor) const -> void { visitor->visit(this); }
    };
    
    class SetAst : public NamespaceItemAst {
    public:
        SetAst(const davecommon::span &spn, AstToken<std::wstring> &&name, std::vector<std::shared_ptr<SetItemAst>> &&items)
        : NamespaceItemAst(spn), Name(std::move(name)), Items(std::move(items))
        {}
        AstToken<std::wstring> Name;
        std::vector<std::shared_ptr<SetItemAst>> Items;
        virtual auto accept(NamespaceItemAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class AutomataAst : public NamespaceItemAst {
    public:
        AutomataAst(const davecommon::span &spn, AstToken<std::wstring> &&name, std::vector<std::shared_ptr<SetItemAst>> &&items)
        : NamespaceItemAst(spn), Name(std::move(name)), Items(std::move(items))
        {}
        AstToken<std::wstring> Name;
        std::vector<std::shared_ptr<SetItemAst>> Items;
        virtual auto accept(NamespaceItemAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class ThenReAst;
    class OrReAst;
    class CardinalReAst;
    class ReferenceReAst;
    class CharReAst;
    class CharClassReAst;
    class CharRangesReAst;
    
    class ReAstVisitor {
    public:
        virtual auto visit(const ThenReAst*) -> void = 0;
        virtual auto visit(const OrReAst*) -> void = 0;
        virtual auto visit(const CardinalReAst*) -> void = 0;
        virtual auto visit(const ReferenceReAst*) -> void = 0;
        virtual auto visit(const CharReAst*) -> void = 0;
        virtual auto visit(const CharClassReAst*) -> void = 0;
        virtual auto visit(const CharRangesReAst*) -> void = 0;
    };
    
    class ReAst : public Ast {
    public:
        ReAst(const davecommon::span &spn)
        : Ast(spn)
        { }
        virtual auto accept(ReAstVisitor*) const -> void = 0;
    };
    
    class ThenReAst : public ReAst {
    public:
        ThenReAst(const davecommon::span &spn, std::shared_ptr<ReAst> &&re1, std::shared_ptr<ReAst> &&re2)
        : ReAst(spn), RE1(std::move(re1)), RE2(std::move(re2))
        { }
        
        std::shared_ptr<ReAst> RE1;
        std::shared_ptr<ReAst> RE2;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class OrReAst : public ReAst {
    public:
        OrReAst(const davecommon::span &spn, std::shared_ptr<ReAst> &&re1, std::shared_ptr<ReAst> &&re2)
        : ReAst(spn), RE1(std::move(re1)), RE2(std::move(re2))
        { }
        
        std::shared_ptr<ReAst> RE1;
        std::shared_ptr<ReAst> RE2;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class CardinalReAst : public ReAst {
    public:
        CardinalReAst(const davecommon::span &spn, std::shared_ptr<ReAst> &&re, int min, int max)
        : ReAst(spn), RE(std::move(re)), Min(min), Max(max)
        { }
        
        std::shared_ptr<ReAst> RE;
        int Min;
        int Max;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class ReferenceReAst : public ReAst {
    public:
        ReferenceReAst(const davecommon::span &spn, std::vector<AstToken<std::wstring>> &&name)
        : ReAst(spn), Name(std::move(name))
        { }
        
        std::vector<AstToken<std::wstring>> Name;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class CharReAst : public ReAst {
    public:
        CharReAst(const davecommon::span &spn, AstToken<wchar_t> &&ch)
        : ReAst(spn), Char(std::move(ch))
        { }
        
        AstToken<wchar_t> Char;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    enum class CharClass {
        AnyChar,
        Digit,
        Whitespace,
        Alpha,
        AlphaNum
    };
    
    class CharClassReAst : public ReAst {
    public:
        CharClassReAst(const davecommon::span &spn, AstToken<CharClass> &&charClass)
        : ReAst(spn), CharClass(std::move(charClass))
        { }
        
        AstToken<CharClass> CharClass;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class CharSetAstVisitor;
    
    class CharSetAst : public Ast {
    public:
        CharSetAst(const davecommon::span &spn)
        : Ast(spn)
        { }
        
        virtual auto accept(CharSetAstVisitor*) const -> void = 0;
    };
    
    class SingleCharAst;
    class CharRangeAst;
    
    class CharSetAstVisitor {
    public:
        virtual auto visit(const SingleCharAst*) -> void = 0;
        virtual auto visit(const CharRangeAst*) -> void = 0;
    };
    
    class SingleCharAst : public CharSetAst {
    public:
        SingleCharAst(const davecommon::span &spn, AstToken<wchar_t> &&ch)
        : CharSetAst(spn), Char(std::move(ch))
        { }
        
        AstToken<wchar_t> Char;
        
        virtual auto accept(CharSetAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class CharRangeAst : public CharSetAst {
    public:
        CharRangeAst(const davecommon::span &spn, AstToken<wchar_t> &&first, AstToken<wchar_t> &&last)
        : CharSetAst(spn), First(std::move(first)), Last(std::move(last))
        { }
        
        AstToken<wchar_t> First;
        AstToken<wchar_t> Last;
        
        virtual auto accept(CharSetAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class CharRangesReAst : public ReAst {
    public:
        CharRangesReAst(const davecommon::span &spn, bool exclude, std::vector<std::shared_ptr<CharSetAst>> &&ranges)
        : ReAst(spn), Exclude(exclude), Ranges(std::move(ranges))
        { }
        
        bool Exclude;
        std::vector<std::shared_ptr<CharSetAst>> Ranges;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };

    class Transition {
    public:
        Transition(size_t fromState, bool isEpsilon, wchar_t first, wchar_t last, size_t toState)
        : FromState(fromState), IsEpsilon(isEpsilon), First(first), Last(last), ToState(toState)
        { }

        size_t FromState;
        bool IsEpsilon;
        wchar_t First;
        wchar_t Last;
        size_t ToState;
    };

    class BuildNfaReAst : public ReAstVisitor {
    public:
        typedef std::vector<AstToken<std::wstring>> QName;
        typedef davecommon::symbol_table<QName, std::shared_ptr<PatternAst>> pattern_symbol_table;
    private:
        const std::shared_ptr<davecommon::container> &_cntr;
        davecommon::logger *_logger;
        bool &_ok;

        std::vector<Transition> &_transitions;
        size_t &_next_state;
        size_t _from;
        size_t _to;

        const std::vector<QName> &_search_namespaces;
        const pattern_symbol_table &_patterns;
    public:
        BuildNfaReAst(const std::shared_ptr<davecommon::container> &cntr, std::vector<Transition> &transitions, size_t &next_state, const size_t &from, const size_t &to, const pattern_symbol_table &patterns, const std::vector<QName> &search_namespaces, davecommon::logger *logger, bool &ok)
        : _cntr(cntr), _transitions(transitions), _next_state(next_state), _from(from), _to(to), _patterns(patterns), _logger(logger), _ok(ok), _search_namespaces(search_namespaces)
        {}

        virtual auto visit(const ThenReAst* ast) -> void {
            auto s = _next_state++;
            auto t = _to;
            _to = s;
            ast->RE1->accept(this);
            _from = s;
            _to = t;
            ast->RE2->accept(this);
        }
        virtual auto visit(const OrReAst* ast) -> void {
            auto t1 = _next_state++;
            auto t2 = _next_state++;
            auto b1 = _next_state++;
            auto b2 = _next_state++;
            auto f = _from;
            auto t = _to;
            _transitions.emplace_back(f, true, L' ', L' ', t1);
            _transitions.emplace_back(f, true, L' ', L' ', b1);
            _transitions.emplace_back(t2, true, L' ', L' ', t);
            _transitions.emplace_back(b2, true, L' ', L' ', t);
            _from = t1;
            _to = t2;
            ast->RE1->accept(this);
            _from = b1;
            _to = b2;
            ast->RE2->accept(this);
        }
        virtual auto visit(const CardinalReAst*) -> void = 0;
        virtual auto visit(const ReferenceReAst* ast) -> void;
        virtual auto visit(const CharReAst* ast) -> void {
            _transitions.emplace_back(_from, false, ast->Char.Value, ast->Char.Value, _to);
        }
        virtual auto visit(const CharClassReAst* ast) -> void {
            switch(ast->CharClass.Value) {
                case CharClass::AnyChar:
                    _transitions.emplace_back(_from, false, 0, WCHAR_MAX, _to);
                    break;
                case CharClass::Digit:
                    _transitions.emplace_back(_from, false, L'0', L'9', _to);
                    break;
                case CharClass::Whitespace:
                    _transitions.emplace_back(_from, false, L' ', L' ', _to);
                    _transitions.emplace_back(_from, false, L'\t', L'\t', _to);
                    _transitions.emplace_back(_from, false, L'\n', L'\n', _to);
                    _transitions.emplace_back(_from, false, L'\r', L'\r', _to);
                    _transitions.emplace_back(_from, false, L'\t', L'\t', _to);
                    _transitions.emplace_back(_from, false, L'\v', L'\v', _to);
                    _transitions.emplace_back(_from, false, L'\f', L'\f', _to);
                    break;
                case CharClass::Alpha:
                    _transitions.emplace_back(_from, false, L'a', L'z', _to);
                    _transitions.emplace_back(_from, false, L'A', L'Z', _to);
                    break;
                case CharClass::AlphaNum:
                    _transitions.emplace_back(_from, false, L'a', L'z', _to);
                    _transitions.emplace_back(_from, false, L'A', L'Z', _to);
                    _transitions.emplace_back(_from, false, L'0', L'9', _to);
                    break;
                default:
                    assert(false);
                    break;
            }
        }
        virtual auto visit(const CharRangesReAst* ast) -> void {
            
        }
    };
}

namespace std
{
    template<> struct hash<davecommon::position> {
        inline auto operator()(const davecommon::position &v) const -> size_t {
            return hash<long>()(v.column) + hash<long>()(v.line);
        }
    };
    
    template<> struct hash<davecommon::span> {
        inline auto operator()(const davecommon::span &v) const -> size_t {
            return hash<davecommon::position>()(v.begin) + hash<davecommon::position>()(v.end);
        }
    };
    
    template<typename T> struct hash<davelexer::AstToken<T>> {
        inline auto operator()(const davelexer::AstToken<T> &v) const -> size_t {
            return hash<davecommon::span>()(v.Spn) + hash<T>()(v.Value);
        }
    };
    
    template<> struct hash<std::vector<davelexer::AstToken<std::wstring>>> {
        inline auto operator()(const std::vector<davelexer::AstToken<std::wstring>> &v) const -> size_t {
            hash<davelexer::AstToken<std::wstring>> ha;
            size_t h = 0;
            for(auto &item : v) {
                h += ha(item);
            }
            return h;
        }
    };
    
    template<> struct equal_to<std::vector<davelexer::AstToken<std::wstring>>> {
        inline auto operator()(const std::vector<davelexer::AstToken<std::wstring>> &v1, const std::vector<davelexer::AstToken<std::wstring>> &v2) const -> bool {
            if (v1.size() == v2.size()) {
                for(size_t i = 0;i<v1.size();i++) {
                    if (!equal_to<davelexer::AstToken<std::wstring>>()(v1[i], v2[i])) {
                        return false;
                    }
                }
                return true;
            } else {
                return false;
            }
        }
    };
}

#endif /* dl_ds_hpp */






