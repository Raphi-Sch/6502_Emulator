#include "unit_test.h"

using namespace std;

void run_all_test(CPU& cpu, Memory& mem){
    int nb_test = 0;
    int test_passed = 0;

    // Setting reset vector
    mem.clear();
    mem.write(0xfffc, 0x00);
    mem.write(0xfffd, 0x02);

    // LDA
    nb_test++; if(load_register_immediate(cpu, mem, CPU::INS_LDA_IM)) test_passed++;
    nb_test++; if(load_register_zero_page(cpu, mem, CPU::INS_LDA_ZP)) test_passed++;
    nb_test++; if(load_register_zero_page_X(cpu, mem, CPU::INS_LDA_ZPX)) test_passed++;
    nb_test++; if(load_register_absolute(cpu, mem, CPU::INS_LDA_ABS)) test_passed++;
    nb_test++; if(load_register_absolute_X(cpu, mem, CPU::INS_LDA_ABSX)) test_passed++;
    nb_test++; if(load_register_absolute_Y(cpu, mem, CPU::INS_LDA_ABSY)) test_passed++;
    nb_test++; if(LDA_INDX(cpu, mem)) test_passed++;
    nb_test++; if(LDA_INDY(cpu, mem)) test_passed++;

    // STA
    nb_test++; if(store_register_zero_page(cpu, mem, CPU::INS_STA_ZP)) test_passed++;
    nb_test++; if(store_register_zero_page_X(cpu, mem, CPU::INS_STA_ZPX)) test_passed++;
    nb_test++; if(store_register_absolute(cpu, mem, CPU::INS_STA_ABS)) test_passed++;
    nb_test++; if(STA_ABSX(cpu, mem)) test_passed++;
    nb_test++; if(STA_ABSY(cpu, mem)) test_passed++;
    nb_test++; if(STA_INDX(cpu, mem)) test_passed++;
    nb_test++; if(STA_INDY(cpu, mem)) test_passed++;

    // LDX
    nb_test++; if(load_register_immediate(cpu, mem, CPU::INS_LDX_IM)) test_passed++;
    nb_test++; if(load_register_zero_page(cpu, mem, CPU::INS_LDX_ZP)) test_passed++;
    nb_test++; if(load_register_zero_page_Y(cpu, mem, CPU::INS_LDX_ZPY)) test_passed++;
    nb_test++; if(load_register_absolute(cpu, mem, CPU::INS_LDX_ABS)) test_passed++;
    nb_test++; if(load_register_absolute_Y(cpu, mem, CPU::INS_LDX_ABSY)) test_passed++;

    // STX
    nb_test++; if(store_register_zero_page(cpu, mem, CPU::INS_STX_ZP)) test_passed++;
    nb_test++; if(store_register_zero_page_Y(cpu, mem, CPU::INS_STX_ZPY)) test_passed++;
    nb_test++; if(store_register_absolute(cpu, mem, CPU::INS_STX_ABS)) test_passed++;
  
    // LDY
    nb_test++; if(load_register_immediate(cpu, mem, CPU::INS_LDY_IM)) test_passed++;
    nb_test++; if(load_register_zero_page(cpu, mem, CPU::INS_LDY_ZP)) test_passed++;
    nb_test++; if(load_register_absolute(cpu, mem, CPU::INS_LDY_ABS)) test_passed++;
    nb_test++; if(load_register_absolute_X(cpu, mem, CPU::INS_LDY_ABSX)) test_passed++;

    // STY
    nb_test++; if(store_register_zero_page(cpu, mem, CPU::INS_STY_ZP)) test_passed++;
    nb_test++; if(store_register_zero_page_X(cpu, mem, CPU::INS_STY_ZPX)) test_passed++;
    nb_test++; if(store_register_absolute(cpu, mem, CPU::INS_STY_ABS)) test_passed++;


    // NOP
    nb_test++; if(nop(cpu, mem)) test_passed++;

    
    cout << dec << test_passed << " of " << nb_test << " test passed successfully" << endl;
}


