//
//  dl.dl.cpp
//  test2
//
//  Created by David Lindeque on 16/12/2015.
//  Copyright © 2015 David Lindeque. All rights reserved.
//

#include "dl.dl.hpp"

namespace davelexer {
    struct tok {
        TokenType tt;
        std::wstring value;
        int line;
    };
    
    inline auto chars(const std::wstring &s, std::vector<tok> &tkns, int line) -> void
    {
        for(auto &ch : s) {
            std::wstring v;
            v += ch;
            tkns.push_back(tok { TokenType::Char, v, line });
        }
    }
    
    inline auto keyword(const std::wstring &name, const std::wstring &token, std::vector<tok> &tkns, int line) -> void {
        tkns.push_back(tok { TokenType::ReStart, L"", line });
        chars(name, tkns, line);
        tkns.push_back(tok { TokenType::ReEnd, L"", line });
        tkns.push_back(tok { TokenType::ProducedBy, L"", line });
        tkns.push_back(tok { TokenType::Identifier, L"keyword", line });
        tkns.push_back(tok { TokenType::Identifier, L"TokenType", line });
        tkns.push_back(tok { TokenType::Dot, L"", line });
        tkns.push_back(tok { TokenType::Identifier, token, line });
        tkns.push_back(tok { TokenType::Semicolon, L"", line });
    }
    
    inline auto value(const std::wstring &name, const std::wstring &token, std::vector<tok> &tkns, int line) -> void {
        tkns.push_back(tok { TokenType::ReStart, L"", line });
        chars(name, tkns, line);
        tkns.push_back(tok { TokenType::ReEnd, L"", line });
        tkns.push_back(tok { TokenType::ProducedBy, L"", line });
        tkns.push_back(tok { TokenType::Identifier, L"value", line });
        tkns.push_back(tok { TokenType::Identifier, L"TokenType", line });
        tkns.push_back(tok { TokenType::Dot, L"", line });
        tkns.push_back(tok { TokenType::Identifier, token, line });
        tkns.push_back(tok { TokenType::Semicolon, L"", line });
    }

    inline auto tkn(const std::wstring &name, const std::wstring &token, std::vector<tok> &tkns, int line) -> void {
        tkns.push_back(tok { TokenType::ReStart, L"", line });
        chars(name, tkns, line);
        tkns.push_back(tok { TokenType::ReEnd, L"", line });
        tkns.push_back(tok { TokenType::ProducedBy, L"", line });
        tkns.push_back(tok { TokenType::Identifier, L"token", line });
        tkns.push_back(tok { TokenType::Identifier, L"TokenType", line });
        tkns.push_back(tok { TokenType::Dot, L"", line });
        tkns.push_back(tok { TokenType::Identifier, token, line });
        tkns.push_back(tok { TokenType::Semicolon, L"", line });
    }

    inline auto tkn_with_goto(const std::wstring &name, const std::wstring _goto, const std::wstring &token, std::vector<tok> &tkns, int line) -> void {
        tkns.push_back(tok { TokenType::ReStart, L"", line });
        chars(name, tkns, line);
        tkns.push_back(tok { TokenType::ReEnd, L", line", line });
        tkns.push_back(tok { TokenType::Goto, L"", line });
        tkns.push_back(tok { TokenType::Identifier, _goto, line });
        tkns.push_back(tok { TokenType::ProducedBy, L"", line });
        tkns.push_back(tok { TokenType::Identifier, L"token", line });
        tkns.push_back(tok { TokenType::Identifier, L"TokenType", line });
        tkns.push_back(tok { TokenType::Dot, L"", line });
        tkns.push_back(tok { TokenType::Identifier, token, line });
        tkns.push_back(tok { TokenType::Semicolon, L"", line });
    }
    
    inline auto tkn_with_return(const std::wstring &name, const std::wstring _goto, const std::wstring &token, std::vector<tok> &tkns, int line) -> void {
        tkns.push_back(tok { TokenType::ReStart, L"", line });
        chars(name, tkns, line);
        tkns.push_back(tok { TokenType::ReEnd, L"", line });
        tkns.push_back(tok { TokenType::Return, L"", line });
        tkns.push_back(tok { TokenType::ProducedBy, L"", line });
        tkns.push_back(tok { TokenType::Identifier, L"token", line });
        tkns.push_back(tok { TokenType::Identifier, L"TokenType", line });
        tkns.push_back(tok { TokenType::Dot, L"", line });
        tkns.push_back(tok { TokenType::Identifier, token, line });
        tkns.push_back(tok { TokenType::Semicolon, L"", line });
    }
    
