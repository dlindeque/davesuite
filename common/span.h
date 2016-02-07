#pragma once

namespace davecommon
{
    struct position {
        position()
        : line(0), column(0)
        { }
        position(long _line, long _column)
        : line(_line), column(_column)
        {}
        position(const position &c)
        : line(c.line), column(c.column)
        {}
        
        inline auto operator =(const position &c) -> position& {
            line = c.line;
            column = c.column;
            return *this;
        }
        
        long line;
        long column;

        friend inline auto operator == (const position &v1, const position &v2) -> bool {
            return v1.line == v2.line && v1.column == v2.column;
        }
    };

    struct span {
        span() { }
        span(const position &_begin, const position &_end)
        : begin(_begin), end(_end)
        { }
        span(const span &c)
        : begin(c.begin), end(c.end)
        { }
        
        position begin;
        position end;

        friend inline auto operator == (const span &v1, const span &v2) -> bool {
            return v1.begin == v2.begin && v1.end == v2.end;
        }
    };
}