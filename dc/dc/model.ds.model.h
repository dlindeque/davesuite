// Generated by Dave Compiler

#pragma once

#include <iostream>
#include <memory>
namespace dc2 {
    
}
namespace dc {
    enum class TokenType;
}
namespace dc2 {
    class position;
    class span;
    template<typename T> class spanvalue;
    
}
namespace dc2 {
    
}
namespace dc {
    // Represents the types of tokens in a ds file
    enum class TokenType {
        // Import another file
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
        OpenTriangle,
        CloseTriangle,
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
        Pipe,
        // Indicates an error in lexical analysis
        Error,
        EOD,
        Documentation,
        Production,
        Type,
        Abstract,
        Sealed,
        Alias,
        Colon,
        Word,
        DWord,
        Int8,
        Int16,
        Int32,
        Int64,
        StringKeyword,
        WString,
        FloatKeyword,
        DFloat,
    };
    
    inline auto operator <<(std::wostream &os, const TokenType &v) -> std::wostream& {
        switch(v) {
        case TokenType::Import: return os << L"Import";
        case TokenType::Set: return os << L"Set";
        case TokenType::Start: return os << L"Start";
        case TokenType::Namespace: return os << L"Namespace";
        case TokenType::Enum: return os << L"Enum";
        case TokenType::Pattern: return os << L"Pattern";
        case TokenType::Automata: return os << L"Automata";
        case TokenType::Include: return os << L"Include";
        case TokenType::Goto: return os << L"Goto";
        case TokenType::Return: return os << L"Return";
        case TokenType::Equals: return os << L"Equals";
        case TokenType::String: return os << L"String";
        case TokenType::Identifier: return os << L"Identifier";
        case TokenType::Number: return os << L"Number";
        case TokenType::Dot: return os << L"Dot";
        case TokenType::Semicolon: return os << L"Semicolon";
        case TokenType::Comma: return os << L"Comma";
        case TokenType::Hat: return os << L"Hat";
        case TokenType::Hyphen: return os << L"Hyphen";
        case TokenType::OpenBrace: return os << L"OpenBrace";
        case TokenType::CloseBrace: return os << L"CloseBrace";
        case TokenType::OpenParenthesis: return os << L"OpenParenthesis";
        case TokenType::CloseParenthesis: return os << L"CloseParenthesis";
        case TokenType::OpenSquare: return os << L"OpenSquare";
        case TokenType::CloseSquare: return os << L"CloseSquare";
        case TokenType::OpenTriangle: return os << L"OpenTriangle";
        case TokenType::CloseTriangle: return os << L"CloseTriangle";
        case TokenType::ProducedBy: return os << L"ProducedBy";
        case TokenType::Comment: return os << L"Comment";
        case TokenType::Whitespace: return os << L"Whitespace";
        case TokenType::ReStart: return os << L"ReStart";
        case TokenType::ReEnd: return os << L"ReEnd";
        case TokenType::Char: return os << L"Char";
        case TokenType::CharClass: return os << L"CharClass";
        case TokenType::Asterisk: return os << L"Asterisk";
        case TokenType::Plus: return os << L"Plus";
        case TokenType::Question: return os << L"Question";
        case TokenType::Pipe: return os << L"Pipe";
        case TokenType::Error: return os << L"Error";
        case TokenType::EOD: return os << L"EOD";
        case TokenType::Documentation: return os << L"Documentation";
        case TokenType::Production: return os << L"Production";
        case TokenType::Type: return os << L"Type";
        case TokenType::Abstract: return os << L"Abstract";
        case TokenType::Sealed: return os << L"Sealed";
        case TokenType::Alias: return os << L"Alias";
        case TokenType::Colon: return os << L"Colon";
        case TokenType::Word: return os << L"Word";
        case TokenType::DWord: return os << L"DWord";
        case TokenType::Int8: return os << L"Int8";
        case TokenType::Int16: return os << L"Int16";
        case TokenType::Int32: return os << L"Int32";
        case TokenType::Int64: return os << L"Int64";
        case TokenType::StringKeyword: return os << L"StringKeyword";
        case TokenType::WString: return os << L"WString";
        case TokenType::FloatKeyword: return os << L"FloatKeyword";
        case TokenType::DFloat: return os << L"DFloat";
        default: return os << L"(Program Error)";
        }
    }
}
namespace dc2 {
    // Represents a position within a source file/text.
    class position {
    private:
        unsigned long _line;
        unsigned long _column;
    public:
        position() { }
        position(const position &c)
        : _line(c._line), _column(c._column)
        {}
        position(position &&c)
        : _line(std::move(c._line)), _column(std::move(c._column))
        {}
        template<typename _Tline,typename _Tcolumn> position(_Tline&& line,_Tcolumn&& column)
        : _line(std::forward<_Tline>(line)), _column(std::forward<_Tcolumn>(column))
        {}
        
        inline auto line() const -> const unsigned long& { return _line; }
        template<typename _Value> inline auto set_line(_Value&& value) -> void { _line = std::forward<_Value>(value); }
        inline auto column() const -> const unsigned long& { return _column; }
        template<typename _Value> inline auto set_column(_Value&& value) -> void { _column = std::forward<_Value>(value); }
    };
    // Represents a span of text with a source file/text.
    class span {
    private:
        dc2::position _begin;
        dc2::position _end;
    public:
        span() { }
        span(const span &c)
        : _begin(c._begin), _end(c._end)
        {}
        span(span &&c)
        : _begin(std::move(c._begin)), _end(std::move(c._end))
        {}
        template<typename _Tbegin,typename _Tend> span(_Tbegin&& begin,_Tend&& end)
        : _begin(std::forward<_Tbegin>(begin)), _end(std::forward<_Tend>(end))
        {}
        
        inline auto begin() const -> const dc2::position& { return _begin; }
        template<typename _Value> inline auto set_begin(_Value&& value) -> void { _begin = std::forward<_Value>(value); }
        inline auto end() const -> const dc2::position& { return _end; }
        template<typename _Value> inline auto set_end(_Value&& value) -> void { _end = std::forward<_Value>(value); }
    };
    // A value in a source file
    template<typename T>
    class spanvalue {
    private:
        dc2::span _spn;
        T _value;
    public:
        spanvalue() { }
        spanvalue(const spanvalue &c)
        : _spn(c._spn), _value(c._value)
        {}
        spanvalue(spanvalue &&c)
        : _spn(std::move(c._spn)), _value(std::move(c._value))
        {}
        template<typename _Tspn,typename _Tvalue> spanvalue(_Tspn&& spn,_Tvalue&& value)
        : _spn(std::forward<_Tspn>(spn)), _value(std::forward<_Tvalue>(value))
        {}
        
        inline auto spn() const -> const dc2::span& { return _spn; }
        template<typename _Value> inline auto set_spn(_Value&& value) -> void { _spn = std::forward<_Value>(value); }
        inline auto value() const -> const T& { return _value; }
        template<typename _Value> inline auto set_value(_Value&& value) -> void { _value = std::forward<_Value>(value); }
    };
    
}