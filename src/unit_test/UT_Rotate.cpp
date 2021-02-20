#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

bool ROL(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string instructionName;
    byte data = 0xAA;
    byte expected_data = 0x54;
    word addr;

    reset_and_prepare_memory(mem);
    cpu.reset(mem);
    cpu.CarryFlag = 0;
    cpu.ZeroFlag = 1;
    cpu.NegativeFlag = 1;
    mem.write(0x200, instruction);

    switch(instruction){
        case CPU::INS_ROL_ACC:
            instructionName = "INS_ROL_ACC";
            cpu.Accumulator = data;
            break;

        case CPU::INS_ROL_ZP:
            instructionName = "INS_ROL_ZP";
            mem.write(0x201, 0xF2); // Addr in ZP
            mem.write(0xF2, data);  // Data
            addr = 0xF2;
            break;

        case CPU::INS_ROL_ZPX:
            instructionName = "INS_ROL_ZPX";
            mem.write(0x201, 0xF2); // Addr in ZP
            cpu.registerX = 0x01;   // Offset
            mem.write(0xF3, data);  // Data
            addr = 0xF3;
            break;

        case CPU::INS_ROL_ABS:
            instructionName = "INS_ROL_ABS";
            mem.write(0x201, 0x02); // LSB of Addr
            mem.write(0x202, 0x0F); // MSB of Addr
            mem.write(0xF02, data); // Data
            addr = 0xF02;
            break;

        case CPU::INS_ROL_ABSX:
            instructionName = "INS_ROL_ABSX";
            cpu.registerX = 0x01;   // Offset
            mem.write(0x201, 0x02); // LSB of Addr
            mem.write(0x202, 0x0F); // MSB of Addr
            mem.write(0xF03, data); // Data       
            addr = 0xF03;
            break;

        default:
            cout << "ROL doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }
 
    CPU cpuCopy = cpu;
    cpu.step_run(mem);

    if(instruction == CPU::INS_ROL_ACC){ 
        if(!expected_eq(cpu.Accumulator, expected_data, instructionName, "Accumulator")) valid = false; 
    }
    else{ 
        if(!expected_eq(mem.read(addr), expected_data, instructionName, "Mem location")) valid = false; 
    }

    if(!expected_eq(cpu.CarryFlag, 1, instructionName, "CarryFlag")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 0, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 0, instructionName, "NegativeFlag")) valid = false;

    // Flags not affected
    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, instructionName, "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, instructionName, "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, instructionName, "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, instructionName, "NegativeFlag")) valid = false;

    return valid;
}

bool ROR(CPU& cpu, Memory& mem, byte instruction){
    bool valid = true;
    string instructionName;
    byte data = 0x54;
    byte expected_data = 0xAA;
    word addr;

    reset_and_prepare_memory(mem);
    cpu.reset(mem);
    cpu.CarryFlag = 1;
    cpu.ZeroFlag = 1;
    cpu.NegativeFlag = 0;
    mem.write(0x200, instruction);

    switch(instruction){
        case CPU::INS_ROR_ACC:
            instructionName = "INS_ROR_ACC";
            cpu.Accumulator = data;
            break;

        case CPU::INS_ROR_ZP:
            instructionName = "INS_ROR_ZP";
            mem.write(0x201, 0xF2); // Addr in ZP
            mem.write(0xF2, data);  // Data
            addr = 0xF2;
            break;

        case CPU::INS_ROR_ZPX:
            instructionName = "INS_ROR_ZPX";
            mem.write(0x201, 0xF2); // Addr in ZP
            cpu.registerX = 0x01;   // Offset
            mem.write(0xF3, data);  // Data
            addr = 0xF3;
            break;

        case CPU::INS_ROR_ABS:
            instructionName = "INS_ROR_ABS";
            mem.write(0x201, 0x02); // LSB of Addr
            mem.write(0x202, 0x0F); // MSB of Addr
            mem.write(0xF02, data); // Data
            addr = 0xF02;
            break;

        case CPU::INS_ROR_ABSX:
            instructionName = "INS_ROR_ABSX";
            cpu.registerX = 0x01;   // Offset
            mem.write(0x201, 0x02); // LSB of Addr
            mem.write(0x202, 0x0F); // MSB of Addr
            mem.write(0xF03, data); // Data       
            addr = 0xF03;
            break;

        default:
            cout << "ROL doesn't handle : " << hex << (int)instruction << endl;
            return false;
    }
 
    CPU cpuCopy = cpu;
    cpu.step_run(mem);

    if(instruction == CPU::INS_ROR_ACC){ 
        if(!expected_eq(cpu.Accumulator, expected_data, instructionName, "Accumulator")) valid = false; 
    }
    else{ 
        if(!expected_eq(mem.read(addr), expected_data, instructionName, "Mem location")) valid = false; 
    }

    if(!expected_eq(cpu.CarryFlag, 0, instructionName, "CarryFlag")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, 0, instructionName, "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, 1, instructionName, "NegativeFlag")) valid = false;

    // Flags not affected
    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, instructionName, "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, instructionName, "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, instructionName, "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, instructionName, "NegativeFlag")) valid = false;

    return valid;
}

int * run_rotate(CPU& cpu, Memory& mem){
    static int result[2];

    result[0]++; if(ROL(cpu, mem, CPU::INS_ROL_ACC)) result[1]++;
    result[0]++; if(ROL(cpu, mem, CPU::INS_ROL_ZP)) result[1]++;
    result[0]++; if(ROL(cpu, mem, CPU::INS_ROL_ZPX)) result[1]++;
    result[0]++; if(ROL(cpu, mem, CPU::INS_ROL_ABS)) result[1]++;
    result[0]++; if(ROL(cpu, mem, CPU::INS_ROL_ABSX)) result[1]++;

    result[0]++; if(ROR(cpu, mem, CPU::INS_ROR_ACC)) result[1]++;
    result[0]++; if(ROR(cpu, mem, CPU::INS_ROR_ZP)) result[1]++;
    result[0]++; if(ROR(cpu, mem, CPU::INS_ROR_ZPX)) result[1]++;
    result[0]++; if(ROR(cpu, mem, CPU::INS_ROR_ABS)) result[1]++;
    result[0]++; if(ROR(cpu, mem, CPU::INS_ROR_ABSX)) result[1]++;

    return result;
}