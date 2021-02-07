#include "unit_test.h"
#include "unit_test/UT_register_load.cpp"
#include "unit_test/UT_register_manipulation.cpp"
#include "unit_test/UT_register_store.cpp"
#include "unit_test/UT_routine.cpp"
#include "unit_test/UT_stack.cpp"

using namespace std;

void run_all_test(CPU& cpu, Memory& mem){
    int test_nb = 0;
    int test_passed = 0;
    int * result;

    reset(mem);

    // NOP
    test_nb++; if(NOP(cpu, mem)) test_passed++;

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

    // Result
    cout << dec << test_passed << " of " << test_nb << " test passed successfully." << endl;
}


// Reset
void reset(Memory& mem){
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

bool only_C_and_Z_flags_affected(CPU& cpu, CPU& copy, string instruction){
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