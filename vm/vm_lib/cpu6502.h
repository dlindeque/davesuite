#pragma once

#include "system_bus.h"
#include "cpu.h"

namespace dave
{
    class cpu6502 : public cpu {
    public:
        int _cycles_left_for_current_operation = 0;
        bool _prev_nmi = false; // We keep this value to track whether the line went high during the last cycle

        struct registers {
            REG16 PC;
            REG8 Y;
            REG8 X;
            REG8 S;
            REG8 A;
            struct PROCESSOR_STATUS {
                REG8 C : 1, Z : 1, I : 1, D : 1, B : 1, UNUSED : 1, V : 1, N : 1;
            } P;
        };

        registers _registers;
    public:
        cpu6502() = delete;
        cpu6502(const cpu6502&) = delete;
        cpu6502(cpu6502 &&) = delete;
        auto operator =(const cpu6502&)->cpu6502& = delete;
        auto operator =(cpu6502 &&)->cpu6502& = delete;

        cpu6502(system_bus *bus)
            : cpu(bus)
        {
            _registers.PC = 0;
        }

        virtual void clock() override;
    };
}