    inline auto produce(const std::wstring &action, const std::wstring &token, std::vector<tok> &tkns, int line) -> void {
        tkns.push_back(tok { TokenType::ProducedBy, L"", line });
        tkns.push_back(tok { TokenType::Identifier, action, line });
        tkns.push_back(tok { TokenType::Identifier, L"TokenType", line });
        tkns.push_back(tok { TokenType::Dot, L"", line });
        tkns.push_back(tok { TokenType::Identifier, token, line });
        tkns.push_back(tok { TokenType::Semicolon, L"", line });
    }
    
#define CHARS(s, tkns) chars(s, tkns, __LINE__)
#define TKNS(tkn, value) tkns.push_back(tok { tkn, value, __LINE__ })
#define KEYWORD(name, tkn, tkns) keyword(name, tkn, tkns, __LINE__)
#define VALUE(name, tkn, tkns) value(name, tkn, tkns, __LINE__)
#define TKN(name, tk, tkns) tkn(name, tk, tkns, __LINE__)
#define TKN_WITH_GOTO(name, _goto, tkn, tkns) tkn_with_goto(name, _goto, tkn, tkns, __LINE__)
#define TKN_WITH_RETURN(name, _goto, tkn, tkns) tkn_with_return(name, _goto, tkn, tkns, __LINE__)
#define PRODUCE(action, tkn, tkns) produce(action, tkn, tkns, __LINE__)
    
