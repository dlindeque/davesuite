#pragma once

namespace davecommon
{
    struct position {
        long line;
        long column;
    };

    struct span {
        position begin;
        position end;
    };
}