//
//  dl.dl.hpp
//  test2
//
//  Created by David Lindeque on 16/12/2015.
//  Copyright © 2015 David Lindeque. All rights reserved.
//

#ifndef dl_dl_hpp
#define dl_dl_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include "dl.ds.hpp"

namespace davelexer
{
    template<typename _Token> class lexerstate {
    private:
        std::wistream &_stm;
        std::shared_ptr<Container> _cntr;
    public:
        lexerstate(std::wistream &stm, const std::shared_ptr<Container> &cntr)
        : _stm(stm), _cntr(cntr)
        {}
        
        std::vector<size_t> states;
        
        _Token token;
        std::wstring value;
        Point begin;
        Point end;
        
        inline auto stm() -> std::wistream& { return _stm; }
        inline auto cntr() const -> const std::shared_ptr<Container>& { return _cntr; }
        inline auto cntr() -> std::shared_ptr<Container>& { return _cntr; }
    };
    
    enum class TokenType {
        Import,
        Set,
        Start,
        Namespace,
        Enum,
        Pattern,
        Automata,
        Include,
        Goto,
        Return,
        Equals,
        String,
        Identifier,
        Number,
        Dot,
        Semicolon,
        Comma,
        Hat,
        Hyphen,
        OpenBrace,
        CloseBrace,
        OpenParenthesis,
        CloseParenthesis,
        OpenSquare,
        CloseSquare,
        ProducedBy,
        Comment,
        Whitespace,
        ReStart,
        ReEnd,
        Char,
        CharClass,
        Asterisk,
        Plus,
        Question,
        Pipe
    };
    
    inline auto text(const TokenType &value) -> std::wstring {
        switch(value) {
            case TokenType::Import: return L"Import";
            case TokenType::Set: return L"Set";
            case TokenType::Start: return L"Start";
            case TokenType::Namespace: return L"Namespace";
            case TokenType::Enum: return L"Enum";
            case TokenType::Pattern: return L"Pattern";
            case TokenType::Automata: return L"Automata";
            case TokenType::Include: return L"Include";
            case TokenType::Goto: return L"Goto";
            case TokenType::Return: return L"Return";
            case TokenType::Equals: return L"Equals";
            case TokenType::String: return L"String";
            case TokenType::Identifier: return L"Identifier";
            case TokenType::Number: return L"Number";
            case TokenType::Dot: return L"Dot";
            case TokenType::Semicolon: return L"Semicolon";
            case TokenType::Comma: return L"Comma";
            case TokenType::Hat: return L"Hat";
            case TokenType::Hyphen: return L"Hyphen";
            case TokenType::OpenBrace: return L"OpenBrace";
            case TokenType::CloseBrace: return L"CloseBrace";
            case TokenType::OpenParenthesis: return L"OpenParenthesis";
            case TokenType::CloseParenthesis: return L"CloseParenthesis";
            case TokenType::OpenSquare: return L"OpenSquare";
            case TokenType::CloseSquare: return L"CloseSquare";
            case TokenType::ProducedBy: return L"ProducedBy";
            case TokenType::Comment: return L"Comment";
            case TokenType::Whitespace: return L"Whitespace";
            case TokenType::ReStart: return L"ReStart";
            case TokenType::ReEnd: return L"ReEnd";
            case TokenType::Char: return L"Char";
            case TokenType::CharClass: return L"CharClass";
            case TokenType::Asterisk: return L"Asterisk";
            case TokenType::Plus: return L"Plus";
            case TokenType::Question: return L"Question";
            case TokenType::Pipe: return L"Pipe";
            default: return L"Unknown";
        }
    }
    
    typedef lexerstate<TokenType> dlstate;
    
    auto read_next_token(dlstate &s) -> bool;
}

#endif /* dl_dl_hpp */
