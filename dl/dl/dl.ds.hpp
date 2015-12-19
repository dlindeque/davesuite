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

namespace davelexer {
    
    class ContainerVisitor;
    
    class Container {
    public:
        virtual auto accept(ContainerVisitor*) const -> void = 0;
    };
    
    class FileContainer;
    
    class ContainerVisitor {
    public:
        virtual auto visit(const FileContainer*) -> void = 0;
    };
    
    class FileContainer : public Container {
    public:
        std::wstring FileName;
        
        virtual auto accept(ContainerVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    struct Point {
        int Line;
        int Column;
    };
    
    struct Span {
        std::shared_ptr<Container> FileName;
        Point Begin;
        Point End;
    };
    
    template<typename T> struct AstToken {
        T Value;
        Span Spn;
    };
    
    class Ast {
    public:
        Span Spn;
    };
    
    class StartAutomataAst;
    class NamespaceAst;
    
    class DocumentAstVisitor {
    public:
        virtual auto visit(const StartAutomataAst*) -> void = 0;
        virtual auto visit(const NamespaceAst*) -> void = 0;
    };
    
    class DocumentAst : public Ast {
    public:
        virtual auto accept(DocumentAstVisitor*) const -> void = 0;
    };
    
    class StartAutomataAst : public DocumentAst {
    public:
        AstToken<std::wstring> Document;
        virtual auto accept(DocumentAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class NamespaceItemAst;
    
    class NamespaceAst : public DocumentAst {
    public:
        AstToken<std::wstring> Name;
        std::vector<std::shared_ptr<NamespaceItemAst>> Items;
        virtual auto accept(DocumentAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class PatternAst;
    class SetAst;
    class AutomataAst;
    
    class NamespaceItemAstVisitor {
    public:
        virtual auto visit(const PatternAst*) -> void = 0;
        virtual auto visit(const SetAst*) -> void = 0;
        virtual auto visit(const AutomataAst*) -> void = 0;
    };
    
    class NamespaceItemAst : public Ast {
    public:
        virtual auto accept(NamespaceItemAstVisitor *visitor) const -> void = 0;
    };
    
    class ReAst;
    
    class PatternAst : public NamespaceItemAst {
    public:
        AstToken<std::wstring> Name;
        std::shared_ptr<ReAst> Value;
        virtual auto accept(NamespaceItemAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class SetItemAstVisitor;
    class SetItemAst : public Ast {
    public:
        bool IsReturn;
        bool IsGoto;
        AstToken<std::wstring> GotoLabel;
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
        AstToken<std::wstring> Name;
        std::shared_ptr<ReAst> Value;
        virtual auto accept(SetItemAstVisitor *visitor) const -> void { visitor->visit(this); }
    };
    
    class IncludeSetAst : public SetItemAst {
    public:
        AstToken<std::wstring> Name;
        virtual auto accept(SetItemAstVisitor *visitor) const -> void { visitor->visit(this); }
    };
    
    class SetAst : public NamespaceItemAst {
    public:
        AstToken<std::wstring> Name;
        std::vector<std::shared_ptr<SetItemAst>> Items;
        virtual auto accept(NamespaceItemAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class AutomataAst : public NamespaceItemAst {
    public:
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
    
    class ReAst {
    public:
        virtual auto accept(ReAstVisitor*) const -> void = 0;
    };
    
    class ThenReAst : public ReAst {
    public:
        std::shared_ptr<ReAst> RE1;
        std::shared_ptr<ReAst> RE2;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class OrReAst : public ReAst {
    public:
        std::shared_ptr<ReAst> RE1;
        std::shared_ptr<ReAst> RE2;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class CardinalReAst : public ReAst {
    public:
        std::shared_ptr<ReAst> RE;
        int Min;
        int Max;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class ReferenceReAst : public ReAst {
    public:
        AstToken<std::wstring> Name;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class CharReAst : public ReAst {
    public:
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
        CharClass CharClass;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
    
    class CharSetAstVisitor;
    
    class CharSetAst : public Ast {
    public:
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
        AstToken<wchar_t> Char;
        
        virtual auto accept(CharSetAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class CharRangeAst : public CharSetAst {
    public:
        AstToken<wchar_t> First;
        AstToken<wchar_t> Last;
        
        virtual auto accept(CharSetAstVisitor* visitor) const -> void { visitor->visit(this); }
    };
    
    class CharRangesReAst : public ReAst {
    public:
        AstToken<bool> Exclude;
        std::vector<std::shared_ptr<CharSetAst>> Ranges;
        
        virtual auto accept(ReAstVisitor * visitor) const -> void { visitor->visit(this); }
    };
}

#endif /* dl_ds_hpp */






