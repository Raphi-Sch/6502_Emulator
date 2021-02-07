#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

bool AND(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string instructionName;
    byte* cpuRegister;

    reset_and_prepare_memory(mem);
    cpu.reset(mem);

    cpu.Accumulator = 0xFF;
    mem.write(0x200, instruction);

    switch(instruction){
        case CPU::INS_AND_IM:
            instructionName = "INS_AND_IM";
            mem.write(0x201, 0x0F); // Data
            break;

        case CPU::INS_AND_ZP:
            instructionName = "INS_AND_ZP";
            mem.write(0x201, 0xF2); // Addr in ZP
            mem.write(0xF2, 0x0F);  // Data in ZP
            break;

        case CPU::INS_AND_ZPX:
            instructionName = "INS_AND_ZPX";
            mem.write(0x201, 0xF2); // Addr in ZP
            cpu.registerX = 0x02;   // Addr offset
            mem.write(0xF4, 0x0F);  // Data in ZP
            break;

        case CPU::INS_AND_ABS:
            instructionName = "INS_AND_ABS";
            mem.write(0x201, 0x02); // LSB of Addr
            mem.write(0x202, 0x0F); // MSB of Addr
            mem.write(0xF02, 0x0F); // Data
            break;

        case CPU::INS_AND_ABSX:
            instructionName = "INS_AND_ABSX";
            mem.write(0x201, 0x02); // LSB of Addr
            mem.write(0x202, 0x0F); // MSB of Addr
            cpu.registerX = 0x03;   // Addr offset
            mem.write(0xF05, 0x0F); // Data
            break;

        case CPU::INS_AND_ABSY:
            instructionName = "INS_AND_ABSY";
            mem.write(0x201, 0x02); // LSB of Addr
            mem.write(0x202, 0x0F); // MSB of Addr
            cpu.registerY = 0x04;   // Addr offset
            mem.write(0xF06, 0x0F); // Data
            break;

        case CPU::INS_AND_INDX:
            instructionName = "INS_AND_INDX";
            mem.write(0x0201, 0x07);
            cpu.registerX = 0x03;

            mem.write(0x0A, 0x01);
            mem.write(0x0B, 0x03);
           
            mem.write(0x0301, 0x0F);
            break;

        case CPU::INS_AND_INDY:
            instructionName = "INS_AND_INDY";
            mem.write(0x0201, 0x07);
            cpu.registerY = 0x03;

            mem.write(0x07, 0x02);
            mem.write(0x08, 0x03);

            mem.write(0x0305, 0x0F);

            break;

        default:
            cout << "AND doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }
 
    CPU CpuCopy = cpu;
    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, 0x0F, instructionName, "Accumulator")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 0, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 0, instructionName, "NegativeFlag")) valid = false;
    if(!only_C_and_Z_flags_affected(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

int * run_AND(CPU& cpu, Memory& mem){
    static int result[2];

    result[0]++; if(AND(cpu, mem, CPU::INS_AND_IM)) result[1]++;
    result[0]++; if(AND(cpu, mem, CPU::INS_AND_ZP)) result[1]++;
    result[0]++; if(AND(cpu, mem, CPU::INS_AND_ZPX)) result[1]++;
    result[0]++; if(AND(cpu, mem, CPU::INS_AND_ABS)) result[1]++;
    result[0]++; if(AND(cpu, mem, CPU::INS_AND_ABSX)) result[1]++;
    result[0]++; if(AND(cpu, mem, CPU::INS_AND_ABSY)) result[1]++;
    result[0]++; if(AND(cpu, mem, CPU::INS_AND_INDX)) result[1]++;
    result[0]++; if(AND(cpu, mem, CPU::INS_AND_INDY)) result[1]++;

    return result;
}