#include "cpu.h"

using namespace std;

void CPU::execute_operation(Memory &mem, byte OpCode){
    switch(OpCode){
        // LDA
        case INS_LDA_IM:{
            // Load the next byte directly into the Accummulator
            load_register_with_next_byte(mem, Accumulator);
            break;
        }

        case INS_LDA_ZP:{
            // Load data from Addr in ZeroPage <=> top 8 bits of the addr is always 0x00
            word addr = fetch_byte(mem) & 0x00FF; 
            load_register_with_byte_from_addr(mem, Accumulator, addr);;
        } break;

        case INS_LDA_ZPX:{
            // Load data from Addr in ZeroPage offset by registerX
            word addr = (fetch_byte(mem) + registerX) & 0x00FF; 
            load_register_with_byte_from_addr(mem, Accumulator, addr);
        } break;

        case INS_LDA_ABS:{
            // Load data from anywhere in memory, absolute addressing
            word addr = fetch_word(mem);
            load_register_with_byte_from_addr(mem, Accumulator, addr);
        } break;

        case INS_LDA_ABSX:{
            // Load data from anywhere in memory, absolute addressing offset by registerX
            word addr = fetch_word(mem) + registerX;
            load_register_with_byte_from_addr(mem, Accumulator, addr);
        } break;

        case INS_LDA_ABSY:{
            // Load data from anywhere in memory, absolute addressing offset by registerY
            word addr = fetch_word(mem) + registerY;
            load_register_with_byte_from_addr(mem, Accumulator, addr);
        } break;

        case INS_LDA_INDX:{
            byte addrFromIns = fetch_byte(mem);
            word addr = addressing_mode_indexed_indirect(mem, addrFromIns);
            load_register_with_byte_from_addr(mem, Accumulator, addr);
        } break;

        case INS_LDA_INDY:{
            byte addrFromIns = fetch_byte(mem);
            word addr = addressing_mode_indirect_indexed(mem, addrFromIns);
            load_register_with_byte_from_addr(mem, Accumulator, addr);
        } break;

        // LDX
        case INS_LDX_IM:{
            load_register_with_next_byte(mem, registerX);
            break;
        }

        case INS_LDX_ZP:{
            word addr = fetch_byte(mem) & 0x00FF; 
            load_register_with_byte_from_addr(mem, registerX, addr);;
        } break;

        case INS_LDX_ZPY:{
            word addr = (fetch_byte(mem) + registerY) & 0x00FF; 
            load_register_with_byte_from_addr(mem, registerX, addr);
        } break;

        case INS_LDX_ABS:{
            word addr = fetch_word(mem);
            load_register_with_byte_from_addr(mem, registerX, addr);
        } break;

        case INS_LDX_ABSY:{
            word addr = fetch_word(mem) + registerY;
            load_register_with_byte_from_addr(mem, registerX, addr);
        } break;

        // LDY
        case INS_LDY_IM:{
            load_register_with_next_byte(mem, registerY);
            break;
        }

        case INS_LDY_ZP:{
            word addr = fetch_byte(mem) & 0x00FF; 
            load_register_with_byte_from_addr(mem, registerY, addr);;
        } break;

        case INS_LDY_ZPX:{
            word addr = (fetch_byte(mem) + registerY) & 0x00FF; 
            load_register_with_byte_from_addr(mem, registerY, addr);
        } break;

        case INS_LDY_ABS:{
            word addr = fetch_word(mem);
            load_register_with_byte_from_addr(mem, registerY, addr);
        } break;

        case INS_LDY_ABSX:{
            word addr = fetch_word(mem) + registerX;
            load_register_with_byte_from_addr(mem, registerY, addr);
        } break;

        // NOP
        case INS_NOP:
            break;

        // PUSH-PULL
        case INS_PHA:
            mem.write(StackPointer, Accumulator);
            StackPointer--;
            break;

        case INS_PLA:
            Accumulator = mem.read(StackPointer);
            StackPointer++;
            break;     

        case INS_PHP:
            mem.write(StackPointer, CarryFlag & (ZeroFlag << 1) & (InterruptDisable << 2) & (DecimalMode << 3) & (BreakCommand << 4) & (OverflowFlag << 6) & (NegativeFlag << 7));
            StackPointer--;
            break;
        
        case INS_PLP:
            byte flags = mem.read(StackPointer);
            CarryFlag = flags & 0x1;
            ZeroFlag = (flags >> 1) & 0x1;
            InterruptDisable = (flags >> 2) & 0x1;
            DecimalMode = (flags >> 3) & 0x1;
            BreakCommand = (flags >> 4) & 0x1;
            OverflowFlag = (flags >> 6) & 0x1;
            NegativeFlag = (flags >> 7) & 0x1;
            StackPointer++;
            break;

        default:
            cout << "CPU : Operation code not handle" << endl;
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

word CPU::addressing_mode_indexed_indirect(const Memory& mem, byte addr){
    // 6502 is little endian
    byte addrFromMemLeast = mem.read((registerX + addr) & 0xFF);
    byte addrFromMemMost  = mem.read((registerX + addr + 0x01) & 0xFF);
    return (addrFromMemLeast | (addrFromMemMost << 8));
}

word CPU::addressing_mode_indirect_indexed(const Memory& mem, byte addr){
    byte addrFromMemLeast = mem.read(addr);
    byte addrFromMemMost  = mem.read((addr + 0x01) & 0xFF);
    return (addrFromMemLeast | (addrFromMemMost << 8)) + registerY;
}