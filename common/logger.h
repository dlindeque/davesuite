#pragma once

#include "container.h"
#include "span.h"

namespace davecommon
{
    struct qname {
        std::vector<std::wstring> parts;
    };

    enum class severity {
        info = 10,
        warning = 30,
        error = 50
    };

    struct log;
    class logger_decorator;

    class logger abstract {
    protected:
        virtual auto write(severity s, const container* cntr, const span &spn, const std::wstring &msg) -> void = 0;
    public:
        logger() {}
        logger(const logger&) = delete;
        logger(logger &&) = delete;

        virtual ~logger() { }

        friend log;
        friend logger_decorator;
    };

    class logger_decorator abstract : public logger {
    private:
        logger *_decorated;
    protected:
        inline auto write_decorated(severity s, const container* cntr, const span &spn, const std::wstring &msg) -> void {
            _decorated->write(s, cntr, spn, msg);
        }
    public:
        logger_decorator() = delete;
        logger_decorator(const logger_decorator&) = delete;
        logger_decorator(logger_decorator&&) = delete;

        logger_decorator(logger *decorated)
            : _decorated(decorated)
        {}

        virtual ~logger_decorator() {}
    };
}