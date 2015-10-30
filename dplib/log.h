#pragma once

#include "..\common\logger.h"

namespace davecommon
{
    struct log {
        struct error {
            static inline auto test(logger *logger, container *container, span &spn) -> void {
                logger->write(severity::error, container, spn, L"This is my test");
            }
        };
    };
}