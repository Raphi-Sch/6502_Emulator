#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

bool CMP(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string instructionName;
    word addr;

    reset_and_prepare_memory(mem);
    cpu.reset(mem);
    cpu.Accumulator = 0x0F;
    cpu.CarryFlag = 0;      // To check if it is set
    cpu.ZeroFlag = 0;       // To check if it is set
    cpu.NegativeFlag = 1;   // To check if it is set
    mem.write(0x200, instruction);

    switch(instruction){
        case CPU::INS_CMP_IM:
            instructionName = "INS_CMP_IM";
            mem.write(0x201, 0x0F);
            break;

        case CPU::INS_CMP_ZP:
            instructionName = "INS_CMP_ZP";
            mem.write(0x201, 0x12);
            mem.write(0x12, 0x0F);
            break;

        case CPU::INS_CMP_ZPX:
            instructionName = "INS_CMP_ZPX";
            cpu.registerX = 0x05;
            mem.write(0x201, 0x12);
            mem.write(0x17, 0x0F);
            break;

        case CPU::INS_CMP_ABS:
            instructionName = "INS_CMP_ABS";
            mem.write(0x201, 0x65);
            mem.write(0x202, 0x87);
            mem.write(0x8765, 0x0F);
            break;

        case CPU::INS_CMP_ABSX:
            instructionName = "INS_CMP_ABSX";
            mem.write(0x201, 0x65);
            mem.write(0x202, 0x87);
            cpu.registerX = 0x03;
            mem.write(0x8768, 0x0F);
            break;

        case CPU::INS_CMP_ABSY:
            instructionName = "INS_CMP_ABSY";
            mem.write(0x201, 0x65);
            mem.write(0x202, 0x87);
            cpu.registerY = 0x05;
            mem.write(0x876A, 0x0F);
            break;

        case CPU::INS_CMP_INDX:
            instructionName = "INS_CMP_INDX";
            mem.write(0x0201, 0x07);
            cpu.registerX = 0x03;

            mem.write(0x0A, 0x01);
            mem.write(0x0B, 0x03);
           
            mem.write(0x0301, 0x0F);
            break;

        case CPU::INS_CMP_INDY:
            instructionName = "INS_CMP_IM";
            mem.write(0x0201, 0x07);
            cpu.registerY = 0x03;

            mem.write(0x07, 0x02);
            mem.write(0x08, 0x03);

            mem.write(0x0305, 0x0F);
            break;

        default:
            cout << "CMP doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }
 
    CPU cpuCopy = cpu;
    cpu.step_run(mem);

    if(!expected_eq(cpu.CarryFlag, 1, instructionName, "CarryFlag")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 1, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, instructionName, "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, instructionName, "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, instructionName, "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, instructionName, "OverflowFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 0, instructionName, "NegativeFlag")) valid = false;

    return valid;
}

bool CPX(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string instructionName;
    word addr;

    reset_and_prepare_memory(mem);
    cpu.reset(mem);
    cpu.registerX = 0x0F;
    cpu.CarryFlag = 0;      // To check if it is set
    cpu.ZeroFlag = 0;       // To check if it is set
    cpu.NegativeFlag = 1;   // To check if it is set
    mem.write(0x200, instruction);

    switch(instruction){
        case CPU::INS_CPX_IM:
            instructionName = "INS_CPX_IM";
            mem.write(0x201, 0x0F);
            break;

        case CPU::INS_CPX_ZP:
            instructionName = "INS_CPX_ZP";
            mem.write(0x201, 0x12);
            mem.write(0x12, 0x0F);
            break;

        case CPU::INS_CPX_ABS:
            instructionName = "INS_CPX_ABS";
            mem.write(0x201, 0x65);
            mem.write(0x202, 0x87);
            mem.write(0x8765, 0x0F);
            break;

        default:
            cout << "CPX doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }
 
    CPU cpuCopy = cpu;
    cpu.step_run(mem);

    if(!expected_eq(cpu.CarryFlag, 1, instructionName, "CarryFlag")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 1, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, instructionName, "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, instructionName, "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, instructionName, "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, instructionName, "OverflowFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 0, instructionName, "NegativeFlag")) valid = false;

    return valid;
}

bool CPY(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string instructionName;
    word addr;

    reset_and_prepare_memory(mem);
    cpu.reset(mem);
    cpu.registerY = 0x0F;
    cpu.CarryFlag = 0;      // To check if it is set
    cpu.ZeroFlag = 0;       // To check if it is set
    cpu.NegativeFlag = 1;   // To check if it is set
    mem.write(0x200, instruction);

    switch(instruction){
        case CPU::INS_CPY_IM:
            instructionName = "INS_CPY_IM";
            mem.write(0x201, 0x0F);
            break;

        case CPU::INS_CPY_ZP:
            instructionName = "INS_CPY_ZP";
            mem.write(0x201, 0x12);
            mem.write(0x12, 0x0F);
            break;

        case CPU::INS_CPY_ABS:
            instructionName = "INS_CPY_ABS";
            mem.write(0x201, 0x65);
            mem.write(0x202, 0x87);
            mem.write(0x8765, 0x0F);
            break;

        default:
            cout << "CPY doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }
 
    CPU cpuCopy = cpu;
    cpu.step_run(mem);

    if(!expected_eq(cpu.CarryFlag, 1, instructionName, "CarryFlag")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 1, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, instructionName, "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, instructionName, "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, instructionName, "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, instructionName, "OverflowFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 0, instructionName, "NegativeFlag")) valid = false;

    return valid;
}

int * run_compare(CPU& cpu, Memory& mem){
    static int result[2];

    result[0]++; if(CMP(cpu, mem, CPU::INS_CMP_IM)) result[1]++;
    result[0]++; if(CMP(cpu, mem, CPU::INS_CMP_ZP)) result[1]++;
    result[0]++; if(CMP(cpu, mem, CPU::INS_CMP_ZPX)) result[1]++;
    result[0]++; if(CMP(cpu, mem, CPU::INS_CMP_ABS)) result[1]++;
    result[0]++; if(CMP(cpu, mem, CPU::INS_CMP_ABSX)) result[1]++;
    result[0]++; if(CMP(cpu, mem, CPU::INS_CMP_ABSY)) result[1]++;
    result[0]++; if(CMP(cpu, mem, CPU::INS_CMP_INDX)) result[1]++;
    result[0]++; if(CMP(cpu, mem, CPU::INS_CMP_INDY)) result[1]++;

    result[0]++; if(CPX(cpu, mem, CPU::INS_CPX_IM)) result[1]++;
    result[0]++; if(CPX(cpu, mem, CPU::INS_CPX_ZP)) result[1]++;
    result[0]++; if(CPX(cpu, mem, CPU::INS_CPX_ABS)) result[1]++;

    result[0]++; if(CPY(cpu, mem, CPU::INS_CPY_IM)) result[1]++;
    result[0]++; if(CPY(cpu, mem, CPU::INS_CPY_ZP)) result[1]++;
    result[0]++; if(CPY(cpu, mem, CPU::INS_CPY_ABS)) result[1]++;

    return result;
}