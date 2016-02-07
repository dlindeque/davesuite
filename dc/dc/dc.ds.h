//
//  dl.ds.hpp
//  test2
//
//  Created by David Lindeque on 14/12/2015.
//  Copyright © 2015 David Lindeque. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include <map>
#include <assert.h>

#include "container.h"
#include "span.h"
#include "logger.h"
#include "spanvalue.h"
#include "symbolreference.h"
#include "containerspan.h"

namespace dc {
    
    class Ast {
    public:
        Ast(const span &spn)
        : Spn(spn)
        {}
        span Spn;
    };
    
    class StartItemAst;
    class NamespaceAst;
    class ImportAst;
    class MixinAst;
    
    class DocumentAstVisitor {
    public:
        virtual auto visit(const StartItemAst*) -> void = 0;
        virtual auto visit(const NamespaceAst*) -> void = 0;
        virtual auto visit(const ImportAst*) -> void = 0;
        virtual auto visit(const MixinAst*) -> void = 0;
    };
    
    class DocumentAst : public Ast {
    public:
        DocumentAst(const span &spn)
        : Ast(spn)
        {}
        virtual auto accept(DocumentAstVisitor*) const -> void = 0;
    };
    
    class StartItemAst : public DocumentAst {
    public:
        StartItemAst(const span &spn, symbolreference &&document)
        : DocumentAst(spn), Document(std::move(document))
        {}
        
