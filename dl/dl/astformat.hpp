#include <iostream>

namespace davelexer
{
	inline auto write_qname(std::wostream &stm, const std::vector<AstToken<std::wstring>> &qname) -> std::wostream& {
    if (!qname.empty()) {
        stm << qname[0].Value;
        for(size_t i = 1; i < qname.size(); i++) {
            stm << L'.' << qname[i].Value;
        }
    }
    return stm;
}
        
inline auto write_char(std::wostream &stm, const wchar_t ch) -> std::wostream& {
    switch(ch) {
        case L'\n': stm << L"\\n"; break;
        case L'\r': stm << L"\\r"; break;
        case L'\t': stm << L"\\t"; break;
        case L'\v': stm << L"\\v"; break;
        case L'\f': stm << L"\\f"; break;
        case L'\b': stm << L"\\b"; break;
        case L'.': stm << L"\\."; break;
        case L'*': stm << L"\\*"; break;
        case L'+': stm << L"\\+"; break;
        case L'?': stm << L"\\?"; break;
        case L'(': stm << L"\\("; break;
        case L')': stm << L"\\)"; break;
        case L'[': stm << L"\\["; break;
        case L']': stm << L"\\]"; break;
        case L'{': stm << L"\\{"; break;
        case L'}': stm << L"\\}"; break;
        case L'\'': stm << L"\\'"; break;
        default: stm << ch;
    }    
    return stm;
}

class ReAstFormatter : public ReAstVisitor {
private:
    std::wostream &_stm;
public:
    ReAstFormatter(std::wostream &stm)
    : _stm(stm)
    {}

    virtual auto visit(const ThenReAst* ast) -> void {
        ast->RE1->accept(this);
        ast->RE2->accept(this);
    }
    virtual auto visit(const OrReAst* ast) -> void {
        _stm << L'(';
        ast->RE1->accept(this);
        _stm << L")|(";
        ast->RE2->accept(this);
        _stm << L')';
    }
    virtual auto visit(const CardinalReAst* ast) -> void {
        _stm << L'(';
        ast->RE->accept(this);
        _stm << L')';
        if (ast->Max == -1) {
            switch(ast->Min) {
                case 0:
                    _stm << L'*';
                    break;
                case 1:
                    _stm << L'+';
                    break;
                default:
                    if (ast->Min == ast->Max) {
                        _stm << L'{' << ast->Min << L'}';
                    } else {
                        _stm << L'{' << ast->Min << L',' << ast->Max << L'}';
                    }
                    break;
            }
        } else if (ast->Min == 0 && ast->Max == 1) {
            _stm << L'?';
        } else {
            if (ast->Min == ast->Max) {
                _stm << L'{' << ast->Min << L'}';
            } else {
                _stm << L'{' << ast->Min << L',' << ast->Max << L'}';
            }
        }
    }
    virtual auto visit(const ReferenceReAst* ast) -> void {
        _stm << L'{';
        write_qname(_stm, ast->Name) << L'}';
    }
    virtual auto visit(const CharReAst* ast) -> void {
        write_char(_stm, ast->Char.Value);
    }
    virtual auto visit(const CharClassReAst* ast) -> void {
        switch(ast->CharClass.Value) {
            case CharClass::Alpha:
                _stm << L"\\a";
                break;
            case CharClass::Digit:
                _stm << L"\\d";
                break;
            case CharClass::AlphaNum:
                _stm << L"\\n";
                break;
            case CharClass::AnyChar:
                _stm << L".";
                break;
            case CharClass::Whitespace:
                _stm << L"\\s";
                break;
            default:
                _stm << L"UNKNOWN";
                break;
        }
    }
    virtual auto visit(const CharRangesReAst* ast) -> void {
        class CharSetAstFormatter : public CharSetAstVisitor {
        private:
            std::wostream &_stm;
        public:
            CharSetAstFormatter(std::wostream &stm)
            : _stm(stm)
            { }
            
            virtual auto visit(const SingleCharAst* ast) -> void {
                write_char(_stm, ast->Char.Value);
            }
            virtual auto visit(const CharRangeAst* ast) -> void {
                write_char(_stm, ast->First.Value) << L'-';
                write_char(_stm, ast->Last.Value);
            }
        } fmt(_stm);
        
        
        _stm << L'[';
        if (ast->Exclude) {
            _stm << L'^';
        }
        for(auto &range : ast->Ranges) {
            range->accept(&fmt);
        }
        _stm << L']';
    }
};

inline auto format_re(std::wostream &stm, const std::shared_ptr<ReAst> &ast) -> std::wostream&
{
    ReAstFormatter fmt(stm);
    stm << L'\'';
    ast->accept(&fmt);
    stm << L'\'';
    return stm;
}
        
class SetItemAstFormatter : public SetItemAstVisitor {
private:
    std::wostream &_stm;
public:
    SetItemAstFormatter(std::wostream &stm)
    : _stm(stm)
    {}

