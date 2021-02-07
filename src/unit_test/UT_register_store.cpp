#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

// Store register test
bool store_register_zero_page(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    // Reseting cpu
    cpu.reset(mem);
    reset_and_prepare_memory(mem);

    switch(instruction){
        case CPU::INS_STA_ZP:
            registerName = "Data store in mem and Accumulator";
            instructionName = "INS_STA_ZP";
            cpuRegister = &cpu.Accumulator;
            cpu.Accumulator = 0xAA;
            break;

        case CPU::INS_STX_ZP:
            registerName = "Data store in mem and registerX";
            instructionName = "INS_STX_ZP";
            cpuRegister = &cpu.registerX;
            cpu.registerX = 0xAA;
            break;

        case CPU::INS_STY_ZP:
            registerName = "Data store in mem and registerY";
            instructionName = "INS_STY_ZP";
            cpuRegister = &cpu.registerY;
            cpu.registerY = 0xAA;
            break;

        default:
            cout << "store_register_zero_page doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }

    CPU CpuCopy = cpu;

    mem.write(0x0200, instruction);
    mem.write(0x0201, 0x01);

    cpu.step_run(mem);

    if(!expected_eq(mem.read(0x0001), 0xAA, instructionName, registerName)) valid = false;
    if(!no_flags_affected(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

bool store_register_zero_page_X(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    // Reseting cpu
    cpu.reset(mem);
    reset_and_prepare_memory(mem);

    switch(instruction){
        case CPU::INS_STA_ZPX:
            registerName = "Data store in mem and Accumulator";
            instructionName = "INS_STA_ZPX";
            cpuRegister = &cpu.Accumulator;
            cpu.Accumulator = 0xAB;
            break;

        case CPU::INS_STY_ZPX:
            registerName = "Data store in mem and registerY";
            instructionName = "INS_STY_ZPX";
            cpuRegister = &cpu.registerY;
            cpu.registerY = 0xAB;
            break;

        default:
            cout << "store_register_zero_page_X doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }

    CPU CpuCopy = cpu;

    mem.write(0x0200, instruction);
    mem.write(0x0201, 0x02);

    cpu.step_run(mem);

    if(!expected_eq(mem.read(0x0002), 0xAB, instructionName, registerName)) valid = false;
    if(!no_flags_affected(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

bool store_register_zero_page_Y(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    // Reseting cpu
    cpu.reset(mem);
    reset_and_prepare_memory(mem);

    switch(instruction){
        case CPU::INS_STX_ZPY:
            registerName = "Data store in mem and registerX";
            instructionName = "INS_STX_ZPY";
            cpuRegister = &cpu.registerX;
            cpu.registerX = 0xAC;
            break;

        default:
            cout << "store_register_zero_page_X doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }

    CPU CpuCopy = cpu;

    mem.write(0x0200, instruction);
    mem.write(0x0201, 0x03);

    cpu.step_run(mem);

    if(!expected_eq(mem.read(0x0003), 0xAC, instructionName, registerName)) valid = false;
    if(!no_flags_affected(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

bool store_register_absolute(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    // Reseting cpu
    cpu.reset(mem);
    reset_and_prepare_memory(mem);

    switch(instruction){
        case CPU::INS_STA_ABS:
            registerName = "Data store in mem and Accumulator";
            instructionName = "INS_STA_ABS";
            cpuRegister = &cpu.Accumulator;
            cpu.Accumulator = 0xAD;
            break;

        case CPU::INS_STX_ABS:
            registerName = "Data store in mem and registerX";
            instructionName = "INS_STX_ABS";
            cpuRegister = &cpu.registerX;
            cpu.registerX = 0xAD;
            break;

        case CPU::INS_STY_ABS:
            registerName = "Data store in mem and registerY";
            instructionName = "INS_STY_ABS";
            cpuRegister = &cpu.registerY;
            cpu.registerY = 0xAD;
            break;

        default:
            cout << "store_register_absolute doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }

    CPU CpuCopy = cpu;

    mem.write(0x0200, instruction);
    mem.write(0x0201, 0x10);
    mem.write(0x0202, 0x01);

    cpu.step_run(mem);

    if(!expected_eq(mem.read(0x0110), 0xAD, instructionName, registerName)) valid = false;
    if(!no_flags_affected(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

// STA specific test
bool STA_ABSX(CPU& cpu, Memory& mem){
    bool valid = true;
 
    // Reseting cpu
    cpu.reset(mem);
    reset_and_prepare_memory(mem);

    cpu.Accumulator = 0x1A;
    cpu.registerX = 0x01;
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, CPU::INS_STA_ABSX);
    mem.write(0x0201, 0x0F);
    mem.write(0x0202, 0x0A);

    cpu.step_run(mem);

    if(!expected_eq(mem.read(0x0A10), 0x1A, "INS_STA_ABSX", "Data store in mem and Accumulator")) valid = false;
    if(!no_flags_affected(cpu, CpuCopy, "INS_STA_ABSX")) valid = false;

    return valid;
}

bool STA_ABSY(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    reset_and_prepare_memory(mem);

    cpu.Accumulator = 0x1B;
    cpu.registerY = 0x01;
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, CPU::INS_STA_ABSY);
    mem.write(0x0201, 0x0F);
    mem.write(0x0202, 0x0B);
    
    cpu.step_run(mem);


    if(!expected_eq(mem.read(0x0B10), 0x1B, "INS_STA_ABSY", "Data store in mem and Accumulator")) valid = false;
    if(!no_flags_affected(cpu, CpuCopy, "INS_STA_ABSY")) valid = false;

    return valid;
}

bool STA_INDX(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    reset_and_prepare_memory(mem);

    cpu.Accumulator = 0x2A;
    cpu.registerX = 0x04;

    CPU CpuCopy = cpu;

    mem.write(0x0200, CPU::INS_STA_INDX);
    mem.write(0x0201, 0x20);
    mem.write(0x0024, 0x74);
    mem.write(0x0025, 0x20);

    cpu.step_run(mem);

    if(!expected_eq(mem.read(0x2074), 0x2A, "INS_STA_INDX", "Data store in mem and Accumulator")) valid = false;
    if(!no_flags_affected(cpu, CpuCopy, "INS_STA_INDX")) valid = false;

    return valid;
}

bool STA_INDY(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    reset_and_prepare_memory(mem);
    
    cpu.registerY = 0x10;
    cpu.Accumulator = 0x2B;
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, CPU::INS_STA_INDY);
    mem.write(0x0201, 0x86);
    
    mem.write(0x0086, 0x28);
    mem.write(0x0087, 0x40);
    mem.write(0x4038, 0xF8);

    cpu.step_run(mem);

    if(!expected_eq(mem.read(0x4038), 0x2B, "INS_STA_INDY", "Data store in mem and Accumulator")) valid = false;
    if(!no_flags_affected(cpu, CpuCopy, "INS_STA_INDY")) valid = false;

    return valid;
}

int * run_register_store(CPU& cpu, Memory& mem){
    static int result[2];

    // STA
    result[0]++; if(store_register_zero_page(cpu, mem, CPU::INS_STA_ZP)) result[1]++;
    result[0]++; if(store_register_zero_page_X(cpu, mem, CPU::INS_STA_ZPX)) result[1]++;
    result[0]++; if(store_register_absolute(cpu, mem, CPU::INS_STA_ABS)) result[1]++;
    result[0]++; if(STA_ABSX(cpu, mem)) result[1]++;
    result[0]++; if(STA_ABSY(cpu, mem)) result[1]++;
    result[0]++; if(STA_INDX(cpu, mem)) result[1]++;
    result[0]++; if(STA_INDY(cpu, mem)) result[1]++;

    // STX
    result[0]++; if(store_register_zero_page(cpu, mem, CPU::INS_STX_ZP)) result[1]++;
    result[0]++; if(store_register_zero_page_Y(cpu, mem, CPU::INS_STX_ZPY)) result[1]++;
    result[0]++; if(store_register_absolute(cpu, mem, CPU::INS_STX_ABS)) result[1]++;
  
    // STY
    result[0]++; if(store_register_zero_page(cpu, mem, CPU::INS_STY_ZP)) result[1]++;
    result[0]++; if(store_register_zero_page_X(cpu, mem, CPU::INS_STY_ZPX)) result[1]++;
    result[0]++; if(store_register_absolute(cpu, mem, CPU::INS_STY_ABS)) result[1]++;

    return result;
}