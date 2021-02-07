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

bool CLC(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    CPU cpuCopy = cpu;

    mem.write(0x0200, CPU::INS_CLC);

    cpu.step_run(mem);

    // Set to true
    if(!expected_eq(cpu.CarryFlag, 0, "INS_CLC", "CarryFlag")) valid = false;

    // Not Affected
    if(!expected_eq(cpu.ZeroFlag, cpuCopy.ZeroFlag, "INS_CLC", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, "INS_CLC", "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, "INS_CLC", "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, "INS_CLC", "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, "INS_CLC", "OverflowFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, cpuCopy.NegativeFlag, "INS_CLC", "NegativeFlag")) valid = false;

    return valid;
}

bool CLD(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    CPU cpuCopy = cpu;

    mem.write(0x0200, CPU::INS_CLD);

    cpu.step_run(mem);

    // Set to true
    if(!expected_eq(cpu.DecimalMode, 0, "INS_CLD", "DecimalMode")) valid = false;

    // Not Affected
    if(!expected_eq(cpu.CarryFlag, cpuCopy.CarryFlag, "INS_CLD", "CarryFlag")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, cpuCopy.ZeroFlag, "INS_CLD", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, "INS_CLD", "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, "INS_CLD", "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, "INS_CLD", "OverflowFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, cpuCopy.NegativeFlag, "INS_CLD", "NegativeFlag")) valid = false;

    return valid;
}

bool CLI(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    CPU cpuCopy = cpu;

    mem.write(0x0200, CPU::INS_CLI);

    cpu.step_run(mem);

    // Set to true
    if(!expected_eq(cpu.InterruptDisable, 0, "INS_CLI", "InterruptDisable")) valid = false;

    // Not Affected
    if(!expected_eq(cpu.CarryFlag, cpuCopy.CarryFlag, "INS_CLI", "CarryFlag")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, cpuCopy.ZeroFlag, "INS_CLI", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, "INS_CLI", "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, "INS_CLI", "BreakCommand")) valid = false;
    if(!expected_eq(cpu.OverflowFlag, cpuCopy.OverflowFlag, "INS_CLI", "OverflowFlag")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, cpuCopy.NegativeFlag, "INS_CLI", "NegativeFlag")) valid = false;

    return valid;
}

bool CLV(CPU& cpu, Memory& mem){
    bool valid = true;

    // Reseting cpu
    cpu.reset(mem);
    CPU cpuCopy = cpu;

    mem.write(0x0200, CPU::INS_CLV);

    cpu.step_run(mem);

    // Set to true
    if(!expected_eq(cpu.OverflowFlag, 0, "INS_CLV", "OverflowFlag")) valid = false;

    // Not Affected
    if(!expected_eq(cpu.CarryFlag, cpuCopy.CarryFlag, "INS_CLV", "CarryFlag")) valid = false;
    if(!expected_eq(cpu.ZeroFlag, cpuCopy.ZeroFlag, "INS_CLV", "ZeroFlag")) valid = false;
    if(!expected_eq(cpu.InterruptDisable, cpuCopy.InterruptDisable, "INS_CLC", "InterruptDisable")) valid = false;
    if(!expected_eq(cpu.DecimalMode, cpuCopy.DecimalMode, "INS_CLV", "DecimalMode")) valid = false;
    if(!expected_eq(cpu.BreakCommand, cpuCopy.BreakCommand, "INS_CLV", "BreakCommand")) valid = false;
    if(!expected_eq(cpu.NegativeFlag, cpuCopy.NegativeFlag, "INS_CLV", "NegativeFlag")) valid = false;

    return valid;
}

int * run_flags(CPU& cpu, Memory& mem){
    static int result[2];

    result[0]++; if(SEC(cpu, mem)) result[1]++;
    result[0]++; if(SED(cpu, mem)) result[1]++;
    result[0]++; if(SEI(cpu, mem)) result[1]++;
    result[0]++; if(CLC(cpu, mem)) result[1]++;
    result[0]++; if(CLD(cpu, mem)) result[1]++;
    result[0]++; if(CLI(cpu, mem)) result[1]++;
    result[0]++; if(CLV(cpu, mem)) result[1]++;

    return result;
}