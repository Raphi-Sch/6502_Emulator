#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

bool BIT(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string instructionName;
    byte* cpuRegister;
    word addr;

    reset_and_prepare_memory(mem);
    cpu.reset(mem);
    cpu.Accumulator = 0x80;
    mem.write(0x200, instruction);

    switch(instruction){
        case CPU::INS_BIT_ZP:
            instructionName = "INS_BIT_ZP";
            mem.write(0x201, 0x23);
            mem.write(0x23, 0xF0);
            break;

        case CPU::INS_BIT_ABS:
            instructionName = "INS_BIT_ABS";
            mem.write(0x201, 0x23);
            mem.write(0x202, 0x01);
            mem.write(0x0123, 0xF0);
            break;

        default:
            cout << "BIT doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }
 
    CPU cpuCopy = cpu;
    cpu.step_run(mem);

    if(!expected_eq(cpu.ZeroFlag, 0, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, 0, instructionName, "OverflowFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 1, instructionName, "NegativeFlag")) valid = false;

    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, instructionName, "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, instructionName, "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, instructionName, "BreakCommand")) valid = false;

    return valid;
}

int * run_BIT(CPU& cpu, Memory& mem){
    static int result[2];

    result[0]++; if(BIT(cpu, mem, CPU::INS_BIT_ZP)) result[1]++;
    result[0]++; if(BIT(cpu, mem, CPU::INS_BIT_ABS)) result[1]++;

    return result;
}