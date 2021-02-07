#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

bool load_register_immediate(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    switch(instruction){
        case CPU::INS_LDA_IM:
            registerName = "Accumulator";
            instructionName = "INS_LDA_IM";
            cpuRegister = &cpu.Accumulator;
            break;

        case CPU::INS_LDX_IM:
            registerName = "registerX";
            instructionName = "INS_LDX_IM";
            cpuRegister = &cpu.registerX;
            break;

        case CPU::INS_LDY_IM:
            registerName = "registerY";
            instructionName = "INS_LDY_IM";
            cpuRegister = &cpu.registerY;
            break;

        default:
            cout << "load_register_immediate doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }

    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    // ZeroFlag shoud be false, NegativeFlag shoud be true
    mem.write(0x0200, instruction);
    mem.write(0x0201, 0xF1);

    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0xF1, instructionName, registerName)) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, instructionName, "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, instructionName)) valid = false;

    // Reseting cpu
    cpu.reset(mem);
    CpuCopy = cpu;

    // ZeroFlag shoud be true, NegativeFlag shoud be false
    mem.write(0x0200, instruction);
    mem.write(0x0201, 0x00);

    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0xF1, instructionName, registerName)) valid = false;
    if(!expected_eq(cpu.ZeroFlag, true, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, false, instructionName, "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

bool load_register_zero_page(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    switch(instruction){
        case CPU::INS_LDA_ZP:
            registerName = "Accumulator";
            instructionName = "INS_LDA_ZP";
            cpuRegister = &cpu.Accumulator;
            break;

        case CPU::INS_LDX_ZP:
            registerName = "registerX";
            instructionName = "INS_LDX_ZP";
            cpuRegister = &cpu.registerX;
            break;

        case CPU::INS_LDY_ZP:
            registerName = "registerY";
            instructionName = "INS_LDY_ZP";
            cpuRegister = &cpu.registerY;
            break;

        default:
            cout << "load_register_zero_page doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }

    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, instruction);
    mem.write(0x0201, 0x01);
    mem.write(0x0001, 0xF2);

    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0xF2, instructionName, registerName)) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, instructionName, "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

bool load_register_zero_page_X(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    switch(instruction){
        case CPU::INS_LDA_ZPX:
            registerName = "Accumulator";
            instructionName = "INS_LDA_ZPX";
            cpuRegister = &cpu.Accumulator;
            break;

        case CPU::INS_LDY_ZPX:
            registerName = "registerY";
            instructionName = "INS_LDY_ZPX";
            cpuRegister = &cpu.registerY;
            break;

        default:
            cout << "load_register_zero_page_X doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }

    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, instruction);
    mem.write(0x0201, 0x01);
    mem.write(0x000A, 0xF3);
    cpu.registerX = 0x09;

    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0xF3, instructionName, registerName)) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, instructionName, "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

bool load_register_zero_page_Y(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    switch(instruction){
        case CPU::INS_LDX_ZPY:
            registerName = "registerX";
            instructionName = "INS_LDX_ZPY";
            cpuRegister = &cpu.registerY;
            break;

        default:
            cout << "load_register_zero_page_Y doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }

    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, instruction);
    mem.write(0x0201, 0x01);
    mem.write(0x000A, 0xF3);
    cpu.registerX = 0x09;

    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0xF3, instructionName, registerName)) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, instructionName, "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

bool load_register_absolute(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    switch(instruction){
        case CPU::INS_LDA_ABS:
            registerName = "Accumulator";
            instructionName = "INS_LDA_ABS";
            cpuRegister = &cpu.Accumulator;
            break;

        case CPU::INS_LDX_ABS:
            registerName = "registerX";
            instructionName = "INS_LDX_ABS";
            cpuRegister = &cpu.registerX;
            break;

        case CPU::INS_LDY_ABS:
            registerName = "registerY";
            instructionName = "INS_LDY_ABS";
            cpuRegister = &cpu.registerY;
            break;

        default:
            cout << "load_register_absolute doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }

    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, instruction);
    mem.write(0x0201, 0x01);
    mem.write(0x0202, 0x10);
    mem.write(0x1001, 0xF4);

    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0xF4, instructionName, registerName)) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, instructionName, "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

bool load_register_absolute_X(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    switch(instruction){
        case CPU::INS_LDA_ABSX:
            registerName = "Accumulator";
            instructionName = "INS_LDA_ABSX";
            cpuRegister = &cpu.Accumulator;
            break;

        case CPU::INS_LDY_ABSX:
            registerName = "registerY";
            instructionName = "INS_LDY_ABSX";
            cpuRegister = &cpu.registerY;
            break;

        default:
            cout << "load_register_absolute_X doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }
    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, instruction);
    mem.write(0x0201, 0x10);
    mem.write(0x0202, 0x0A);
    mem.write(0x0A1A, 0xF5);
    cpu.registerX = 0x0A;

    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0xF5, instructionName, registerName)) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, instructionName, "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

bool load_register_absolute_Y(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    switch(instruction){
        case CPU::INS_LDA_ABSY:
            registerName = "Accumulator";
            instructionName = "INS_LDA_ABSY";
            cpuRegister = &cpu.Accumulator;
            break;

        case CPU::INS_LDX_ABSY:
            registerName = "registerX";
            instructionName = "INS_LDX_ABSY";
            cpuRegister = &cpu.registerX;
            break;

        default:
            cout << "load_register_absolute_Y doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }
    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, instruction);
    mem.write(0x0201, 0x10);
    mem.write(0x0202, 0x0B);
    mem.write(0x0B1A, 0xF6);
    cpu.registerY = 0x0A;

    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0xF6, instructionName, registerName)) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, instructionName, "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, instructionName)) valid = false;
    

    return valid;
}

// LDA specific test
bool LDA_INDX(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, CPU::INS_LDA_INDX);
    mem.write(0x0201, 0x20);
    cpu.registerX = 0x04;
    mem.write(0x0024, 0x74);
    mem.write(0x0025, 0x20);
    mem.write(0x2074, 0xF7);

    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, 0xF7, "INS_LDA_INDX", "Accumulator")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, "INS_LDA_INDX", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, "INS_LDA_INDX", "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, "INS_LDA_INDX")) valid = false;

    return valid;
}

bool LDA_INDY(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, CPU::INS_LDA_INDY);
    mem.write(0x0201, 0x86);
    cpu.registerY = 0x10;
    mem.write(0x0086, 0x28);
    mem.write(0x0087, 0x40);
    mem.write(0x4038, 0xF8);

    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, 0xF8, "INS_LDA_INDY", "Accumulator")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, "INS_LDA_INDY", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, "INS_LDA_INDY", "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, "INS_LDA_INDY")) valid = false;

    return valid;
}