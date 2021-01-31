#include "unit_test.h"

using namespace std;

void run_all_test(CPU& cpu, Memory& mem){
    const int nb_test = 1;
    int test_passed = 0;
    cout << "There are " << nb_test << " to do." << endl;

    if(LDA_immediate(cpu, mem)) test_passed++;
    
    cout << test_passed << " of " << nb_test << " test passed successfully" << endl;
}

bool LDA_immediate(CPU& cpu, Memory& mem){
    bool valid = true;
    
    // Reseting cpu
    cpu.reset(mem);
    CPU CpuCopy = cpu;

    // ZeroFlag shoud be false, NegativeFlag shoud be true
    mem.write(0x0200, CPU::INS_LDA_IM);
    mem.write(0x0201, 0xFF);

    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, 0xFF, "INS_LDA_IM", "Accumulator")) valid = false;
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

bool expected_eq(bool value, bool expected, string instruction, string thing){
    if(value != expected){
        cout << instruction << " : " << thing << " not set properly ( expected : '" << expected << "' - got : '" << value << "')" << endl;
        return false;
    }
    return true;
}

bool expected_eq(byte value, byte expected, string instruction, string thing){
    if(value != expected){
        cout << instruction << " : " << thing << " not set properly ( expected : '" << hex << expected << "' - got : '" << value << "')" << endl;
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