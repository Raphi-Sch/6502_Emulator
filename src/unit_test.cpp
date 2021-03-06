#include "unit_test.h"
#include "unit_test/UT_register_load.cpp"
#include "unit_test/UT_register_manipulation.cpp"
#include "unit_test/UT_register_store.cpp"
#include "unit_test/UT_routine.cpp"
#include "unit_test/UT_stack.cpp"
#include "unit_test/UT_flags.cpp"
#include "unit_test/UT_ADC.cpp"
#include "unit_test/UT_AND.cpp"
#include "unit_test/UT_ASL.cpp"
#include "unit_test/UT_Branch.cpp"
#include "unit_test/UT_BIT.cpp"
#include "unit_test/UT_Compare.cpp"
#include "unit_test/UT_LSR.cpp"
#include "unit_test/UT_Decrement.cpp"
#include "unit_test/UT_Increment.cpp"
#include "unit_test/UT_ORA.cpp"
#include "unit_test/UT_EOR.cpp"
#include "unit_test/UT_Rotate.cpp"
#include "unit_test/UT_SBC.cpp"

using namespace std;

bool run_all_test(CPU& cpu, Memory& mem){
    int test_nb = 0;
    int test_passed = 0;
    int * result;

    reset_and_prepare_memory(mem);

    // NOP
    test_nb++; if(NOP(cpu, mem)) test_passed++;

    // BRK
    test_nb++; if(BRK(cpu, mem)) test_passed++;

    // Routine
    result = run_routine(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // Store register
    result = run_register_load(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // Stack Instructions
    result = run_stack(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // Store register
    result = run_register_store(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];
    
    // Increment-Decrement register
    result = run_register_manipulation(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // Flags
    result = run_flags(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // ADC
    result = run_ADC(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // AND
    result = run_AND(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];
    
    // ASL
    result = run_ASL(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // Branch if
    result = run_branch(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // BIT
    result = run_BIT(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // CMP
    result = run_compare(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // CMP
    result = run_LSR(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // Decrement
    result = run_decrement(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // Increment
    result = run_increment(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // Logical OR
    result = run_ORA(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // Logical EOR
    result = run_EOR(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // Rotation (shifting)
    result = run_rotate(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // SBC
    result = run_SBC(cpu, mem);
    test_nb += result[0];
    test_passed += result[1];

    // Result
    cout << dec << test_passed << " of " << test_nb << " test passed successfully." << endl;

    return test_passed == test_nb;
}

// Reset
void reset_and_prepare_memory(Memory& mem){
    mem.clear();
    mem.write(0xfffc, 0x00);
    mem.write(0xfffd, 0x02);
}

// No Operation
bool NOP(CPU& cpu, Memory& mem){
    bool valid = true;

    cpu.reset(mem);
    CPU cpuCopy = cpu;
    mem.write(0x0200, CPU::INS_NOP);
    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, cpuCopy.Accumulator, "INS_NOP", "Accumulator")) valid = false;
    if(!expected_eq(cpu.registerX, cpuCopy.registerX, "INS_NOP", "registerX")) valid = false;
    if(!expected_eq(cpu.registerY, cpuCopy.registerY, "INS_NOP", "registerY")) valid = false;
    if(!expected_eq(cpu.ProgramCounter, cpuCopy.ProgramCounter + 0x01, "INS_NOP", "ProgramCounter")) valid = false;
    if(!expected_eq(cpu.StackPointer, cpuCopy.StackPointer, "INS_NOP", "StackPointer")) valid = false;
    if(!no_flags_affected(cpu, cpuCopy, "INS_NOP")) valid = false;

    return valid;
}

bool BRK(CPU& cpu, Memory& mem){
    bool valid = true;

    cpu.reset(mem);
    reset_and_prepare_memory(mem);

    mem.write(0x200, CPU::INS_BRK);
    mem.write(0xFFFE, 0x89);
    mem.write(0xFFFF, 0x67);

    CPU cpuCopy = cpu;
    cpu.step_run(mem);


    if(!expected_eq(mem.read(0x1FF), 0x01, "INS_BRK", "LSB Program Counter store in stack")) valid = false;
    if(!expected_eq(mem.read(0x1FE), 0x02, "INS_BRK", "MSB Program Counter in stack")) valid = false;
    if(!expected_eq(mem.read(0x1FD), 0x02, "INS_BRK", "Flags store in stack")) valid = false;

    // Not Affected
    if(!expected_eq(cpu.CarryFlag, cpuCopy.CarryFlag, "INS_BRK", "CarryFlag")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, cpuCopy.ZeroFlag, "INS_BRK", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, "INS_BRK", "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, "INS_BRK", "DecimalMode")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, "INS_BRK", "OverflowFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, cpuCopy.NegativeFlag, "INS_BRK", "NegativeFlag")) valid = false;

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

bool only_Z_and_N_flags_affected(CPU& cpu, CPU& copy, string instruction){
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