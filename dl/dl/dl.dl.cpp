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
    };
    
    inline auto chars(const std::wstring &s, std::vector<tok> &tkns) -> void
    {
        for(auto &ch : s) {
            std::wstring v;
            v += ch;
            tkns.push_back(tok { TokenType::Char, v });
        }
    }
    
    inline auto keyword(const std::wstring &name, const std::wstring &token, std::vector<tok> &tkns) -> void {
        tkns.push_back(tok { TokenType::ReStart, L"" });
        chars(name, tkns);
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        tkns.push_back(tok { TokenType::ProducedBy, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"keyword" });
        tkns.push_back(tok { TokenType::Identifier, L"TokenType" });
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::Identifier, token });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
    }
    
    inline auto value(const std::wstring &name, const std::wstring &token, std::vector<tok> &tkns) -> void {
        tkns.push_back(tok { TokenType::ReStart, L"" });
        chars(name, tkns);
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        tkns.push_back(tok { TokenType::ProducedBy, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"value" });
        tkns.push_back(tok { TokenType::Identifier, L"TokenType" });
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::Identifier, token });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
    }

    inline auto tkn(const std::wstring &name, const std::wstring &token, std::vector<tok> &tkns) -> void {
        tkns.push_back(tok { TokenType::ReStart, L"" });
        chars(name, tkns);
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        tkns.push_back(tok { TokenType::ProducedBy, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"token" });
        tkns.push_back(tok { TokenType::Identifier, L"TokenType" });
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::Identifier, token });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
    }

    inline auto tkn_with_goto(const std::wstring &name, const std::wstring _goto, const std::wstring &token, std::vector<tok> &tkns) -> void {
        tkns.push_back(tok { TokenType::ReStart, L"" });
        chars(name, tkns);
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        tkns.push_back(tok { TokenType::Goto, L"" });
        tkns.push_back(tok { TokenType::Identifier, _goto });
        tkns.push_back(tok { TokenType::ProducedBy, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"token" });
        tkns.push_back(tok { TokenType::Identifier, L"TokenType" });
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::Identifier, token });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
    }
    
    inline auto tkn_with_return(const std::wstring &name, const std::wstring _goto, const std::wstring &token, std::vector<tok> &tkns) -> void {
        tkns.push_back(tok { TokenType::ReStart, L"" });
        chars(name, tkns);
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        tkns.push_back(tok { TokenType::Return, L"" });
        tkns.push_back(tok { TokenType::ProducedBy, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"token" });
        tkns.push_back(tok { TokenType::Identifier, L"TokenType" });
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::Identifier, token });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
    }
    
    inline auto produce(const std::wstring &action, const std::wstring &token, std::vector<tok> &tkns) -> void {
        tkns.push_back(tok { TokenType::ProducedBy, L"" });
        tkns.push_back(tok { TokenType::Identifier, action });
        tkns.push_back(tok { TokenType::Identifier, L"TokenType" });
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::Identifier, token });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
    }
    
    inline auto gettokens() -> std::vector<tok> {
        std::vector<tok> tkns;
        
        tkns.push_back(tok { TokenType::Whitespace, L"" });
        tkns.push_back(tok { TokenType::Comment, L"// This is a test" });
        
        tkns.push_back(tok { TokenType::Import, L"" });
        tkns.push_back(tok { TokenType::String, L"dl.ds" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        tkns.push_back(tok { TokenType::Namespace, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"davelexer" });
        tkns.push_back(tok { TokenType::OpenBrace, L"" });
        
        // enum TokenType
        tkns.push_back(tok { TokenType::Enum, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"TokenType" });
        tkns.push_back(tok { TokenType::OpenBrace, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Import" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Set" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Start" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Namespace" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Enum" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Pattern" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Automata" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Include" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Goto" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Return" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Equals" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"String" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Identifier" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Number" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Dot" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Semicolon" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Comma" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Hat" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Hyphen" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"OpenBrace" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"CloseBrace" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"OpenParenthesis" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"CloseParenthesis" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"OpenSquare" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"CloseSquare" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"ProducedBy" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Comment" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Whitespace" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"ReStart" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"ReEnd" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Char" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"CharClass" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Asterisk" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Plus" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Question" });
        tkns.push_back(tok { TokenType::Comma, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Pipe" });
        tkns.push_back(tok { TokenType::CloseBrace, L"" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        // pattern identifier  = '[a-zA-Z_][a-zA-Z_0-9]*';
        tkns.push_back(tok { TokenType::Pattern, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"identifier" });
        tkns.push_back(tok { TokenType::Equals, L"" });
        tkns.push_back(tok { TokenType::ReStart, L"" });
        tkns.push_back(tok { TokenType::OpenSquare, L"" });
        tkns.push_back(tok { TokenType::Char, L"a" });
        tkns.push_back(tok { TokenType::Hyphen, L"" });
        tkns.push_back(tok { TokenType::Char, L"z" });
        tkns.push_back(tok { TokenType::Char, L"A" });
        tkns.push_back(tok { TokenType::Hyphen, L"" });
        tkns.push_back(tok { TokenType::Char, L"Z" });
        tkns.push_back(tok { TokenType::Char, L"_" });
        tkns.push_back(tok { TokenType::CloseSquare, L"" });
        tkns.push_back(tok { TokenType::OpenSquare, L"" });
        tkns.push_back(tok { TokenType::Char, L"a" });
        tkns.push_back(tok { TokenType::Hyphen, L"" });
        tkns.push_back(tok { TokenType::Char, L"z" });
        tkns.push_back(tok { TokenType::Char, L"A" });
        tkns.push_back(tok { TokenType::Hyphen, L"" });
        tkns.push_back(tok { TokenType::Char, L"Z" });
        tkns.push_back(tok { TokenType::Char, L"_" });
        tkns.push_back(tok { TokenType::Char, L"0" });
        tkns.push_back(tok { TokenType::Hyphen, L"" });
        tkns.push_back(tok { TokenType::Char, L"9" });
        tkns.push_back(tok { TokenType::CloseSquare, L"" });
        tkns.push_back(tok { TokenType::Asterisk, L"" });
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        // pattern string      = '"([^"]|(\\.))*"';
        tkns.push_back(tok { TokenType::Pattern, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"string" });
        tkns.push_back(tok { TokenType::Equals, L"" });
        tkns.push_back(tok { TokenType::ReStart, L"" });
        tkns.push_back(tok { TokenType::Char, L"\"" });
        tkns.push_back(tok { TokenType::OpenParenthesis, L"" });
        tkns.push_back(tok { TokenType::OpenSquare, L"" });
        tkns.push_back(tok { TokenType::Hat, L"" });
        tkns.push_back(tok { TokenType::Char, L"\"" });
        tkns.push_back(tok { TokenType::CloseSquare, L"" });
        tkns.push_back(tok { TokenType::Pipe, L"" });
        tkns.push_back(tok { TokenType::OpenParenthesis, L"" });
        tkns.push_back(tok { TokenType::Char, L"\\" });
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::CloseParenthesis, L"" });
        tkns.push_back(tok { TokenType::CloseParenthesis, L"" });
        tkns.push_back(tok { TokenType::Asterisk, L"" });
        tkns.push_back(tok { TokenType::Char, L"\"" });
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        // pattern hex         = '[a-fA-F0-0]+';
        tkns.push_back(tok { TokenType::Pattern, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"hex" });
        tkns.push_back(tok { TokenType::Equals, L"" });
        tkns.push_back(tok { TokenType::ReStart, L"" });
        tkns.push_back(tok { TokenType::OpenSquare, L"" });
        tkns.push_back(tok { TokenType::Char, L"a" });
        tkns.push_back(tok { TokenType::Hyphen, L"" });
        tkns.push_back(tok { TokenType::Char, L"f" });
        tkns.push_back(tok { TokenType::Char, L"A" });
        tkns.push_back(tok { TokenType::Hyphen, L"" });
        tkns.push_back(tok { TokenType::Char, L"F" });
        tkns.push_back(tok { TokenType::Char, L"0" });
        tkns.push_back(tok { TokenType::Hyphen, L"" });
        tkns.push_back(tok { TokenType::Char, L"9" });
        tkns.push_back(tok { TokenType::CloseSquare, L"" });
        tkns.push_back(tok { TokenType::Plus, L"" });
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        // pattern int         = '0|([1-9][0-9]*)';
        tkns.push_back(tok { TokenType::Pattern, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"int" });
        tkns.push_back(tok { TokenType::Equals, L"" });
        tkns.push_back(tok { TokenType::ReStart, L"" });
        tkns.push_back(tok { TokenType::Char, L"0" });
        tkns.push_back(tok { TokenType::Pipe, L"" });
        tkns.push_back(tok { TokenType::OpenParenthesis, L"" });
        tkns.push_back(tok { TokenType::OpenSquare, L"" });
        tkns.push_back(tok { TokenType::Char, L"1" });
        tkns.push_back(tok { TokenType::Hyphen, L"" });
        tkns.push_back(tok { TokenType::Char, L"9" });
        tkns.push_back(tok { TokenType::CloseSquare, L"" });
        tkns.push_back(tok { TokenType::OpenSquare, L"" });
        tkns.push_back(tok { TokenType::Char, L"0" });
        tkns.push_back(tok { TokenType::Hyphen, L"" });
        tkns.push_back(tok { TokenType::Char, L"9" });
        tkns.push_back(tok { TokenType::CloseSquare, L"" });
        tkns.push_back(tok { TokenType::Asterisk, L"" });
        tkns.push_back(tok { TokenType::CloseParenthesis, L"" });
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        tkns.push_back(tok { TokenType::Automata, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"lexer" });
        tkns.push_back(tok { TokenType::OpenBrace, L"" });
        
        // '\s+'       -> token TokenType.Whitespace;
        tkns.push_back(tok { TokenType::ReStart, L"" });
        tkns.push_back(tok { TokenType::CharClass, L"s" });
        tkns.push_back(tok { TokenType::Plus, L"" });
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        tkns.push_back(tok { TokenType::ProducedBy, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"token" });
        tkns.push_back(tok { TokenType::Identifier, L"TokenType" });
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"Whitespace" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        // 'import'    -> keyword TokenType.Import;
        keyword(L"import", L"Import", tkns);
        keyword(L"set", L"Set", tkns);
        keyword(L"start", L"Start", tkns);
        keyword(L"namespace", L"Namespace", tkns);
        keyword(L"pattern", L"Pattern", tkns);
        keyword(L"automata", L"Automata", tkns);
        keyword(L"include", L"Include", tkns);
        keyword(L"goto", L"Goto", tkns);
        keyword(L"return", L"Return", tkns);
        tkn(L"=", L"Equals", tkns);
        tkn(L".", L"Dot", tkns);
        tkn(L";", L"Semicolon", tkns);
        tkn(L"{", L"OpenBrace", tkns);
        tkn(L"}", L"CloseBrace", tkns);
        tkn(L"->", L"ProducedBy", tkns);
        tkn_with_goto(L"'", L"re", L"ReStart", tkns);
        tkn_with_goto(L"/*", L"comment", L"Comment", tkns);
        
        tkn(L"//\n", L"Comment", tkns);
        
        // '//[^/].*\n' -> token TokenType.Comment;
        tkns.push_back(tok { TokenType::ReStart, L"" });
        chars(L"//",  tkns);
        tkns.push_back(tok { TokenType::OpenSquare, L"" });
        tkns.push_back(tok { TokenType::Hat, L"" });
        chars(L"/", tkns);
        tkns.push_back(tok { TokenType::CloseSquare, L"" });
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::Asterisk, L"" });
        chars(L"\n", tkns);
        produce(L"token", L"Comment", tkns);
        
        // '////.*\n'  -> token TokenType.Comment;
        tkns.push_back(tok { TokenType::ReStart, L"" });
        chars(L"////",  tkns);
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::Asterisk, L"" });
        chars(L"\n", tkns);
        produce(L"token", L"Comment", tkns);
        
        value(L"///\n", L"Documentation", tkns);
        
        // '///[^/].*' -> value TokenType.Documentation;
        tkns.push_back(tok { TokenType::ReStart, L"" });
        chars(L"///",  tkns);
        tkns.push_back(tok { TokenType::OpenSquare, L"" });
        tkns.push_back(tok { TokenType::Hat, L"" });
        chars(L"/", tkns);
        tkns.push_back(tok { TokenType::CloseSquare, L"" });
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::Asterisk, L"" });
        chars(L"\n", tkns);
        produce(L"value", L"Documentation", tkns);

        tkns.push_back(tok { TokenType::ReStart, L"" });
        tkns.push_back(tok { TokenType::OpenBrace, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"string" });
        tkns.push_back(tok { TokenType::CloseBrace, L"" });
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        produce(L"value", L"String", tkns);
        
        tkns.push_back(tok { TokenType::ReStart, L"" });
        tkns.push_back(tok { TokenType::OpenBrace, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"identifier" });
        tkns.push_back(tok { TokenType::CloseBrace, L"" });
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        produce(L"value", L"Identifier", tkns);
        
        tkns.push_back(tok { TokenType::CloseBrace, L"" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        // automata comment
        tkns.push_back(tok { TokenType::Automata, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"comment" });
        tkns.push_back(tok { TokenType::OpenBrace, L"" });
        chars(L"*/", tkns);
        tkns.push_back(tok { TokenType::Return, L"" });
        produce(L"token", L"Comment", tkns);
        tkns.push_back(tok { TokenType::ReStart, L"" });
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::Asterisk, L"" });
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        produce(L"token", L"Comment", tkns);
        tkns.push_back(tok { TokenType::CloseBrace, L"" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        // set rechar
        tkns.push_back(tok { TokenType::Set, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"rechar" });
        tkns.push_back(tok { TokenType::OpenBrace, L"" });
        tkns.push_back(tok { TokenType::ReStart, L"" });
        chars(L"\\x", tkns);
        tkns.push_back(tok { TokenType::OpenBrace, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"hex" });
        tkns.push_back(tok { TokenType::CloseBrace, L"" });
        tkns.push_back(tok { TokenType::OpenBrace, L"" });
        tkns.push_back(tok { TokenType::Number, L"4" });
        tkns.push_back(tok { TokenType::CloseBrace, L"" });
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        tkns.push_back(tok { TokenType::Return, L"" });
        produce(L"value", L"Char", tkns);
        tkns.push_back(tok { TokenType::ReStart, L"" });
        tkns.push_back(tok { TokenType::Char, L"\\" });
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        produce(L"value", L"Char", tkns);
        tkns.push_back(tok { TokenType::ReStart, L"" });
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        produce(L"value", L"Char", tkns);
        tkns.push_back(tok { TokenType::CloseBrace, L"" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        // automata re
        tkns.push_back(tok { TokenType::Automata, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"re" });
        tkns.push_back(tok { TokenType::OpenBrace, L"" });
        tkns.push_back(tok { TokenType::ReStart, L"" });
        chars(L"'", tkns);
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        tkns.push_back(tok { TokenType::Return, L"" });
        produce(L"token", L"ReEnd", tkns);
        tkn(L"(", L"OpenParenthesis", tkns);
        tkn(L")", L"CloseParenthesis", tkns);
        tkn_with_goto(L"{", L"rebrace", L"OpenBrace", tkns);
        tkn_with_goto(L"[", L"resqr", L"OpenSquare", tkns);
        tkn(L"*", L"Asterisk", tkns);
        tkn(L"?", L"Question", tkns);
        tkn(L"+", L"Plus", tkns);
        tkns.push_back(tok { TokenType::Include, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"rechar" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        tkns.push_back(tok { TokenType::CloseBrace, L"" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        // automata rebrace
        tkns.push_back(tok { TokenType::Automata, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"rebrace" });
        tkns.push_back(tok { TokenType::OpenBrace, L"" });
        tkns.push_back(tok { TokenType::ReStart, L"" });
        chars(L"}", tkns);
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        tkns.push_back(tok { TokenType::Return, L"" });
        produce(L"token", L"CloseBrace", tkns);
        tkns.push_back(tok { TokenType::ReStart, L"" });
        tkns.push_back(tok { TokenType::OpenBrace, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"identifier" });
        tkns.push_back(tok { TokenType::CloseBrace, L"" });
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        produce(L"value", L"Identifier", tkns);
        tkn(L".", L"Dot", tkns);
        tkns.push_back(tok { TokenType::ReStart, L"" });
        tkns.push_back(tok { TokenType::OpenBrace, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"int" });
        tkns.push_back(tok { TokenType::CloseBrace, L"" });
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        produce(L"value", L"Number", tkns);
        tkn(L",", L"Comma", tkns);
        tkns.push_back(tok { TokenType::CloseBrace, L"" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        // automata resqr
        tkns.push_back(tok { TokenType::Automata, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"resqr" });
        tkns.push_back(tok { TokenType::OpenBrace, L"" });
        tkns.push_back(tok { TokenType::ReStart, L"" });
        chars(L"]", tkns);
        tkns.push_back(tok { TokenType::ReEnd, L"" });
        tkns.push_back(tok { TokenType::Return, L"" });
        produce(L"token", L"CloseSquare", tkns);
        tkn(L"^", L"Hat", tkns);
        tkn(L"-", L"Hyphen", tkns);
        tkns.push_back(tok { TokenType::Include, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"rechar" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        tkns.push_back(tok { TokenType::CloseBrace, L"" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        tkns.push_back(tok { TokenType::CloseBrace, L"" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        tkns.push_back(tok { TokenType::Set, L"" });
        tkns.push_back(tok { TokenType::Start, L"" });
        tkns.push_back(tok { TokenType::Equals, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"davelexer" });
        tkns.push_back(tok { TokenType::Dot, L"" });
        tkns.push_back(tok { TokenType::Identifier, L"lexer" });
        tkns.push_back(tok { TokenType::Semicolon, L"" });
        
        return tkns;
    }
    
    auto read_next_token(dlstate &s) -> bool
    {
        static std::vector<tok> tkns = gettokens();
     
        if (s.states.back() == tkns.size()) return false;
        
        s.token = tkns[s.states.back()].tt;
        s.value = tkns[s.states.back()].value;
        s.states.back()++;
        return true;
    }
}