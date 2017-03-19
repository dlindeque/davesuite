// vm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "..\vm_lib\machine.h"
#include "..\vm_lib\cpu6502.h"
#include "..\vm_lib\rom.h"

int main()
{
    dave::machine machine;

    machine.add_cpu<dave::cpu6502>();
    machine.add_device<dave::rom>();

    return 0;
}

