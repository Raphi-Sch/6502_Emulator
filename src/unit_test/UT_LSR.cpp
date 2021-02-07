#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

bool LSR(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string instructionName;
    byte data = 0xFF;
    word addr;

    reset_and_prepare_memory(mem);
    cpu.reset(mem);
    cpu.CarryFlag = 0;
    cpu.ZeroFlag = 1;
    cpu.NegativeFlag = 1;
    mem.write(0x200, instruction);

    switch(instruction){
        case CPU::INS_LSR_ACC:
            instructionName = "INS_LSR_ACC";
            cpu.Accumulator = data;
            break;

        case CPU::INS_LSR_ZP:
            instructionName = "INS_LSR_ZP";
            mem.write(0x201, 0x12);
            mem.write(0x12, data);
            addr = 0x12;
            break;

        case CPU::INS_LSR_ZPX:
            instructionName = "INS_LSR_ZPX";
            mem.write(0x201, 0x12);
            cpu.registerX = 0x03;
            mem.write(0x15, data);
            addr = 0x15;
            break;

        case CPU::INS_LSR_ABS:
            instructionName = "INS_LSR_ABS";
            mem.write(0x201, 0xBA);
            mem.write(0x202, 0xDC);
            mem.write(0xDCBA, data);
            addr = 0xDCBA;
            break;

        case CPU::INS_LSR_ABSX:
            instructionName = "INS_LSR_ABSX";
            mem.write(0x201, 0xBA);
            mem.write(0x202, 0xDC);
            cpu.registerX = 0x01;
            mem.write(0xDCBB, data);
            addr = 0xDCBB;
            break;

        default:
            cout << "LSR doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }
 
    CPU cpuCopy = cpu;
    cpu.step_run(mem);

    if(instruction == CPU::INS_LSR_ACC){ if(!expected_eq(cpu.Accumulator, (data >> 1), instructionName, "Accumulator")) valid = false; }
    else{ if(!expected_eq(mem.read(addr), (data >> 1), instructionName, "Mem location")) valid = false; }

    if(!expected_eq(cpu.CarryFlag, 1, instructionName, "CarryFlag")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 0, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 0, instructionName, "NegativeFlag")) valid = false;

    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, instructionName, "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, instructionName, "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, instructionName, "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, instructionName, "NegativeFlag")) valid = false;

    return valid;
}

int * run_LSR(CPU& cpu, Memory& mem){
    static int result[2];

    result[0]++; if(LSR(cpu, mem, CPU::INS_LSR_ACC)) result[1]++;
    result[0]++; if(LSR(cpu, mem, CPU::INS_LSR_ZP)) result[1]++;
    result[0]++; if(LSR(cpu, mem, CPU::INS_LSR_ZPX)) result[1]++;
    result[0]++; if(LSR(cpu, mem, CPU::INS_LSR_ABS)) result[1]++;
    result[0]++; if(LSR(cpu, mem, CPU::INS_LSR_ABSX)) result[1]++;

    return result;
}