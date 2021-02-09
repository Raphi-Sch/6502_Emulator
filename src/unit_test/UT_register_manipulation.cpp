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

    // Reseting cpu
    reset_and_prepare_memory(mem);
    cpu.reset(mem);

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


    CPU CpuCopy = cpu;
    mem.write(0x0200, instruction);
    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0x11, instructionName, registerName)) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 0, instructionName, registerName)) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 0, instructionName, registerName)) valid = false;
    if(!only_C_and_Z_flags_affected(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

bool decrement_register(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    // Reseting cpu
    cpu.reset(mem);
    reset_and_prepare_memory(mem);

    switch(instruction){
        case CPU::INS_DEX:
            registerName = "registerX";
            instructionName = "INS_DEX";
            cpu.registerX = 0x10;
            cpuRegister = &cpu.registerX;
            break;

        case CPU::INS_DEY:
            registerName = "registerY";
            instructionName = "INS_DEY";
            cpu.registerY = 0x10;
            cpuRegister = &cpu.registerY;
            break;

        default:
            cout << "decrement_register doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }


    CPU CpuCopy = cpu;
    mem.write(0x0200, instruction);
    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0x09, instructionName, registerName)) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 0, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 0, instructionName, "NegativeFlag")) valid = false;

    if(!only_C_and_Z_flags_affected(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

bool transfer_accumulator(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    // Reseting cpu
    cpu.reset(mem);
    reset_and_prepare_memory(mem);

    switch(instruction){
        case CPU::INS_TAX:
            registerName = "registerX";
            instructionName = "INS_TAX";
            cpu.Accumulator = 0xAA;
            cpuRegister = &cpu.registerX;
            break;

        case CPU::INS_TAY:
            registerName = "registerY";
            instructionName = "INS_TAY";
            cpu.Accumulator = 0xAA;
            cpuRegister = &cpu.registerY;
            break;

        default:
            cout << "transfer_accumulator doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }

    CPU CpuCopy = cpu;
    mem.write(0x0200, instruction);
    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0xAA, instructionName, registerName)) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 0, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 1, instructionName, "NegativeFlag")) valid = false;
    if(!only_C_and_Z_flags_affected(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

bool transfer_registerX(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    // Reseting cpu
    cpu.reset(mem);
    reset_and_prepare_memory(mem);

    switch(instruction){
        case CPU::INS_TXA:
            registerName = "Accumulator";
            instructionName = "INS_TXA";
            cpu.registerX = 0x5B;
            cpuRegister = &cpu.Accumulator;
            break;

        case CPU::INS_TXS:
            registerName = "StackPointer";
            instructionName = "INS_TXS";
            cpu.registerX = 0x5B;
            cpu.ZeroFlag = 0;
            cpuRegister = &cpu.StackPointer;
            break;

        default:
            cout << "transfer_registerX doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }

    CPU CpuCopy = cpu;
    mem.write(0x0200, instruction);
    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0x5B, instructionName, registerName)) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 0, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 0, instructionName, "NegativeFlag")) valid = false;
    if(!only_C_and_Z_flags_affected(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

bool TSX(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    reset_and_prepare_memory(mem);
    cpu.reset(mem);
    cpu.StackPointer = 0x9D;

    CPU CpuCopy = cpu;
    mem.write(0x0200, CPU::INS_TSX);
    cpu.step_run(mem);

    if(!expected_eq(cpu.registerX, 0x9D, "INS_TSX", "RegisterX")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 0, "INS_TSX", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 1, "INS_TSX", "NegativeFlag")) valid = false;
    if(!only_C_and_Z_flags_affected(cpu, CpuCopy, "INS_TSX")) valid = false;

    return valid;
}

bool TYA(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    reset_and_prepare_memory(mem);
    cpu.reset(mem);
    cpu.registerY = 0x4D;

    CPU CpuCopy = cpu;
    mem.write(0x0200, CPU::INS_TYA);
    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, 0x4D, "INS_TYA", "Accumulator")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 0, "INS_TYA", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 0, "INS_TYA", "NegativeFlag")) valid = false;
    if(!only_C_and_Z_flags_affected(cpu, CpuCopy, "INS_TYA")) valid = false;

    return valid;
}

int * run_register_manipulation(CPU& cpu, Memory& mem){
    static int result[2];

    result[0]++; if(increment_register(cpu, mem, CPU::INS_INX)) result[1]++;
    result[0]++; if(increment_register(cpu, mem, CPU::INS_INY)) result[1]++;

    result[0]++; if(decrement_register(cpu, mem, CPU::INS_DEX)) result[1]++;
    result[0]++; if(decrement_register(cpu, mem, CPU::INS_DEY)) result[1]++;

    result[0]++; if(transfer_accumulator(cpu, mem, CPU::INS_TAX)) result[1]++;
    result[0]++; if(transfer_accumulator(cpu, mem, CPU::INS_TAY)) result[1]++;

    result[0]++; if(transfer_registerX(cpu, mem, CPU::INS_TXA)) result[1]++;
    result[0]++; if(transfer_registerX(cpu, mem, CPU::INS_TXS)) result[1]++;

    result[0]++; if(TSX(cpu, mem)) result[1]++;
    result[0]++; if(TYA(cpu, mem)) result[1]++;

    return result;
}