        symbolreference Document;
        virtual auto accept(DocumentAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class ImportAst : public DocumentAst {
    public:
        ImportAst(const span &spn, spantext &&document)
        : DocumentAst(spn), Document(document)
        {}
        spantext Document;
        virtual auto accept(DocumentAstVisitor* visitor) const -> void { visitor->visit(this); }
    };

    class MixinAst : public DocumentAst {
    public:
        MixinAst(const span &spn)
        : DocumentAst(spn)
        {}
        virtual auto accept(DocumentAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class NamespaceItemAst;
    
    class NamespaceAst : public DocumentAst {
    public:
        NamespaceAst(const span &spn, symbolreference &&name, std::vector<std::shared_ptr<NamespaceItemAst>> &&items)
        : DocumentAst(spn), Name(std::move(name)), Items(std::move(items))
        {}
        
        symbolreference Name;
        std::vector<std::shared_ptr<NamespaceItemAst>> Items;
        virtual auto accept(DocumentAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class PatternAst;
    class SetAst;
    class AutomataAst;
    class EnumAst;
    class UsingNamespaceAst;
    
    class NamespaceItemAstVisitor {
    public:
        virtual auto visit(const PatternAst*) -> void = 0;
        virtual auto visit(const SetAst*) -> void = 0;
        virtual auto visit(const AutomataAst*) -> void = 0;
        virtual auto visit(const EnumAst*) -> void = 0;
        virtual auto visit(const UsingNamespaceAst*) -> void = 0;
    };
    
    class NamespaceItemAst : public Ast {
    public:
        NamespaceItemAst(const span &spn)
        : Ast(spn)
        { }
        
        virtual auto accept(NamespaceItemAstVisitor *visitor) const -> void = 0;
    };
    
    class ReAst;
    
    class PatternAst : public NamespaceItemAst {
    public:
        PatternAst(const span &spn, spantext &&name, std::shared_ptr<ReAst> &&value)
        : NamespaceItemAst(spn), Name(std::move(name)), Value(std::move(value))
        { }
        spantext Name;
        std::shared_ptr<ReAst> Value;
        virtual auto accept(NamespaceItemAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class EnumAst : public NamespaceItemAst {
    public:
        EnumAst(const span &spn, spantext &&name, std::vector<spantext> &&items)
        : NamespaceItemAst(spn), Name(std::move(name)), Items(std::move(items))
        {}
        spantext Name;
        std::vector<spantext> Items;
        virtual auto accept(NamespaceItemAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class UsingNamespaceAst : public NamespaceItemAst {
    public:
        UsingNamespaceAst(const span &spn, symbolreference &&name)
        : NamespaceItemAst(spn), Name(std::move(name))
        { }
        symbolreference Name;
        virtual auto accept(NamespaceItemAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class SetItemAstVisitor;
    class SetItemAst : public Ast {
    public:
        SetItemAst(const span &spn, bool isReturn, bool isGoto, symbolreference &&gotoLabel)
        : Ast(spn), IsReturn(isReturn), IsGoto(isGoto), GotoLabel(std::move(gotoLabel))
        { }
        
        bool IsReturn;
        bool IsGoto;
        symbolreference GotoLabel;
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
        MatchDefinitionAst(const span &spn, std::shared_ptr<ReAst> && value, bool isReturn, bool isGoto, symbolreference &&gotoLabel, spantext &&functionName, symbolreference &&tokenName)
        : SetItemAst(spn, isReturn, isGoto, std::move(gotoLabel)), Value(std::move(value)), FunctionName(std::move(functionName)), TokenName(std::move(tokenName))
        {}
        
        std::shared_ptr<ReAst> Value;
        spantext FunctionName;
        symbolreference TokenName;
        virtual auto accept(SetItemAstVisitor *visitor) const -> void { visitor->visit(this); }
    };
    
    class IncludeSetAst : public SetItemAst {
    public:
        IncludeSetAst(const span &spn, symbolreference &&name, bool isReturn, bool isGoto, symbolreference &&gotoLabel)
        : SetItemAst(spn, isReturn, isGoto, std::move(gotoLabel)), Name(std::move(name))
        {}
        
        symbolreference Name;
        virtual auto accept(SetItemAstVisitor *visitor) const -> void { visitor->visit(this); }
    };
    
    class SetAst : public NamespaceItemAst {
    public:
        SetAst(const span &spn, spantext &&name, std::vector<std::shared_ptr<SetItemAst>> &&items)
        : NamespaceItemAst(spn), Name(std::move(name)), Items(std::move(items))
        {}
        spantext Name;
        std::vector<std::shared_ptr<SetItemAst>> Items;
        virtual auto accept(NamespaceItemAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class AutomataAst : public NamespaceItemAst {
    public:
        AutomataAst(const span &spn, spantext &&name, std::vector<std::shared_ptr<SetItemAst>> &&items)
        : NamespaceItemAst(spn), Name(std::move(name)), Items(std::move(items))
        {}
        spantext Name;
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
        ReAst(const span &spn)
        : Ast(spn)
        { }
        virtual auto accept(ReAstVisitor*) const -> void = 0;
    };
    
    class ThenReAst : public ReAst {
    public:
        ThenReAst(const span &spn, std::shared_ptr<ReAst> &&re1, std::shared_ptr<ReAst> &&re2)
        : ReAst(spn), RE1(std::move(re1)), RE2(std::move(re2))
        { }
        
        std::shared_ptr<ReAst> RE1;
        std::shared_ptr<ReAst> RE2;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class OrReAst : public ReAst {
    public:
        OrReAst(const span &spn, std::shared_ptr<ReAst> &&re1, std::shared_ptr<ReAst> &&re2)
        : ReAst(spn), RE1(std::move(re1)), RE2(std::move(re2))
        { }
        
        std::shared_ptr<ReAst> RE1;
        std::shared_ptr<ReAst> RE2;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class CardinalReAst : public ReAst {
    public:
        CardinalReAst(const span &spn, std::shared_ptr<ReAst> &&re, int min, int max)
        : ReAst(spn), RE(std::move(re)), Min(min), Max(max)
        { }
        
        std::shared_ptr<ReAst> RE;
        int Min;
        int Max;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class ReferenceReAst : public ReAst {
    public:
        ReferenceReAst(const span &spn, symbolreference &&name)
        : ReAst(spn), Name(std::move(name))
        { }
        
        symbolreference Name;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class CharReAst : public ReAst {
    public:
        CharReAst(const span &spn, spanvalue<wchar_t> &&ch)
        : ReAst(spn), Char(std::move(ch))
        { }
        
        spanvalue<wchar_t> Char;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    enum class CharClass {
        AnyChar,
        Digit,
        Whitespace,
        Alpha,
        AlphaNum,
        EndOfData
    };
    
    class CharClassReAst : public ReAst {
    public:
        CharClassReAst(const span &spn, spanvalue<CharClass> &&charClass)
        : ReAst(spn), CharClass(std::move(charClass))
        { }
        
        spanvalue<CharClass> CharClass;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class CharSetAstVisitor;
    
    class CharSetAst : public Ast {
    public:
        CharSetAst(const span &spn)
        : Ast(spn)
        { }
        
        virtual auto accept(CharSetAstVisitor*) const -> void = 0;
    };
    
    class SingleCharAst;
    class CharRangeAst;
    class CharClassRangeAst;
    
    class CharSetAstVisitor {
    public:
        virtual auto visit(const SingleCharAst*) -> void = 0;
        virtual auto visit(const CharRangeAst*) -> void = 0;
        virtual auto visit(const CharClassRangeAst*) -> void = 0;
    };
    
    class SingleCharAst : public CharSetAst {
    public:
        SingleCharAst(const span &spn, spanvalue<wchar_t> &&ch)
        : CharSetAst(spn), Char(std::move(ch))
        { }
        
        spanvalue<wchar_t> Char;
        
        virtual auto accept(CharSetAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class CharRangeAst : public CharSetAst {
    public:
        CharRangeAst(const span &spn, spanvalue<wchar_t> &&first, spanvalue<wchar_t> &&last)
        : CharSetAst(spn), First(std::move(first)), Last(std::move(last))
        { }
        
        spanvalue<wchar_t> First;
        spanvalue<wchar_t> Last;
        
        virtual auto accept(CharSetAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class CharClassRangeAst : public CharSetAst {
    public:
        CharClassRangeAst(const span &spn, const CharClass &cls)
        : CharSetAst(spn), Cls(cls)
        {}
        
        CharClass Cls;
        
        virtual auto accept(CharSetAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class CharRangesReAst : public ReAst {
    public:
        CharRangesReAst(const span &spn, bool exclude, std::vector<std::shared_ptr<CharSetAst>> &&ranges)
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
        {}
        Transition(const Transition &c)
        : FromState(c.FromState), IsEpsilon(c.IsEpsilon), First(c.First), Last(c.Last), ToState(c.ToState)
        {}
        Transition(Transition &&c)
        : FromState(c.FromState), IsEpsilon(c.IsEpsilon), First(c.First), Last(c.Last), ToState(c.ToState)
        {}

        size_t FromState;
        bool IsEpsilon;
        wchar_t First;
        wchar_t Last;
        size_t ToState;

        inline auto operator =(const Transition &c) -> Transition& {
            FromState = c.FromState;
            IsEpsilon = c.IsEpsilon;
            First = c.First;
            Last = c.Last;
            ToState = c.ToState;
            return *this;
        }
        inline auto operator =(Transition &&c) -> Transition& {
            if (this != &c) {
                FromState = c.FromState;
                IsEpsilon = c.IsEpsilon;
                First = c.First;
                Last = c.Last;
                ToState = c.ToState;
            }
            return *this;
        }
    };

    struct NfaAction
    {
        int Precedence;
        spantext FunctionName;
        symbolreference TokenName;
        bool IsReturn;
        bool IsGoto;
        size_t GotoAutomata;
        containerspan cspn;
    };
    
    struct NfaActionLess {
        inline auto operator()(const NfaAction &v1, const NfaAction &v2) const -> bool {
            return v1.Precedence < v2.Precedence;
        }
    };

    class nfa {
    public:
        std::vector<Transition> transitions;
        size_t next_state = 1;
        std::unordered_map<size_t, std::set<NfaAction, NfaActionLess>> actions;
        int next_precedence = 0;
        std::unordered_map<size_t, containerspan> automataspns;
    };

    struct DfaAction
    {
        bool CanYield;
        // If we can yield
        NfaAction YieldAction;
        //// If we cannot yield
        //int RewindSteps;
        //NfaAction RewindAction;

        //bool IsAbsoluteFinalState;
    };

    class dfa {
    public:
        std::map<size_t, std::vector<Transition>> transitions;
        std::unordered_map<size_t, DfaAction> actions;
        std::unordered_map<size_t, containerspan> automataspns;
    };

    auto exclude_char_range(wchar_t first, wchar_t last, std::vector<std::pair<wchar_t, wchar_t>> &result) -> void;

    class BuildNfaReAst : public ReAstVisitor {
    private:
        std::vector<std::shared_ptr<container>> _cntr_stack;
        logger *_logger;
        bool &_ok;
        bool &_start_is_final;

        nfa &_nfa;
        size_t _from;
        size_t _to;

        const std::vector<symbolreference> &_search_namespaces;
        template<class _Action> inline static auto process_ranges(const CharClass &cls, const _Action &action) -> void {
            switch(cls) {
                case CharClass::AnyChar:
                    action(0, WCHAR_MAX - 1);
                    break;
                case CharClass::Digit:
                    action(L'0', L'9');
                    break;
                case CharClass::Whitespace:
                    action(L' ', L' ');
                    action(L'\t', L'\t');
                    action(L'\n', L'\n');
                    action(L'\r', L'\r');
                    action(L'\v', L'\v');
                    action(L'\f', L'\f');
                    break;
                case CharClass::Alpha:
                    action(L'a', L'z');
                    action(L'A', L'Z');
                    break;
                case CharClass::AlphaNum:
                    action(L'a', L'z');
                    action(L'A', L'Z');
                    action(L'0', L'9');
                    break;
                case CharClass::EndOfData:
                    action(WCHAR_MAX, WCHAR_MAX);
                    break;
                default:
                    assert(false);
                    break;
            }
        }
    public:
        BuildNfaReAst(const std::shared_ptr<container> &cntr, nfa &nfa, const size_t &from, const size_t &to, const std::vector<symbolreference> &search_namespaces, logger *logger, bool &ok, bool &start_is_final)
        : _nfa(nfa), _from(from), _to(to), _logger(logger), _ok(ok), _search_namespaces(search_namespaces), _start_is_final(start_is_final)
        {
            _cntr_stack.push_back(cntr);
        }

        virtual auto visit(const ThenReAst* ast) -> void {
            auto s = _nfa.next_state++;
            auto t = _to;
            _to = s;
            ast->RE1->accept(this);
            bool sif = _start_is_final;
            _from = s;
            _to = t;
            ast->RE2->accept(this);
            _start_is_final &= sif;
        }
        virtual auto visit(const OrReAst* ast) -> void {
            auto t1 = _nfa.next_state++;
            auto t2 = _nfa.next_state++;
            auto b1 = _nfa.next_state++;
            auto b2 = _nfa.next_state++;
            auto f = _from;
            auto t = _to;
            _nfa.transitions.emplace_back(f, true, L' ', L' ', t1);
            _nfa.transitions.emplace_back(f, true, L' ', L' ', b1);
            _nfa.transitions.emplace_back(t2, true, L' ', L' ', t);
            _nfa.transitions.emplace_back(b2, true, L' ', L' ', t);
            _from = t1;
            _to = t2;
            ast->RE1->accept(this);
            bool sif = _start_is_final;
            _from = b1;
            _to = b2;
            ast->RE2->accept(this);
            _start_is_final |= sif;
        }
        virtual auto visit(const CardinalReAst* ast) -> void;
        virtual auto visit(const ReferenceReAst* ast) -> void;
        virtual auto visit(const CharReAst* ast) -> void {
            _nfa.transitions.emplace_back(_from, false, ast->Char.value(), ast->Char.value(), _to);
            _start_is_final = false;
        }
        virtual auto visit(const CharClassReAst* ast) -> void {
            auto &nfa = _nfa;
            auto &from = _from;
            auto &to = _to;
            process_ranges(ast->CharClass.value(), [&nfa, &from, &to](const wchar_t &first, const wchar_t &last)
            {
                nfa.transitions.emplace_back(from, false, first, last, to);
            } );
            _start_is_final = false;
        }
        virtual auto visit(const CharRangesReAst* ast) -> void {
            class include_ranges_visitor : public CharSetAstVisitor {
            private:
                std::vector<std::pair<wchar_t, wchar_t>> &_ranges;
            public:
                include_ranges_visitor(std::vector<std::pair<wchar_t, wchar_t>> &ranges)
                : _ranges(ranges)
                { }

                virtual auto visit(const SingleCharAst* c) -> void {
                    _ranges.emplace_back(c->Char.value(), c->Char.value());
                }
                virtual auto visit(const CharRangeAst* c) -> void {
                    _ranges.emplace_back(c->First.value(), c->Last.value());
                }
                virtual auto visit(const CharClassRangeAst* c) -> void {
                    auto &ranges = _ranges;
                    process_ranges(c->Cls, [&ranges](const wchar_t &first, const wchar_t &last)
                    {
                        ranges.emplace_back(first, last);
                    });
                }
            };
            class exclude_ranges_visitor : public CharSetAstVisitor {
            private:
                std::vector<std::pair<wchar_t, wchar_t>> &_ranges;
            public:
                exclude_ranges_visitor(std::vector<std::pair<wchar_t, wchar_t>> &ranges)
                : _ranges(ranges)
                { }

                virtual auto visit(const SingleCharAst* c) -> void {
                    exclude_char_range(c->Char.value(), c->Char.value(), _ranges);
                }
                virtual auto visit(const CharRangeAst* c) -> void {
                    exclude_char_range(c->First.value(), c->Last.value(), _ranges);
                }
                virtual auto visit(const CharClassRangeAst* c) -> void {
                    auto &ranges = _ranges;
                    process_ranges(c->Cls, [&ranges](const wchar_t &first, const wchar_t &last)
                    {
                        exclude_char_range(first, last, ranges);
                    });
                }
            };

            assert(!ast->Ranges.empty());

            std::vector<std::pair<wchar_t, wchar_t>> ranges;
            if (ast->Exclude) {
                ranges.emplace_back((wchar_t)0, (wchar_t)WCHAR_MAX);
                exclude_ranges_visitor v(ranges);
                for(auto &r : ast->Ranges) {
                    r->accept(&v);
                }
            }
            else {
                include_ranges_visitor v(ranges);
                for(auto &r : ast->Ranges) {
                    r->accept(&v);
                }    
            }
            
            for(auto &range : ranges) {
                _nfa.transitions.emplace_back(_from, false, range.first, range.second, _to);
            }

            _start_is_final = false;
        }
    };
}







