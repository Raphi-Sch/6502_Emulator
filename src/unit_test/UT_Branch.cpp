#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

bool branch(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string instructionName;
    byte* cpuRegister;

    reset_and_prepare_memory(mem);
    cpu.reset(mem);
    mem.write(0x200, instruction);

    switch(instruction){
        case CPU::INS_BCC:
            instructionName = "INS_BCC";
            cpu.CarryFlag = 0;
            mem.write(0x201, 0x05);
            break;

        case CPU::INS_BCS:
            instructionName = "INS_BCS";
            cpu.CarryFlag = 1;
            mem.write(0x201, 0x05);
            break;

        case CPU::INS_BEQ:
            instructionName = "INS_BEQ";
            cpu.ZeroFlag = 1;
            mem.write(0x201, 0x05);
            break;

        case CPU::INS_BMI:
            instructionName = "INS_BMI";
            cpu.NegativeFlag = 1;
            mem.write(0x201, 0x05);
            break;

        case CPU::INS_BNE:
            instructionName = "INS_BNE";
            cpu.ZeroFlag = 0;
            mem.write(0x201, 0x05);
            break;

        case CPU::INS_BPL:
            instructionName = "INS_BPL";
            cpu.NegativeFlag = 0;
            mem.write(0x201, 0x05);
            break;

        default:
            cout << "Branch doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }
 
    CPU cpuCopy = cpu;
    cpu.step_run(mem);



    if(!expected_eq(cpu.ProgramCounter, 0x207, instructionName, "Program Counter")) valid = false;

    if(!no_flags_affected(cpu, cpuCopy, instructionName)) valid = false;
    
    return valid;
}

int * run_branch(CPU& cpu, Memory& mem){
    static int result[2];

    result[0]++; if(branch(cpu, mem, CPU::INS_BCC)) result[1]++;
    result[0]++; if(branch(cpu, mem, CPU::INS_BCS)) result[1]++;
    result[0]++; if(branch(cpu, mem, CPU::INS_BEQ)) result[1]++;
    result[0]++; if(branch(cpu, mem, CPU::INS_BMI)) result[1]++;
    result[0]++; if(branch(cpu, mem, CPU::INS_BNE)) result[1]++;
    result[0]++; if(branch(cpu, mem, CPU::INS_BPL)) result[1]++;

    return result;
}