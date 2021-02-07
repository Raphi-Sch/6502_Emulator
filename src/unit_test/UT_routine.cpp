#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

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

bool rti(CPU& cpu, Memory& mem){
    bool valid = true;

    // Memory
    // PC in memory 0x1050;
    mem.write(0x01FF, 0x50);
    mem.write(0x01FE, 0x10);
    mem.write(0x01FD, 0xFF);

    // Reseting cpu
    cpu.reset(mem);
    cpu.StackPointer = 0xFC;

    mem.write(0x0200, CPU::INS_RTI);
    
    cpu.step_run(mem);

    if(!expected_eq(cpu.ProgramCounter, 0x5010, "INS_RTI", "Return from sub ADDR")) valid = false;
    if(!expected_eq(cpu.CarryFlag, 1, "INS_RTI", "CarryFlag")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 1, "INS_RTI", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.InterruptDisable, 1, "INS_RTI", "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, 1, "INS_RTI", "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, 1, "INS_RTI", "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, 1, "INS_RTI", "OverflowFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 1, "INS_RTI", "NegativeFlag")) valid = false;

    return valid;
}

int * run_routine(CPU& cpu, Memory& mem){
    static int result[2];

    // Jump
    result[0]++; if(jump(cpu, mem, CPU::INS_JMP_ABS)) result[1]++;
    result[0]++; if(jump(cpu, mem, CPU::INS_JMP_IND)) result[1]++;

    // Sub Routine
    result[0]++; if(jsr(cpu, mem)) result[1]++;
    result[0]++; if(rts(cpu, mem)) result[1]++;

    // Return from Interrupt
    result[0]++; if(rti(cpu, mem)) result[1]++;

    return result;
}