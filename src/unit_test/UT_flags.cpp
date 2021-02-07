#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "../unit_test.h"
#endif

bool SEC(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    CPU cpuCopy = cpu;

    mem.write(0x0200, CPU::INS_SEC);

    cpu.step_run(mem);

    // Set to true
    if(!expected_eq(cpu.CarryFlag, 1, "INS_SEC", "CarryFlag")) valid = false;

    // Not Affected
    if(!expected_eq(cpu.ZeroFlag, cpuCopy.ZeroFlag, "INS_SEC", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, "INS_SEC", "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, "INS_SEC", "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, "INS_SEC", "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, "INS_SEC", "OverflowFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, cpuCopy.NegativeFlag, "INS_SEC", "NegativeFlag")) valid = false;

    return valid;
}

bool SED(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    CPU cpuCopy = cpu;

    mem.write(0x0200, CPU::INS_SED);

    cpu.step_run(mem);

    // Set to true
    if(!expected_eq(cpu.DecimalMode, 1, "INS_SED", "DecimalMode")) valid = false;

    // Not Affected
    if(!expected_eq(cpu.CarryFlag, cpuCopy.CarryFlag, "INS_SED", "CarryFlag")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, cpuCopy.ZeroFlag, "INS_SED", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, "INS_SED", "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, "INS_SED", "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, "INS_SED", "OverflowFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, cpuCopy.NegativeFlag, "INS_SED", "NegativeFlag")) valid = false;

    return valid;
}

bool SEI(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    CPU cpuCopy = cpu;

    mem.write(0x0200, CPU::INS_SEI);

    cpu.step_run(mem);

    // Set to true
    if(!expected_eq(cpu.InterruptDisable, 1, "INS_SEI", "InterruptDisable")) valid = false;

    // Not Affected
    if(!expected_eq(cpu.CarryFlag, cpuCopy.CarryFlag, "INS_SEI", "CarryFlag")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, cpuCopy.ZeroFlag, "INS_SEI", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, "INS_SEI", "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, "INS_SEI", "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, "INS_SEI", "OverflowFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, cpuCopy.NegativeFlag, "INS_SEI", "NegativeFlag")) valid = false;

    return valid;
}

int * run_flags(CPU& cpu, Memory& mem){
    static int result[2];

    result[0]++; if(SEC(cpu, mem)) result[1]++;
    result[0]++; if(SED(cpu, mem)) result[1]++;
    result[0]++; if(SEI(cpu, mem)) result[1]++;

    return result;
}