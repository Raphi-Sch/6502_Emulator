#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

// Increment
bool increment_register(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    switch(instruction){
        case CPU::INS_INX:
            registerName = "registerX";
            instructionName = "INS_INX";
            cpu.registerX = 0x10;
            cpuRegister = &cpu.registerX;
            break;

        case CPU::INS_INY:
            registerName = "registerY";
            instructionName = "INS_INY";
            cpu.registerY = 0x10;
            cpuRegister = &cpu.registerY;
            break;

        default:
            cout << "increment_register doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }

    // Reseting cpu
    cpu.reset(mem);
    CPU CpuCopy = cpu;
    mem.write(0x0200, instruction);
    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0x11, instructionName, registerName)) valid = false;
    if(!no_flags_affected(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

bool decrement_register(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    switch(instruction){
        case CPU::INS_INX:
            registerName = "registerX";
            instructionName = "INS_DEX";
            cpu.registerX = 0x10;
            cpuRegister = &cpu.registerX;
            break;

        case CPU::INS_INY:
            registerName = "registerY";
            instructionName = "INS_DEY";
            cpu.registerY = 0x10;
            cpuRegister = &cpu.registerY;
            break;

        default:
            cout << "decrement_register doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }

    // Reseting cpu
    cpu.reset(mem);
    CPU CpuCopy = cpu;
    mem.write(0x0200, instruction);
    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0x09, instructionName, registerName)) valid = false;
    if(!no_flags_affected(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}