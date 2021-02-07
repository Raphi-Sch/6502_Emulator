#include "unit_test.h"
#include "unit_test/UT_register_load.cpp"
#include "unit_test/UT_register_manipulation.cpp"
#include "unit_test/UT_register_store.cpp"
#include "unit_test/UT_stack.cpp"

using namespace std;

void run_all_test(CPU& cpu, Memory& mem){
    int test_nb = 0;
    int test_passed = 0;

    reset(mem);

    // JMP
    test_nb++; if(jump(cpu, mem, CPU::INS_JMP_ABS)) test_passed++;
    test_nb++; if(jump(cpu, mem, CPU::INS_JMP_IND)) test_passed++;

    // Sub Routine
    test_nb++; if(jsr(cpu, mem)) test_passed++;
    test_nb++; if(rts(cpu, mem)) test_passed++;
    
    // NOP
    test_nb++; if(NOP(cpu, mem)) test_passed++;

    // Store register
    int * result_register_load = run_register_load(cpu, mem);
    test_nb += result_register_load[0];
    test_passed += result_register_load[1];

    // Stack Instructions
    int * result_stack = run_stack(cpu, mem);
    test_nb += result_stack[0];
    test_passed += result_stack[1];

    // Store register
    int * result_register_store = run_register_store(cpu, mem);
    test_nb += result_register_store[0];
    test_passed += result_register_store[1];
    
    // Increment-Decrement register
    int * result_register_manipulation = run_register_manipulation(cpu, mem);
    test_nb += result_register_manipulation[0];
    test_passed += result_register_manipulation[1];

    // Result
    cout << dec << test_passed << " of " << test_nb << " test passed successfully." << endl;
}


// Reset
void reset(Memory& mem){
    mem.clear();
    mem.write(0xfffc, 0x00);
    mem.write(0xfffd, 0x02);
}



// Jump
bool jump(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string instructionName;
    byte* cpuRegister;
    word expected;

    // Reseting cpu
    cpu.reset(mem);
    CPU CpuCopy = cpu;

    switch(instruction){
        case CPU::INS_JMP_ABS:
            instructionName = "INS_JMP_ABS";
            mem.write(0x0201, 0xCD);
            mem.write(0x0202, 0XAB);
            expected = 0xABCD;
            break;

        case CPU::INS_JMP_IND:
            instructionName = "INS_JMP_IND";
            mem.write(0x0201, 0x34);
            mem.write(0x0202, 0x12);
            mem.write(0x0203, 0x35);
            mem.write(0x0204, 0x12);
            mem.write(0x1234, 0xCD);
            mem.write(0x1235, 0xAB);
            expected = 0xABCD;
            break;

        default:
            cout << "Jump doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }

    mem.write(0x0200, instruction);
    
    cpu.step_run(mem);

    if(!expected_eq(cpuRegister, expected, instructionName, "")) valid = false;
    if(!no_flags_affected(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

// Jump to SubRoutine
bool jsr(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    CPU CpuCopy = cpu;

    // Return ADDR is PC - 1
    mem.write(0x0200, CPU::INS_JSR);
    mem.write(0x0201, 0x56);
    mem.write(0x0202, 0x34);
    
    cpu.step_run(mem);

    if(!expected_eq(cpu.ProgramCounter, 0x3456, "INS_JSR", "Jump ADDR")) valid = false;
    if(!expected_eq((word)(mem.read(0x01FF) + (mem.read(0x01FE) << 8)), (word)0x0202 , "INS_JSR", "Return ADDR")) valid = false;
    if(!no_flags_affected(cpu, CpuCopy, "INS_JSR")) valid = false;

    return valid;
}

// Return from interrupt
bool rts(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    cpu.StackPointer = 0xFD;

    CPU CpuCopy = cpu;

    // Return ADDR is 0x5677 (jsr push PC - 1)
    mem.write(0x01FF, 0x56);
    mem.write(0x01FE, 0x77);

    mem.write(0x0200, CPU::INS_RTS);
    
    cpu.step_run(mem);

    if(!expected_eq(cpu.ProgramCounter, 0x5678, "INS_RTS", "Return from sub ADDR")) valid = false;
    if(!expected_eq(cpu.StackPointer, 0xFF, "INS_RTS", "StackPointer value")) valid = false;
    if(!no_flags_affected(cpu, CpuCopy, "INS_RTS")) valid = false;

    return valid;
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