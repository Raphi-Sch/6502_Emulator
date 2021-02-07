#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

bool ASL(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string instructionName;
    byte* cpuRegister;
    word addr;

    reset_and_prepare_memory(mem);
    cpu.reset(mem);
    
    cpu.Accumulator = 0xFF;
    cpu.CarryFlag = 0;
    mem.write(0x200, instruction);

    switch(instruction){
        case CPU::INS_ASL_ACC:
            instructionName = "INS_ASL_ACC";
            break;

        case CPU::INS_ASL_ZP:
            instructionName = "INS_ASL_ZP";
            mem.write(0x201, 0x23);
            mem.write(0x23, 0xFF);
            addr = 0x23;
            break;

        case CPU::INS_ASL_ZPX:
            instructionName = "INS_ASL_ZPX";
            mem.write(0x201, 0x23);
            cpu.registerX = 0x02;
            mem.write(0x25, 0xFF);
            addr = 0x25;
            break;

        case CPU::INS_ASL_ABS:
            instructionName = "INS_ASL_ABS";
            mem.write(0x201, 0x30);
            mem.write(0x202, 0x12);
            mem.write(0x1230, 0xFF);
            addr = 0x1230;
            break;

        case CPU::INS_ASL_ABSX:
            instructionName = "INS_ASL_ABSX";
            mem.write(0x201, 0x30);
            mem.write(0x202, 0x12);
            cpu.registerX = 0x05;
            mem.write(0x1235, 0xFF);
            addr = 0x1235;
            break;

        default:
            cout << "ASL doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }
 
    CPU cpuCopy = cpu;
    cpu.step_run(mem);


    if(instruction == CPU::INS_ASL_ACC){ if(!expected_eq(cpu.Accumulator, 0xFE, instructionName, "Accumulator")) valid = false; }
    else { if(!expected_eq(mem.read(addr), 0xFE, instructionName, "Accumulator")) valid = false; }

    if(!expected_eq(cpu.ZeroFlag, 0, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 1, instructionName, "NegativeFlag")) valid = false;

    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, instructionName, "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, instructionName, "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, instructionName, "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, instructionName, "OverflowFlag")) valid = false;

    return valid;
}

int * run_ASL(CPU& cpu, Memory& mem){
    static int result[2];

    result[0]++; if(ASL(cpu, mem, CPU::INS_ASL_ACC)) result[1]++;
    result[0]++; if(ASL(cpu, mem, CPU::INS_ASL_ZP)) result[1]++;
    result[0]++; if(ASL(cpu, mem, CPU::INS_ASL_ZPX)) result[1]++;
    result[0]++; if(ASL(cpu, mem, CPU::INS_ASL_ABS)) result[1]++;
    result[0]++; if(ASL(cpu, mem, CPU::INS_ASL_ABSX)) result[1]++;

    return result;
}