#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

bool ADC(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string instructionName;
    byte* cpuRegister;

    cpu.reset(mem);
    cpu.Accumulator = 0xF0;
    cpu.CarryFlag = 0;
    mem.write(0x0200, instruction);

    switch(instruction){
        case CPU::INS_ADC_IM:
            instructionName = "INS_ADC_IM";
            mem.write(0x0201, 0x05);
            break;

        case CPU::INS_ADC_ZP:
            instructionName = "INS_ADC_ZP";
            mem.write(0x0201, 0x0A);
            mem.write(0x000A, 0x05);
            break;

        case CPU::INS_ADC_ZPX:
            instructionName = "INS_ADC_ZPX";
            mem.write(0x0201, 0x0A);
            cpu.registerX = 0x01;
            mem.write(0x000B, 0x05);
            break;

        case CPU::INS_ADC_ABS:
            instructionName = "INS_ADC_ABS";
            mem.write(0x0201, 0x0A);
            mem.write(0x0202, 0x0B);
            mem.write(0x0B0A, 0x05);
            break;

        case CPU::INS_ADC_ABSX:
            instructionName = "INS_ADC_ABSX";
            mem.write(0x0201, 0x0A);
            mem.write(0x0202, 0x0B);
            cpu.registerX = 0x01;
            mem.write(0x0B0B, 0x05);
            break;

        case CPU::INS_ADC_ABSY:
            instructionName = "INS_ADC_ABSY";
            mem.write(0x0201, 0x0A);
            mem.write(0x0202, 0x0B);
            cpu.registerY = 0x02;
            mem.write(0x0B0C, 0x05);
            break;

        case CPU::INS_ADC_INDX:
            instructionName = "INS_ADC_INDX";
            mem.write(0x0201, 0x07);
            cpu.registerX = 0x03;

            mem.write(0x0A, 0x01);
            mem.write(0x0B, 0x03);
           
            mem.write(0x0301, 0x05);
            break;

        case CPU::INS_ADC_INDY:
            instructionName = "INS_ADC_INDY";
            mem.write(0x0201, 0x07);
            cpu.registerY = 0x03;

            mem.write(0x07, 0x02);
            mem.write(0x08, 0x03);

            mem.write(0x0305, 0x05);
            break;

        default:
            cout << "ADC doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }
 
    CPU CpuCopy = cpu;
    cpu.step_run(mem);

    if(!expected_eq(cpu.Accumulator, 0xF5, instructionName, "Accumulator")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 0, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 1, instructionName, "NegativeFlag")) valid = false;
    if(!only_C_and_Z_flags_affected(cpu, CpuCopy, instructionName)) valid = false;

    return valid;
}

int * run_ADC(CPU& cpu, Memory& mem){
    static int result[2];

    result[0]++; if(ADC(cpu, mem, CPU::INS_ADC_IM)) result[1]++;
    result[0]++; if(ADC(cpu, mem, CPU::INS_ADC_ZP)) result[1]++;
    result[0]++; if(ADC(cpu, mem, CPU::INS_ADC_ZPX)) result[1]++;
    result[0]++; if(ADC(cpu, mem, CPU::INS_ADC_ABS)) result[1]++;
    result[0]++; if(ADC(cpu, mem, CPU::INS_ADC_ABSX)) result[1]++;
    result[0]++; if(ADC(cpu, mem, CPU::INS_ADC_ABSY)) result[1]++;
    result[0]++; if(ADC(cpu, mem, CPU::INS_ADC_INDX)) result[1]++;
    result[0]++; if(ADC(cpu, mem, CPU::INS_ADC_INDY)) result[1]++;

    return result;
}