#pragma once

#include "common.h"
#include "device.h"
#include "system_bus.h"

namespace dave
{
    class rom : public device {
    public:
        const static REG16 addr_lower = 0x0E00;
        const static REG16 addr_upper = 0xFFFF;
    private:
        REG8 _data[addr_upper - addr_lower + 1] = {};
    public:
        rom(system_bus *bus)
            : device(bus)
        {}
        rom() = delete;
        rom(const rom&) = delete;
        rom(rom &&) = delete;
        auto operator =(const rom&)->rom& = delete;
        auto operator =(rom &&)->rom& = delete;

        virtual void nop() override { }
        virtual void write(const REG16 &address, const REG8 *data) override {
            // Set access violation
            _bus->irq = true; // This needs work
        }
        virtual void read(const REG16 &address, REG8 *dest) override {
            if (address >= addr_lower && address <= addr_upper) {
                *dest = _data[address];
            }
        }
    };
}