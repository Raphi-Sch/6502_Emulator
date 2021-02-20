#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

bool SBC(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string instructionName;
    byte* cpuRegister;
    
    reset_and_prepare_memory(mem);
    cpu.reset(mem);

    cpu.Accumulator = 0xF0;
    byte initial_data = 0xD0;
    byte expected_data = 0x20; // 0xF0 - 0xD0 = 0x20

    cpu.CarryFlag = 1;
    mem.write(0x0200, instruction);

    switch(instruction){
        case CPU::INS_SBC_IM:
            instructionName = "INS_SBC_IM";
            mem.write(0x0201, initial_data);
            break;

        case CPU::INS_SBC_ZP:
            instructionName = "INS_SBC_ZP";
            mem.write(0x0201, 0x0A);
            mem.write(0x000A, initial_data);
            break;

        case CPU::INS_SBC_ZPX:
            instructionName = "INS_SBC_ZPX";
            mem.write(0x0201, 0x0A);
            cpu.registerX = 0x01;
            mem.write(0x000B, initial_data);
            break;

        case CPU::INS_SBC_ABS:
            instructionName = "INS_SBC_ABS";
            mem.write(0x0201, 0x0A);
            mem.write(0x0202, 0x0B);
            mem.write(0x0B0A, initial_data);
            break;

        case CPU::INS_SBC_ABSX:
            instructionName = "INS_SBC_ABSX";
            mem.write(0x0201, 0x0A);
            mem.write(0x0202, 0x0B);
            cpu.registerX = 0x01;
            mem.write(0x0B0B, initial_data);
            break;

        case CPU::INS_SBC_ABSY:
            instructionName = "INS_SBC_ABSY";
            mem.write(0x0201, 0x0A);
            mem.write(0x0202, 0x0B);
            cpu.registerY = 0x02;
            mem.write(0x0B0C, initial_data);
            break;

        case CPU::INS_SBC_INDX:
            instructionName = "INS_SBC_INDX";
            mem.write(0x0201, 0x07);
            cpu.registerX = 0x03;

            mem.write(0x0A, 0x01);
            mem.write(0x0B, 0x03);
           
            mem.write(0x0301, initial_data);
            break;

        case CPU::INS_SBC_INDY:
            instructionName = "INS_SBC_INDY";
            mem.write(0x0201, 0x07);
            cpu.registerY = 0x03;

            mem.write(0x07, 0x02);
            mem.write(0x08, 0x03);

            mem.write(0x0305, initial_data);
            break;

        default:
            cout << "SBC doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }
 
    CPU CpuCopy = cpu;
    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, expected_data, instructionName, "Accumulator")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 0, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 0, instructionName, "NegativeFlag")) valid = false;
    if(!expected_eq(cpu.CarryFlag, 0, instructionName, "CarryFlag")) valid = false;

    // Flags not affected
    if(!expected_eq(cpu.InterruptDisable, CpuCopy.InterruptDisable, instructionName, "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, CpuCopy.DecimalMode, instructionName, "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, CpuCopy.BreakCommand, instructionName, "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, CpuCopy.OverflowFlag, instructionName, "NegativeFlag")) valid = false;

    return valid;
}

int * run_SBC(CPU& cpu, Memory& mem){
    static int result[2];

    result[0]++; if(SBC(cpu, mem, CPU::INS_SBC_IM)) result[1]++;
    result[0]++; if(SBC(cpu, mem, CPU::INS_SBC_ZP)) result[1]++;
    result[0]++; if(SBC(cpu, mem, CPU::INS_SBC_ZPX)) result[1]++;
    result[0]++; if(SBC(cpu, mem, CPU::INS_SBC_ABS)) result[1]++;
    result[0]++; if(SBC(cpu, mem, CPU::INS_SBC_ABSX)) result[1]++;
    result[0]++; if(SBC(cpu, mem, CPU::INS_SBC_ABSY)) result[1]++;
    result[0]++; if(SBC(cpu, mem, CPU::INS_SBC_INDX)) result[1]++;
    result[0]++; if(SBC(cpu, mem, CPU::INS_SBC_INDY)) result[1]++;

    return result;
}