    virtual auto visit(const MatchDefinitionAst* ast) -> void {
        _stm << L"    ";
        format_re(_stm, ast->Value);
        if (ast->IsReturn) {
            _stm << L" return";
        } else if (ast->IsGoto) {
            _stm << L" goto ";
            write_qname(_stm, ast->GotoLabel);
        }
        _stm << L" -> " << ast->FunctionName.Value << L' ';
        write_qname(_stm, ast->TokenName) << L";" << std::endl;
    }
    virtual auto visit(const IncludeSetAst* ast) -> void {
        _stm << L"    include ";
        write_qname(_stm, ast->Name);
        if (ast->IsReturn) {
            _stm << L" return";
        } else if (ast->IsGoto) {
            _stm << L" goto ";
            write_qname(_stm, ast->GotoLabel);
        }
        _stm << L';' << std::endl;
    }
};
        
class NamespaceItemAstFormatter : public NamespaceItemAstVisitor {
private:
    std::wostream &_stm;
public:
    NamespaceItemAstFormatter(std::wostream &stm)
    : _stm(stm)
    { }

    virtual auto visit(const PatternAst *ast) -> void {
        _stm << L"  pattern " << ast->Name.Value << L" = ";
        format_re(_stm, ast->Value) << L";" << std::endl;
    }
    virtual auto visit(const SetAst* ast) -> void {
        _stm << L"  set " << ast->Name.Value << L" {" << std::endl;
        SetItemAstFormatter fmt(_stm);
        for(auto &si : ast->Items) {
            si->accept(&fmt);
        }
        _stm << L"  };" << std::endl;
    }
    virtual auto visit(const AutomataAst* ast) -> void {
        _stm << L"  automata " << ast->Name.Value << L" {" << std::endl;
        SetItemAstFormatter fmt(_stm);
        for(auto &si : ast->Items) {
            si->accept(&fmt);
        }
        _stm << L"  };" << std::endl;
    }
    virtual auto visit(const EnumAst* ast) -> void {
        _stm << L"  enum " << ast->Name.Value << L" {" << std::endl;
        for(auto &item : ast->Items) {
            _stm << L"    " << item.Value << L',' << std::endl;
        }
        _stm << L"  };" << std::endl;
    }
};
        
class DocumentAstFormatter : public DocumentAstVisitor {
private:
    std::wostream &_stm;
public:
    DocumentAstFormatter(std::wostream &stm)
    : _stm(stm)
    {}
    virtual auto visit(const StartAutomataAst* ast) -> void {
        _stm << L"set start = ";
        write_qname(_stm, ast->Document) << L";" << std::endl;
    }
    virtual auto visit(const NamespaceAst* ast) -> void {
        _stm << L"namespace ";
        write_qname(_stm, ast->Name) << L" {" << std::endl;
        NamespaceItemAstFormatter fmt(_stm);
        for(auto &ni : ast->Items) {
            ni->accept(&fmt);
        }
        _stm << L"};" << std::endl;
    }
    virtual auto visit(const ImportAst* ast) -> void {
        _stm << L"import \"" << ast->Document.Value << "\";" << std::endl;
    }
};
}