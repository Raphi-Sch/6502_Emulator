#include "cpu.h"

// Reset
void CPU::reset(Memory &mem){
    ProgramCounter = mem.read(0xfffc) | (mem.read(0xfffd) << 8);
}

void CPU::execute(Memory &mem, byte OpCode){

};