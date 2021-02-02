#include <iostream>
#include <string>
#include "cpu.h"

using namespace std;

void run_all_test(CPU& cpu, Memory& mem);


// Load register test
bool load_register_immediate(CPU& cpu, Memory& mem, byte instruction);
bool load_register_zero_page(CPU& cpu, Memory& mem, byte instruction);
bool load_register_zero_page_X(CPU& cpu, Memory& mem, byte instruction);
bool load_register_zero_page_Y(CPU& cpu, Memory& mem, byte instruction);
bool load_register_absolute(CPU& cpu, Memory& mem, byte instruction);
bool load_register_absolute_X(CPU& cpu, Memory& mem, byte instruction);
bool load_register_absolute_Y(CPU& cpu, Memory& mem, byte instruction);

// LDA specific
bool LDA_INDX(CPU& cpu, Memory& mem);
bool LDA_INDY(CPU& cpu, Memory& mem);

// Store register test
bool store_register_zero_page(CPU& cpu, Memory& mem, byte instruction);
bool store_register_zero_page_X(CPU& cpu, Memory& mem, byte instruction);
bool store_register_zero_page_Y(CPU& cpu, Memory& mem, byte instruction);
bool store_register_absolute(CPU& cpu, Memory& mem, byte instruction);
bool store_register_absolute_X(CPU& cpu, Memory& mem, byte instruction);
bool store_register_absolute_Y(CPU& cpu, Memory& mem, byte instruction);

// STA Specific
bool STA_ABSX(CPU& cpu, Memory& mem);
bool STA_ABSY(CPU& cpu, Memory& mem);
bool STA_INDX(CPU& cpu, Memory& mem);
bool STA_INDY(CPU& cpu, Memory& mem);

// NOP
bool nop(CPU& cpu, Memory& mem);

// Expected
bool load_register_not_changing_unexpected_flags(CPU& cpu, CPU& copy, string instruction);
bool expected_eq(bool value, bool expected, string instruction, string thing);
bool expected_eq(byte value, byte expected, string instruction, string thing);
bool expected_eq(word value, word expected, string instruction, string thing);
bool no_flags_affected(CPU& cpu, CPU& copy, string instruction);