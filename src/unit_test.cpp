#include "unit_test.h"

using namespace std;

void run_all_test(CPU& cpu, Memory& mem){
    int nb_test = 0;
    int test_passed = 0;

    // Setting reset vector
    mem.write(0xfffc, 0x00);
    mem.write(0xfffd, 0x02);

    nb_test++; if(LDA_IM(cpu, mem)) test_passed++;
    nb_test++; if(LDA_ZP(cpu, mem)) test_passed++;
    nb_test++; if(LDA_ZPX(cpu, mem)) test_passed++;
    nb_test++; if(LDA_ABS(cpu, mem)) test_passed++;
    nb_test++; if(LDA_ABSX(cpu, mem)) test_passed++;
    nb_test++; if(LDA_ABSY(cpu, mem)) test_passed++;
    nb_test++; if(LDA_INDX(cpu, mem)) test_passed++;
    nb_test++; if(LDA_INDY(cpu, mem)) test_passed++;
    
    cout << test_passed << " of " << nb_test << " test passed successfully" << endl;
}

bool LDA_IM(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    // ZeroFlag shoud be false, NegativeFlag shoud be true
    mem.write(0x0200, CPU::INS_LDA_IM);
    mem.write(0x0201, 0xF1);

    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, 0xF1, "INS_LDA_IM", "Accumulator")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, "INS_LDA_IM", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, "INS_LDA_IM", "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, "INS_LDA_IM")) valid = false;

    // Reseting cpu
    cpu.reset(mem);
    CpuCopy = cpu;

    // ZeroFlag shoud be true, NegativeFlag shoud be false
    mem.write(0x0200, CPU::INS_LDA_IM);
    mem.write(0x0201, 0x00);

    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, 0x00, "INS_LDA_IM", "Accumulator")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, true, "INS_LDA_IM", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, false, "INS_LDA_IM", "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, "INS_LDA_IM")) valid = false;

    return valid;
}

bool LDA_ZP(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, CPU::INS_LDA_ZP);
    mem.write(0x0201, 0x01);
    mem.write(0x0001, 0xF2);

    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, 0xF2, "INS_LDA_ZP", "Accumulator")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, "INS_LDA_ZP", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, "INS_LDA_ZP", "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, "INS_LDA_ZP")) valid = false;

    return valid;
}

bool LDA_ZPX(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, CPU::INS_LDA_ZPX);
    mem.write(0x0201, 0x01);
    mem.write(0x000A, 0xF3);
    cpu.registerX = 0x09;

    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, 0xF3, "INS_LDA_ZPX", "Accumulator")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, "INS_LDA_ZPX", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, "INS_LDA_ZPX", "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, "INS_LDA_ZPX")) valid = false;

    return valid;
}

bool LDA_ABS(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    
    CPU CpuCopy = cpu;

    mem.write(0x0200, CPU::INS_LDA_ABS);
    mem.write(0x0201, 0x10);
    mem.write(0x0202, 0x10);
    mem.write(0x1010, 0xF4);

    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, 0xF4, "INS_LDA_ABS", "Accumulator")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, false, "INS_LDA_ABS", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, true, "INS_LDA_ABS", "NegativeFlag")) valid = false;
    if(!load_register_not_changing_unexpected_flags(cpu, CpuCopy, "INS_LDA_ABS")) valid = false;

    return valid;
}

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