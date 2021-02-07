#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

// Stack Instruction
bool PHA(CPU& cpu, Memory& mem){
    bool valid = true;

    cpu.reset(mem);
    cpu.Accumulator = 0xDB;
    cpu.StackPointer = 0xFA;

    CPU cpuCopy = cpu;

    mem.write(0x0200, CPU::INS_PHA);
    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, mem.read(0x01FA), "INS_PHA", "Data store in mem[StackPointer] and Accumulator")) valid = false;

    if(!expected_eq(cpu.Accumulator, cpuCopy.Accumulator, "INS_PHA", "Accumulator")) valid = false;
    if(!expected_eq(cpu.registerX, cpuCopy.registerX, "INS_PHA", "registerX")) valid = false;
    if(!expected_eq(cpu.registerY, cpuCopy.registerY, "INS_PHA", "registerY")) valid = false;
    if(!expected_eq(cpu.ProgramCounter, cpuCopy.ProgramCounter + 0x01, "INS_PHA", "ProgramCounter")) valid = false;
    if(!expected_eq(cpu.StackPointer, cpuCopy.StackPointer - 0x01, "INS_PHA", "StackPointer")) valid = false;
    if(!no_flags_affected(cpu, cpuCopy, "INS_PHA")) valid = false;

    return valid;
}

bool PLA(CPU& cpu, Memory& mem){
    bool valid = true;

    cpu.reset(mem);
    cpu.StackPointer = 0xFB;
    mem.write(0x01FC, 0xFD);

    CPU cpuCopy = cpu;

    mem.write(0x0200, CPU::INS_PLA);
    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, mem.read(0x01FC), "INS_PLA", "Data store in mem[StackPointer] and Accumulator")) valid = false;
    if(!expected_eq(cpu.registerX, cpuCopy.registerX, "INS_PLA", "registerX")) valid = false;
    if(!expected_eq(cpu.registerY, cpuCopy.registerY, "INS_PLA", "registerY")) valid = false;
    if(!expected_eq(cpu.ProgramCounter, cpuCopy.ProgramCounter + 0x01, "INS_PLA", "ProgramCounter")) valid = false;
    if(!expected_eq(cpu.StackPointer, cpuCopy.StackPointer + 0x01, "INS_PLA", "StackPointer")) valid = false;
    if(!only_C_and_Z_flags_affected(cpu, cpuCopy, "INS_PLA")) valid = false;

    return valid;
}

bool PHP(CPU& cpu, Memory& mem){
    bool valid = true;

    cpu.reset(mem);
    cpu.StackPointer = 0xFC;
    cpu.CarryFlag = 1;
    cpu.ZeroFlag = 1;
    cpu.InterruptDisable = 1;
    cpu.DecimalMode = 1;
    cpu.BreakCommand = 1;
    cpu.OverflowFlag = 1;
    cpu.NegativeFlag = 1;

    CPU cpuCopy = cpu;

    mem.write(0x0200, CPU::INS_PHP);
    cpu.step_run(mem);

    if(!expected_eq(mem.read(0x01FC), 0xDF,  "INS_PHP", "Data store in mem[StackPointer] and flags")) valid = false;
    if(!expected_eq(cpu.registerX, cpuCopy.registerX, "INS_PHP", "registerX")) valid = false;
    if(!expected_eq(cpu.registerY, cpuCopy.registerY, "INS_PHP", "registerY")) valid = false;
    if(!expected_eq(cpu.ProgramCounter, cpuCopy.ProgramCounter + 0x01, "INS_PHP", "ProgramCounter")) valid = false;
    if(!expected_eq(cpu.StackPointer, cpuCopy.StackPointer - 0x01, "INS_PHP", "StackPointer")) valid = false;
    if(!no_flags_affected(cpu, cpuCopy, "INS_PHP")) valid = false;

    return valid;
}

bool PLP(CPU& cpu, Memory& mem){
    bool valid = true;

    cpu.reset(mem);
    cpu.StackPointer = 0xFD;
    mem.write(0x01FE, 0xDF);

    CPU cpuCopy = cpu;

    mem.write(0x0200, CPU::INS_PLP);
    cpu.step_run(mem);

    byte flags = cpu.CarryFlag | (cpu.ZeroFlag << 1) | (cpu.InterruptDisable << 2) | (cpu.DecimalMode << 3) | (cpu.BreakCommand << 4) | (cpu.OverflowFlag << 6) | (cpu.NegativeFlag << 7);

    if(!expected_eq(flags, 0xDF,  "INS_PLP", "Data store in mem[StackPointer] and flags")) valid = false;
    if(!expected_eq(cpu.registerX, cpuCopy.registerX, "INS_PLP", "registerX")) valid = false;
    if(!expected_eq(cpu.registerY, cpuCopy.registerY, "INS_PLP", "registerY")) valid = false;
    if(!expected_eq(cpu.ProgramCounter, cpuCopy.ProgramCounter + 0x01, "INS_PLP", "ProgramCounter")) valid = false;
    if(!expected_eq(cpu.StackPointer, cpuCopy.StackPointer + 0x01, "INS_PLP", "StackPointer")) valid = false;

    return valid;
}
