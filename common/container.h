#pragma once

#include <string>

namespace davecommon
{
    class container abstract {
    public:
        // The name of this token source (i.e.: property name)
        virtual auto name() const->std::wstring = 0;
    };
}