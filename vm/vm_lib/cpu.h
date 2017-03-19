#pragma once

#include "system_bus.h"

namespace dave
{
    class cpu {
    protected:
        system_bus *_bus;
    public:
        cpu() = delete;
        cpu(const cpu&) = delete;
        cpu(cpu &&) = delete;
        auto operator =(const cpu&)->cpu& = delete;
        auto operator =(cpu &&)->cpu& = delete;

        cpu(system_bus *bus)
            : _bus(bus)
        {}

        virtual void clock() = 0;
    };
}