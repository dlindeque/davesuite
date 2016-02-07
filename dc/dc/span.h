#pragma once

namespace dc
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
        friend inline auto operator != (const position &v1, const position &v2) -> bool {
            return !(v1 == v2);
        }
        friend inline auto operator <(const position &v1, const position &v2) -> bool {
            if (v1.line == v2.line) {
                return v1.column < v2.column;
            } 
            else {
                return v1.line < v2.line;
            }
        }
        friend inline auto operator >(const position &v1, const position &v2) -> bool {
            if (v1.line == v2.line) {
                return v1.column > v2.column;
            } 
            else {
                return v1.line > v2.line;
            }
        }
        friend inline auto operator <=(const position &v1, const position &v2) -> bool {
            return !(v1 > v2);
        }
        friend inline auto operator >=(const position &v1, const position &v2) -> bool {
            return !(v1 < v2);
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
        friend inline auto operator != (const span &v1, const span &v2) -> bool {
            return !(v1 == v2);
        }
        friend inline auto operator <(const span &v1, const span &v2) -> bool {
            if (v1.begin == v2.begin) {
                return v1.end < v2.end;
            } 
            else {
                return v1.begin < v2.begin;
            }
        }
        friend inline auto operator >(const span &v1, const span &v2) -> bool {
            if (v1.begin == v2.begin) {
                return v1.end > v2.end;
            } 
            else {
                return v1.begin > v2.begin;
            }
        }
        friend inline auto operator <=(const span &v1, const span &v2) -> bool {
            return !(v1 > v2);
        }
        friend inline auto operator >=(const span &v1, const span &v2) -> bool {
            return !(v1 < v2);
        }
    };
}

namespace std
{
    template<> struct hash<dc::position> {
        inline auto operator()(const dc::position &v) const -> size_t {
            return hash<long>()(v.column) + hash<long>()(v.line);
        }
    };
    
    template<> struct hash<dc::span> {
        inline auto operator()(const dc::span &v) const -> size_t {
            return hash<dc::position>()(v.begin) + hash<dc::position>()(v.end);
        }
    };
}