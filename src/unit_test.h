#include <iostream>
#include <string>

#ifndef CPU_H
#define CPU_H
#include "cpu.h"
#endif

using namespace std;

void reset(Memory& mem);
void run_all_test(CPU& cpu, Memory& mem);

// Jump
bool jump(CPU& cpu, Memory& mem, byte instruction);

// Sub routine
bool jsr(CPU& cpu, Memory& mem);
bool rts(CPU& cpu, Memory& mem);

// NOP
bool NOP(CPU& cpu, Memory& mem);

// Expected
bool expected_eq(bool value, bool expected, string instruction, string thing);
bool expected_eq(byte value, byte expected, string instruction, string thing);
bool expected_eq(word value, word expected, string instruction, string thing);
bool no_flags_affected(CPU& cpu, CPU& copy, string instruction);
bool only_C_and_Z_flags_affected(CPU& cpu, CPU& copy, string instruction);