// Load register test
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

    if(!expected_eq(cpu.Accumulator, 0xF8, "INS_LDA_INDX", "Accumulator")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, "INS_LDA_INDX", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, "INS_LDA_INDX", "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, "INS_LDA_INDX")) valid = false;

    return valid;
}

// Store register test
bool store_register_zero_page(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string registerName;
    string instructionName;
    byte* cpuRegister;

    // Reseting cpu
    cpu.reset(mem);

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


// No Operation
bool nop(CPU& cpu, Memory& mem){
    bool valid = true;

    cpu.reset(mem);
    CPU cpuCopy = cpu;
    mem.write(0x0200, CPU::INS_NOP);
    cpu.step_run(mem);

    if(!expected_eq(cpuCopy.Accumulator, cpu.Accumulator, "INS_NOP", "Accumulator")) valid = false;
    if(!expected_eq(cpuCopy.registerX, cpu.registerX, "INS_NOP", "registerX")) valid = false;
    if(!expected_eq(cpuCopy.registerY, cpu.registerY, "INS_NOP", "registerY")) valid = false;
    if(!expected_eq(cpuCopy.ProgramCounter + 0x01, cpu.ProgramCounter, "INS_NOP", "ProgramCounter")) valid = false;
    if(!expected_eq(cpuCopy.StackPointer, cpu.StackPointer, "INS_NOP", "StackPointer")) valid = false;
    if(!no_flags_affected(cpu, cpuCopy, "INS_NOP")) valid = false;

    return valid;
}


// Expected
bool expected_eq(bool value, bool expected, string instruction, string thing){
    if(value != expected){
        cout << instruction << " : " << thing << " not equal (Expected : '" << hex << (int)expected << "' - Got : '" << hex << (int)value << "')" << endl;
        return false;
    }
    return true;
}

bool expected_eq(byte value, byte expected, string instruction, string thing){
    if(value != expected){
        cout << instruction << " : " << thing << " not equal (Expected : '" << hex << (int)expected << "' - Got : '" << hex << (int)value << "')" << endl;
        return false;
    }

    return true;
}

bool expected_eq(word value, word expected, string instruction, string thing){
    if(value != expected){
        cout << instruction << " : " << thing << " not equal (Expected : '" << hex << (int)expected << "' - Got : '" << hex << (int)value << "')" << endl;
        return false;
    }

    return true;
}

bool load_register_not_changing_unexpected_flags(CPU& cpu, CPU& copy, string instruction){
    bool valid = true;
    
    if(!expected_eq(cpu.CarryFlag, copy.CarryFlag, instruction, "CarryFlag")) valid = false;
    if(!expected_eq(cpu.InterruptDisable, copy.InterruptDisable, instruction, "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, copy.DecimalMode, instruction, "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, copy.BreakCommand, instruction, "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, copy.OverflowFlag, instruction, "OverflowFlag")) valid = false;

    return valid;
}

bool no_flags_affected(CPU& cpu, CPU& copy, string instruction){
    bool valid = true;
        
    if(!expected_eq(copy.CarryFlag, cpu.CarryFlag, instruction, "CarryFlag")) valid = false;
    if(!expected_eq(copy.ZeroFlag, cpu.ZeroFlag, instruction, "ZeroFlag")) valid = false;
    if(!expected_eq(copy.InterruptDisable, cpu.InterruptDisable, instruction, "InterruptDisable")) valid = false;
    if(!expected_eq(copy.DecimalMode, cpu.DecimalMode, instruction, "DecimalMode")) valid = false;
    if(!expected_eq(copy.BreakCommand, cpu.BreakCommand, instruction, "BreakCommand")) valid = false;
    if(!expected_eq(copy.OverflowFlag, cpu.OverflowFlag, instruction, "OverflowFlag")) valid = false;
    if(!expected_eq(copy.NegativeFlag, cpu.NegativeFlag, instruction, "NegativeFlag")) valid = false;

    return valid;
}