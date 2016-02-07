#pragma once

#include "logger.h"
#include "span.h"

namespace davecommon
{
    class offset_logger sealed : public logger_decorator {
    private:
        span _ofs;
    protected:
        virtual auto write(severity s, const container* cntr, const span &spn, const std::wstring &msg) -> void override {
            write_decorated(
                s, 
                cntr, 
                span{ 
                    position{ spn.begin.line + _ofs.begin.line - 1, spn.begin.column + _ofs.begin.column - 1 },
                    position{ spn.end.line + _ofs.end.line - 1, spn.end.column + _ofs.end.column - 1 }
                }, 
                msg);
        }
    public:
        offset_logger() = delete;
        offset_logger(const offset_logger &) = delete;
        offset_logger(offset_logger &&) = delete;

        offset_logger(logger *decorated, span ofs)
            : logger_decorator(decorated), _ofs(ofs)
        {}

        virtual ~offset_logger() { }
    };
}