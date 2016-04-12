// Generated by Dave Compiler

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "test.ds.model.h"

namespace davelexer {
    class lexer {
    private:
        // state of the lexer
        long _line;
        long _column;
        std::wistream &_stm;
        wchar_t _ch;
        std::vector<size_t> _states;
    public:
        lexer() = delete;
        lexer(const lexer&) = delete;
        lexer(lexer&&) = delete;
        lexer(std::wistream &stm)
        : _stm(stm), _line(1), _column(1)
        {
            // Read the first char
            _ch = _stm.get();
            // Initialize the states
            _states.push_back(0);
        }

        inline auto operator=(const lexer &) -> lexer& = delete;
        inline auto operator=(lexer &&c) -> lexer& = delete;

        // state of the lexer
        inline auto line() const -> const long& { return _line; }
        inline auto line() -> long& { return _line; }
        inline auto column() const -> const long& { return _column; }
        inline auto column() -> long& { return _column; }
        inline auto stm() const -> const std::wistream& { return _stm; }
        inline auto stm() -> std::wistream& { return _stm; }
        inline auto states() const -> const std::vector<size_t>& { return _states; }
        inline auto states() -> std::vector<size_t>& { return _states; }

        auto try_read_next_token(long &start_line, long &start_column, long &end_line, long &end_column, std::wstring &value, davelexer::TokenType &token) -> bool;
    };
}
