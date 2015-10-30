#pragma once

#include "container.h"
#include "span.h"

namespace davecommon
{
    enum class severity {
        info = 10,
        warning = 30,
        error = 50
    };

    struct log;

    class logger abstract {
    protected:
        virtual auto write(severity severity, const container* container, const span &span, const std::wstring &msg) -> void = 0;
    public:
        logger() { }
        logger(const logger&) = delete;
        logger(logger &&) = delete;

        virtual ~logger() { }

        friend log;
    };
}