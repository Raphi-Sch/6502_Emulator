#include "cpu.h"

void CPU::reset(Memory &mem){
    ProgramCounter = mem.read(0xfffc) | (mem.read(0xfffd) << 8);
}

// Function relative to the Program Counter

word CPU::get_program_counter(){
    return ProgramCounter;
}

void CPU::set_program_counter(word addr){
    ProgramCounter = addr;
}

void CPU::increment_program_counter(){
    ProgramCounter ++;
}

// Function relative to the Stack Pointer

byte CPU::get_stack_pointer(){
    return StackPointer;
}

void CPU::increment_stack_pointer(){
    StackPointer ++;
}
        
void CPU::decrement_stack_pointer(){
    StackPointer --;
}

