#include "unit_test.h"

using namespace std;

void run_all_test(CPU& cpu, Memory& mem){
    int nb_test = 0;
    int test_passed = 0;

    // Setting reset vector
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

    // LDX
    nb_test++; if(load_register_immediate(cpu, mem, CPU::INS_LDX_IM)) test_passed++;
    nb_test++; if(load_register_zero_page(cpu, mem, CPU::INS_LDX_ZP)) test_passed++;
    nb_test++; if(load_register_absolute(cpu, mem, CPU::INS_LDX_ABS)) test_passed++;
    nb_test++; if(load_register_absolute_Y(cpu, mem, CPU::INS_LDX_ABSY)) test_passed++;
    
    // LDY
    nb_test++; if(load_register_immediate(cpu, mem, CPU::INS_LDY_IM)) test_passed++;
    nb_test++; if(load_register_zero_page(cpu, mem, CPU::INS_LDY_ZP)) test_passed++;
    nb_test++; if(load_register_absolute(cpu, mem, CPU::INS_LDY_ABS)) test_passed++;
    nb_test++; if(load_register_absolute_X(cpu, mem, CPU::INS_LDY_ABSX)) test_passed++;
    
    cout << dec << test_passed << " of " << nb_test << " test passed successfully" << endl;
}

// LDA


bool LDA_ABSX(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, CPU::INS_LDA_ABSX);
    mem.write(0x0201, 0x10);
    mem.write(0x0202, 0x10);
    mem.write(0x101A, 0xF5);
    cpu.registerX = 0x0A;

    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, 0xF5, "INS_LDA_ABSX", "Accumulator")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, "INS_LDA_ABSX", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, "INS_LDA_ABSX", "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, "INS_LDA_ABSX")) valid = false;

    return valid;
}

bool LDA_ABSY(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, CPU::INS_LDA_ABSY);
    mem.write(0x0201, 0x10);
    mem.write(0x0202, 0x10);
    mem.write(0x101A, 0xF6);
    cpu.registerY = 0x0A;

    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, 0xF6, "INS_LDA_ABSY", "Accumulator")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, "INS_LDA_ABSY", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, "INS_LDA_ABSY", "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, "INS_LDA_ABSY")) valid = false;

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
    mem.write(0x0201, 0x10);
    mem.write(0x0202, 0x10);
    mem.write(0x1010, 0xF4);

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
    mem.write(0x0202, 0x10);
    mem.write(0x101A, 0xF5);
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
    mem.write(0x0202, 0x10);
    mem.write(0x101A, 0xF6);
    cpu.registerY = 0x0A;

    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, 0xF6, instructionName, registerName)) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, instructionName, "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, instructionName)) valid = false;
    

    return valid;
}





// Expected

bool expected_eq(bool value, bool expected, string instruction, string thing){
    if(value != expected){
        cout << instruction << " : " << thing << " not set properly (expected : '" << hex << (int)expected << "' - got : '" << hex << (int)value << "')" << endl;
        return false;
    }
    return true;
}

bool expected_eq(byte value, byte expected, string instruction, string thing){
    if(value != expected){
        cout << instruction << " : " << thing << " not set properly (expected : '" << hex << (int)expected << "' - got : '" << hex << (int)value << "')" << endl;
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