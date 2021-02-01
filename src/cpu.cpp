#include "cpu.h"

using namespace std;

void CPU::execute_operation(Memory &mem, byte OpCode){
    switch(OpCode){
        case INS_LDA_IM:
            load_register_with_next_byte(mem, Accumulator);
            break;

        case INS_LDA_ZP:{
            // Addr is in ZeroPage aka top byte of the addr is always 0x00
            word addr = fetch_byte(mem) & 0x00FF; 
            load_register_with_byte_from_addr(mem, Accumulator, addr);;
        } break;

        case INS_LDA_ZPX:{
            // Addr is in ZeroPage aka top byte of the addr is always 0x00
            word addr = (fetch_byte(mem) + registerX) & 0x00FF; 
            load_register_with_byte_from_addr(mem, Accumulator, addr);
        } break;

        case INS_LDA_ABS:{
            word addr = fetch_word(mem);
            load_register_with_byte_from_addr(mem, Accumulator, addr);
        } break;

        case INS_LDA_ABSX:{
            word addr = fetch_word(mem) + registerX;
            load_register_with_byte_from_addr(mem, Accumulator, addr);
        } break;

        case INS_LDA_ABSY:{
            word addr = fetch_word(mem) + registerY;
            load_register_with_byte_from_addr(mem, Accumulator, addr);
        } break;

        case INS_LDA_INDX:{
            byte addrFromIns = fetch_byte(mem);
            byte addrFromMemLeast = mem.read((registerX + addrFromIns) & 0xFF);
            byte addrFromMemMost = mem.read((registerX + addrFromIns + 0x01) & 0xFF);
            word addr = addrFromMemLeast | (addrFromMemMost << 8);
            load_register_with_byte_from_addr(mem, Accumulator, addr);
        } break;

        case INS_LDA_INDY:{
            byte addrFromIns = fetch_byte(mem);
            
            
        } break;

        default:
            cout << "Operation code not handle" << endl;
            break;
    }
}

void CPU::step_run(Memory& mem){
    execute_operation(mem, fetch_byte(mem));
}

void CPU::reset(Memory& mem){
    // Register
    // 6502 is little endian
    ProgramCounter = mem.read(0xfffc) | (mem.read(0xfffd) << 8);
    StackPointer = 0xff;
    Accumulator = 0;
    registerX = 0;
    registerY = 0;

    // Flags
    CarryFlag = 0;
    ZeroFlag = 0;;
    InterruptDisable = 0;;
    DecimalMode = 0;;
    BreakCommand = 0;;
    OverflowFlag = 0;;
    NegativeFlag = 0;;
}

byte CPU::fetch_byte(const Memory& mem){
    byte Data = mem.read(ProgramCounter);
    ProgramCounter ++;
    return Data;
}

word CPU::fetch_word(const Memory& mem){
    // 6502 is little endian
    word data = mem.read(ProgramCounter) | (mem.read(ProgramCounter + 1) << 8);
    ProgramCounter += 2;
    return data;
}

void CPU::set_zero_and_negative_flag(byte value){
    ZeroFlag = !value;
    NegativeFlag = (value & (1 << 7));
}

void CPU::load_register_with_next_byte(const Memory& mem, byte& cpuRegister){
    cpuRegister = fetch_byte(mem);
    set_zero_and_negative_flag(cpuRegister);
}

void CPU::load_register_with_byte_from_addr(const Memory& mem, byte& cpuRegister, word addr){
    cpuRegister = mem.read(addr);
    set_zero_and_negative_flag(cpuRegister);
}