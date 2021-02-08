#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

bool increment(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string instructionName;
    word addr;

    reset_and_prepare_memory(mem);
    cpu.reset(mem);
    cpu.ZeroFlag = 1;       // To check if it is set
    cpu.NegativeFlag = 1;   // To check if it is set
    mem.write(0x200, instruction);

    switch(instruction){
        case CPU::INS_INC_ZP:
            instructionName = "INS_INC_ZP";
            mem.write(0x201, 0x56);
            mem.write(0x56, 0x03);
            addr = 0x56;
            break;

        case CPU::INS_INC_ZPX:
            instructionName = "INS_INC_ZPX";
            mem.write(0x201, 0x56);
            cpu.registerX = 0x04;
            mem.write(0x5A, 0x03);
            addr = 0x5A;
            break;

        case CPU::INS_INC_ABS:
            instructionName = "INS_INC_ABS";
            mem.write(0x201, 0x56);
            mem.write(0x202, 0x34);
            mem.write(0x3456, 0x03);
            addr = 0x3456;
            break;

        case CPU::INS_INC_ABSX:
            instructionName = "INS_INC_ABSX";
            mem.write(0x201, 0x56);
            mem.write(0x202, 0x34);
            cpu.registerX = 0x04;
            mem.write(0x345A, 0x03);
            addr = 0x345A;
            break;

        default:
            cout << "Decrement doesn't handle : " << hex << (int)instruction << endl;
            return false; 
    }
 
    CPU cpuCopy = cpu;
    cpu.step_run(mem);

    if(!expected_eq(mem.read(addr), 0x04, instructionName, "Result")) valid = false;

    if(!expected_eq(cpu.CarryFlag, cpuCopy.CarryFlag, instructionName, "CarryFlag")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 0, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, instructionName, "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, instructionName, "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, instructionName, "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, instructionName, "OverflowFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 0, instructionName, "NegativeFlag")) valid = false;

    return valid;
}

int * run_increment(CPU& cpu, Memory& mem){
    static int result[2];

    result[0]++; if(increment(cpu, mem, CPU::INS_INC_ZP)) result[1]++;
    result[0]++; if(increment(cpu, mem, CPU::INS_INC_ZPX)) result[1]++;
    result[0]++; if(increment(cpu, mem, CPU::INS_INC_ABS)) result[1]++;
    result[0]++; if(increment(cpu, mem, CPU::INS_INC_ABSX)) result[1]++;

    return result;
}