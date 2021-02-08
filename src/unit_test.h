#include <iostream>
#include <string>
#include "cpu.h"
#include "memory.h"

using namespace std;

void reset_and_prepare_memory(Memory& mem);
void run_all_test(CPU& cpu, Memory& mem);

// NOP
bool NOP(CPU& cpu, Memory& mem);
bool BRK(CPU& cpu, Memory& mem);

// Expected
bool expected_eq(bool value, bool expected, string instruction, string thing);
bool expected_eq(byte value, byte expected, string instruction, string thing);
bool expected_eq(word value, word expected, string instruction, string thing);
bool no_flags_affected(CPU& cpu, CPU& copy, string instruction);
bool only_C_and_Z_flags_affected(CPU& cpu, CPU& copy, string instruction);