    inline auto gettokens() -> std::vector<tok> {
        std::vector<tok> tkns;
        
        TKNS(TokenType::Whitespace, L"");
        TKNS(TokenType::Comment, L"// This is a test");
        
        TKNS(TokenType::Import, L"");
        TKNS(TokenType::String, L"dl.ds");
        TKNS(TokenType::Semicolon, L"");
        
        TKNS(TokenType::Namespace, L"");
        TKNS(TokenType::Identifier, L"davelexer");
        TKNS(TokenType::OpenBrace, L"");
        
        // enum TokenType
        TKNS(TokenType::Enum, L"");
        TKNS(TokenType::Identifier, L"TokenType");
        TKNS(TokenType::OpenBrace, L"");
        TKNS(TokenType::Identifier, L"Import");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Set");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Start");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Namespace");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Enum");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Pattern");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Automata");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Include");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Goto");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Return");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Equals");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"String");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Identifier");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Number");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Dot");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Semicolon");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Comma");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Hat");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Hyphen");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"OpenBrace");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"CloseBrace");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"OpenParenthesis");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"CloseParenthesis");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"OpenSquare");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"CloseSquare");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"ProducedBy");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Comment");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Whitespace");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"ReStart");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"ReEnd");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Char");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"CharClass");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Asterisk");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Plus");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Question");
        TKNS(TokenType::Comma, L"");
        TKNS(TokenType::Identifier, L"Pipe");
        TKNS(TokenType::CloseBrace, L"");
        TKNS(TokenType::Semicolon, L"");
        
        // pattern identifier  = '[a-zA-Z_][a-zA-Z_0-9]*';
        TKNS(TokenType::Pattern, L"");
        TKNS(TokenType::Identifier, L"identifier");
        TKNS(TokenType::Equals, L"");
        TKNS(TokenType::ReStart, L"");
        TKNS(TokenType::OpenSquare, L"");
        TKNS(TokenType::Char, L"a");
        TKNS(TokenType::Hyphen, L"");
        TKNS(TokenType::Char, L"z");
        TKNS(TokenType::Char, L"A");
        TKNS(TokenType::Hyphen, L"");
        TKNS(TokenType::Char, L"Z");
        TKNS(TokenType::Char, L"_");
        TKNS(TokenType::CloseSquare, L"");
        TKNS(TokenType::OpenSquare, L"");
        TKNS(TokenType::Char, L"a");
        TKNS(TokenType::Hyphen, L"");
        TKNS(TokenType::Char, L"z");
        TKNS(TokenType::Char, L"A");
        TKNS(TokenType::Hyphen, L"");
        TKNS(TokenType::Char, L"Z");
        TKNS(TokenType::Char, L"_");
        TKNS(TokenType::Char, L"0");
        TKNS(TokenType::Hyphen, L"");
        TKNS(TokenType::Char, L"9");
        TKNS(TokenType::CloseSquare, L"");
        TKNS(TokenType::Asterisk, L"");
        TKNS(TokenType::ReEnd, L"");
        TKNS(TokenType::Semicolon, L"");
        
        // pattern string      = '"([^"]|(\\.))*"';
        TKNS(TokenType::Pattern, L"");
        TKNS(TokenType::Identifier, L"string");
        TKNS(TokenType::Equals, L"");
        TKNS(TokenType::ReStart, L"");
        TKNS(TokenType::Char, L"\"");
        TKNS(TokenType::OpenParenthesis, L"");
        TKNS(TokenType::OpenSquare, L"");
        TKNS(TokenType::Hat, L"");
        TKNS(TokenType::Char, L"\"");
        TKNS(TokenType::CloseSquare, L"");
        TKNS(TokenType::Pipe, L"");
        TKNS(TokenType::OpenParenthesis, L"");
        TKNS(TokenType::Char, L"\\");
        TKNS(TokenType::Dot, L"");
        TKNS(TokenType::CloseParenthesis, L"");
        TKNS(TokenType::CloseParenthesis, L"");
        TKNS(TokenType::Asterisk, L"");
        TKNS(TokenType::Char, L"\"");
        TKNS(TokenType::ReEnd, L"");
        TKNS(TokenType::Semicolon, L"");
        
        // pattern hex         = '[a-fA-F0-0]+';
        TKNS(TokenType::Pattern, L"");
        TKNS(TokenType::Identifier, L"hex");
        TKNS(TokenType::Equals, L"");
        TKNS(TokenType::ReStart, L"");
        TKNS(TokenType::OpenSquare, L"");
        TKNS(TokenType::Char, L"a");
        TKNS(TokenType::Hyphen, L"");
        TKNS(TokenType::Char, L"f");
        TKNS(TokenType::Char, L"A");
        TKNS(TokenType::Hyphen, L"");
        TKNS(TokenType::Char, L"F");
        TKNS(TokenType::Char, L"0");
        TKNS(TokenType::Hyphen, L"");
        TKNS(TokenType::Char, L"9");
        TKNS(TokenType::CloseSquare, L"");
        TKNS(TokenType::Plus, L"");
        TKNS(TokenType::ReEnd, L"");
        TKNS(TokenType::Semicolon, L"");
        
        // pattern int         = '0|([1-9][0-9]*)';
        TKNS(TokenType::Pattern, L"");
        TKNS(TokenType::Identifier, L"int");
        TKNS(TokenType::Equals, L"");
        TKNS(TokenType::ReStart, L"");
        TKNS(TokenType::Char, L"0");
        TKNS(TokenType::Pipe, L"");
        TKNS(TokenType::OpenParenthesis, L"");
        TKNS(TokenType::OpenSquare, L"");
        TKNS(TokenType::Char, L"1");
        TKNS(TokenType::Hyphen, L"");
        TKNS(TokenType::Char, L"9");
        TKNS(TokenType::CloseSquare, L"");
        TKNS(TokenType::OpenSquare, L"");
        TKNS(TokenType::Char, L"0");
        TKNS(TokenType::Hyphen, L"");
        TKNS(TokenType::Char, L"9");
        TKNS(TokenType::CloseSquare, L"");
        TKNS(TokenType::Asterisk, L"");
        TKNS(TokenType::CloseParenthesis, L"");
        TKNS(TokenType::ReEnd, L"");
        TKNS(TokenType::Semicolon, L"");
        
        TKNS(TokenType::Automata, L"");
        TKNS(TokenType::Identifier, L"lexer");
        TKNS(TokenType::OpenBrace, L"");
        
        // '\s+'       -> token TokenType.Whitespace;
        TKNS(TokenType::ReStart, L"");
        TKNS(TokenType::CharClass, L"s");
        TKNS(TokenType::Plus, L"");
        TKNS(TokenType::ReEnd, L"");
        TKNS(TokenType::ProducedBy, L"");
        TKNS(TokenType::Identifier, L"token");
        TKNS(TokenType::Identifier, L"TokenType");
        TKNS(TokenType::Dot, L"");
        TKNS(TokenType::Identifier, L"Whitespace");
        TKNS(TokenType::Semicolon, L"");
        
        // 'import'    -> keyword TokenType.Import;
        KEYWORD(L"import", L"Import", tkns);
        KEYWORD(L"set", L"Set", tkns);
        KEYWORD(L"start", L"Start", tkns);
        KEYWORD(L"namespace", L"Namespace", tkns);
        KEYWORD(L"pattern", L"Pattern", tkns);
        KEYWORD(L"automata", L"Automata", tkns);
        KEYWORD(L"include", L"Include", tkns);
        KEYWORD(L"goto", L"Goto", tkns);
        KEYWORD(L"return", L"Return", tkns);
        TKN(L"=", L"Equals", tkns);
        TKN(L".", L"Dot", tkns);
        TKN(L";", L"Semicolon", tkns);
        TKN(L"{", L"OpenBrace", tkns);
        TKN(L"}", L"CloseBrace", tkns);
        TKN(L"->", L"ProducedBy", tkns);
        TKN_WITH_GOTO(L"'", L"re", L"ReStart", tkns);
        TKN_WITH_GOTO(L"/*", L"comment", L"Comment", tkns);
        
        TKN(L"//\n", L"Comment", tkns);
        
        // '//[^/].*\n' -> token TokenType.Comment;
        TKNS(TokenType::ReStart, L"");
        CHARS(L"//",  tkns);
        TKNS(TokenType::OpenSquare, L"");
        TKNS(TokenType::Hat, L"");
        CHARS(L"/", tkns);
        TKNS(TokenType::CloseSquare, L"");
        TKNS(TokenType::Dot, L"");
        TKNS(TokenType::Asterisk, L"");
        CHARS(L"\n", tkns);
        TKNS(TokenType::ReEnd, L"");
        PRODUCE(L"token", L"Comment", tkns);
        
        // '////.*\n'  -> token TokenType.Comment;
        TKNS(TokenType::ReStart, L"");
        CHARS(L"////",  tkns);
        TKNS(TokenType::Dot, L"");
        TKNS(TokenType::Asterisk, L"");
        CHARS(L"\n", tkns);
        TKNS(TokenType::ReEnd, L"");
        PRODUCE(L"token", L"Comment", tkns);
        
        VALUE(L"///\n", L"Documentation", tkns);
        
        // '///[^/].*' -> value TokenType.Documentation;
        TKNS(TokenType::ReStart, L"");
        CHARS(L"///",  tkns);
        TKNS(TokenType::OpenSquare, L"");
        TKNS(TokenType::Hat, L"");
        CHARS(L"/", tkns);
        TKNS(TokenType::CloseSquare, L"");
        TKNS(TokenType::Dot, L"");
        TKNS(TokenType::Asterisk, L"");
        CHARS(L"\n", tkns);
        TKNS(TokenType::ReEnd, L"");
        PRODUCE(L"value", L"Documentation", tkns);
        
        TKNS(TokenType::ReStart, L"");
        TKNS(TokenType::OpenBrace, L"");
        TKNS(TokenType::Identifier, L"string");
        TKNS(TokenType::CloseBrace, L"");
        TKNS(TokenType::ReEnd, L"");
        PRODUCE(L"value", L"String", tkns);
        
        TKNS(TokenType::ReStart, L"");
        TKNS(TokenType::OpenBrace, L"");
        TKNS(TokenType::Identifier, L"identifier");
        TKNS(TokenType::CloseBrace, L"");
        TKNS(TokenType::ReEnd, L"");
        PRODUCE(L"value", L"Identifier", tkns);
        
        TKNS(TokenType::CloseBrace, L"");
        TKNS(TokenType::Semicolon, L"");
        
        // automata comment
        TKNS(TokenType::Automata, L"");
        TKNS(TokenType::Identifier, L"comment");
        TKNS(TokenType::OpenBrace, L"");
        TKNS(TokenType::ReStart, L"");
        CHARS(L"*/", tkns);
        TKNS(TokenType::ReEnd, L"");
        TKNS(TokenType::Return, L"");
        PRODUCE(L"token", L"Comment", tkns);
        TKNS(TokenType::ReStart, L"");
        TKNS(TokenType::Dot, L"");
        TKNS(TokenType::Asterisk, L"");
        TKNS(TokenType::ReEnd, L"");
        PRODUCE(L"token", L"Comment", tkns);
        TKNS(TokenType::CloseBrace, L"");
        TKNS(TokenType::Semicolon, L"");
        
        // set rechar
        TKNS(TokenType::Set, L"");
        TKNS(TokenType::Identifier, L"rechar");
        TKNS(TokenType::OpenBrace, L"");
        TKNS(TokenType::ReStart, L"");
        CHARS(L"\\x", tkns);
        TKNS(TokenType::OpenBrace, L"");
        TKNS(TokenType::Identifier, L"hex");
        TKNS(TokenType::CloseBrace, L"");
        TKNS(TokenType::OpenBrace, L"");
        TKNS(TokenType::Number, L"4");
        TKNS(TokenType::CloseBrace, L"");
        TKNS(TokenType::ReEnd, L"");
        TKNS(TokenType::Return, L"");
        PRODUCE(L"value", L"Char", tkns);
        TKNS(TokenType::ReStart, L"");
        TKNS(TokenType::Char, L"\\");
        TKNS(TokenType::Dot, L"");
        TKNS(TokenType::ReEnd, L"");
        PRODUCE(L"value", L"Char", tkns);
        TKNS(TokenType::ReStart, L"");
        TKNS(TokenType::Dot, L"");
        TKNS(TokenType::ReEnd, L"");
        PRODUCE(L"value", L"Char", tkns);
        TKNS(TokenType::CloseBrace, L"");
        TKNS(TokenType::Semicolon, L"");
        
        // automata re
        TKNS(TokenType::Automata, L"");
        TKNS(TokenType::Identifier, L"re");
        TKNS(TokenType::OpenBrace, L"");
        TKNS(TokenType::ReStart, L"");
        CHARS(L"'", tkns);
        TKNS(TokenType::ReEnd, L"");
        TKNS(TokenType::Return, L"");
        PRODUCE(L"token", L"ReEnd", tkns);
        TKN(L"(", L"OpenParenthesis", tkns);
        TKN(L")", L"CloseParenthesis", tkns);
        TKN_WITH_GOTO(L"{", L"rebrace", L"OpenBrace", tkns);
        TKN_WITH_GOTO(L"[", L"resqr", L"OpenSquare", tkns);
        TKN(L"*", L"Asterisk", tkns);
        TKN(L"?", L"Question", tkns);
        TKN(L"+", L"Plus", tkns);
        TKNS(TokenType::Include, L"");
        TKNS(TokenType::Identifier, L"rechar");
        TKNS(TokenType::Semicolon, L"");
        TKNS(TokenType::CloseBrace, L"");
        TKNS(TokenType::Semicolon, L"");
        
        // automata rebrace
        TKNS(TokenType::Automata, L"");
        TKNS(TokenType::Identifier, L"rebrace");
        TKNS(TokenType::OpenBrace, L"");
        TKNS(TokenType::ReStart, L"");
        CHARS(L"}", tkns);
        TKNS(TokenType::ReEnd, L"");
        TKNS(TokenType::Return, L"");
        PRODUCE(L"token", L"CloseBrace", tkns);
        TKNS(TokenType::ReStart, L"");
        TKNS(TokenType::OpenBrace, L"");
        TKNS(TokenType::Identifier, L"identifier");
        TKNS(TokenType::CloseBrace, L"");
        TKNS(TokenType::ReEnd, L"");
        PRODUCE(L"value", L"Identifier", tkns);
        TKN(L".", L"Dot", tkns);
        TKNS(TokenType::ReStart, L"");
        TKNS(TokenType::OpenBrace, L"");
        TKNS(TokenType::Identifier, L"int");
        TKNS(TokenType::CloseBrace, L"");
        TKNS(TokenType::ReEnd, L"");
        PRODUCE(L"value", L"Number", tkns);
        TKN(L",", L"Comma", tkns);
        TKNS(TokenType::CloseBrace, L"");
        TKNS(TokenType::Semicolon, L"");
        
        // automata resqr
        TKNS(TokenType::Automata, L"");
        TKNS(TokenType::Identifier, L"resqr");
        TKNS(TokenType::OpenBrace, L"");
        TKNS(TokenType::ReStart, L"");
        CHARS(L"]", tkns);
        TKNS(TokenType::ReEnd, L"");
        TKNS(TokenType::Return, L"");
        PRODUCE(L"token", L"CloseSquare", tkns);
        TKN(L"^", L"Hat", tkns);
        TKN(L"-", L"Hyphen", tkns);
        TKNS(TokenType::Include, L"");
        TKNS(TokenType::Identifier, L"rechar");
        TKNS(TokenType::Semicolon, L"");
        TKNS(TokenType::CloseBrace, L"");
        TKNS(TokenType::Semicolon, L"");
        
        TKNS(TokenType::CloseBrace, L"");
        TKNS(TokenType::Semicolon, L"");
        
        TKNS(TokenType::Set, L"");
        TKNS(TokenType::Start, L"");
        TKNS(TokenType::Equals, L"");
        TKNS(TokenType::Identifier, L"davelexer");
        TKNS(TokenType::Dot, L"");
        TKNS(TokenType::Identifier, L"lexer");
        TKNS(TokenType::Semicolon, L"");
        
        return tkns;
    }
    
    auto read_next_token(dlstate &s) -> bool
    {
        static std::vector<tok> tkns = gettokens();
     
        if (s.states.back() == tkns.size()) return false;

        s.begin.line = s.end.line = tkns[s.states.back()].line;

        s.token = tkns[s.states.back()].tt;
        s.value = tkns[s.states.back()].value;
        s.states.back()++;
        return true;
    }
}