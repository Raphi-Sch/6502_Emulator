#include <iostream>
#include <string>
#include "cpu.h"

using namespace std;

void run_all_test(CPU& cpu, Memory& mem);

bool LDA_IM(CPU& cpu, Memory& mem);
bool LDA_ZP(CPU& cpu, Memory& mem);
bool LDA_ZPX(CPU& cpu, Memory& mem);
bool LDA_ABS(CPU& cpu, Memory& mem);
bool LDA_ABSX(CPU& cpu, Memory& mem);
bool LDA_ABSY(CPU& cpu, Memory& mem);
bool LDA_INDX(CPU& cpu, Memory& mem);
bool LDA_INDY(CPU& cpu, Memory& mem);

bool load_register_not_changing_unexpected_flags(CPU& cpu, CPU& copy, string instruction);

bool expected_eq(bool value, bool expected, string instruction, string thing);
bool expected_eq(byte value, byte expected, string instruction, string thing);