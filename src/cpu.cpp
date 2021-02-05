#include "cpu.h"

using namespace std;

void CPU::execute_operation(Memory &mem, byte OpCode){
    switch(OpCode){
        // AND
        case INS_AND_IM: Accumulator = Accumulator & mem.read(addressing_mode_immediate()); break;
        case INS_AND_ZP: Accumulator = Accumulator & mem.read(addressing_mode_zero_page(mem)); break;
        case INS_AND_ZPX: Accumulator = Accumulator & mem.read(addressing_mode_zero_page_X(mem)); break;
        case INS_AND_ABS: Accumulator = Accumulator & mem.read(addressing_mode_absolute(mem)); break;
        case INS_AND_ABSX: Accumulator = Accumulator & mem.read(addressing_mode_absolute_X(mem)); break;
        case INS_AND_ABSY: Accumulator = Accumulator & mem.read(addressing_mode_absolute_Y(mem)); break;
        case INS_AND_INDX: Accumulator = Accumulator & mem.read(addressing_mode_indexed_indirect(mem)); break;
        case INS_AND_INDY: Accumulator = Accumulator & mem.read(addressing_mode_indirect_indexed(mem)); break;

        // ASL
        case INS_ASL_ACC:{
            CarryFlag = (Accumulator & 0x80) >> 7;
            Accumulator = Accumulator << 1;
            set_zero_and_negative_flag(Accumulator);
        } break;

        case INS_ASL_ZP: arithmetic_shift_left(mem, addressing_mode_zero_page(mem)); break;
        case INS_ASL_ZPX: arithmetic_shift_left(mem, addressing_mode_zero_page_X(mem)); break;
        case INS_ASL_ABS: arithmetic_shift_left(mem, addressing_mode_absolute(mem)); break;
        case INS_ASL_ABSX: arithmetic_shift_left(mem, addressing_mode_absolute_X(mem)); break;

        // BCC
        case INS_BCC: {
            if(!CarryFlag){
                byte offset = fetch_byte(mem);
                ((offset & 0x80) >> 7) ? ProgramCounter -= offset : ProgramCounter += offset;
            }
        } break;

        // BCS
        case INS_BCS: {
            if(CarryFlag){
                byte offset = fetch_byte(mem);
                ((offset & 0x80) >> 7) ? ProgramCounter -= offset : ProgramCounter += offset;
            }
        } break;

        // BEQ
        case INS_BEQ: {
            if(ZeroFlag){
                byte offset = fetch_byte(mem);
                ((offset & 0x80) >> 7) ? ProgramCounter -= offset : ProgramCounter += offset;
            }
        } break;

        // LDA
        case INS_LDA_IM: load_register(mem, Accumulator, addressing_mode_immediate()); break;
        case INS_LDA_ZP: load_register(mem, Accumulator, addressing_mode_zero_page(mem)); break;
        case INS_LDA_ZPX: load_register(mem, Accumulator, addressing_mode_zero_page_X(mem)); break;
        case INS_LDA_ABS: load_register(mem, Accumulator, addressing_mode_absolute(mem)); break;
        case INS_LDA_ABSX: load_register(mem, Accumulator, addressing_mode_absolute_X(mem)); break;
        case INS_LDA_ABSY: load_register(mem, Accumulator, addressing_mode_absolute_Y(mem)); break;
        case INS_LDA_INDX: load_register(mem, Accumulator, addressing_mode_indexed_indirect(mem)); break;
        case INS_LDA_INDY: load_register(mem, Accumulator, addressing_mode_indirect_indexed(mem)); break;

        // LDX
        case INS_LDX_IM: load_register(mem, registerX, addressing_mode_immediate()); break;
        case INS_LDX_ZP: load_register(mem, registerX, addressing_mode_zero_page(mem)); break;
        case INS_LDX_ZPY: load_register(mem, registerX, addressing_mode_zero_page_Y(mem)); break;
        case INS_LDX_ABS: load_register(mem, registerX, addressing_mode_absolute(mem)); break;
        case INS_LDX_ABSY: load_register(mem, registerX, addressing_mode_absolute_Y(mem)); break;

        // LDY
        case INS_LDY_IM: load_register(mem, registerY, addressing_mode_immediate()); break;
        case INS_LDY_ZP: load_register(mem, registerY, addressing_mode_zero_page(mem)); break;
        case INS_LDY_ZPX: load_register(mem, registerY, addressing_mode_zero_page_X(mem)); break;
        case INS_LDY_ABS: load_register(mem, registerY, addressing_mode_absolute(mem)); break;
        case INS_LDY_ABSX: load_register(mem, registerY, addressing_mode_absolute_X(mem)); break;

        // STA
        case INS_STA_ZP: mem.write(addressing_mode_zero_page(mem), Accumulator); break;
        case INS_STA_ZPX: mem.write(addressing_mode_zero_page_X(mem), Accumulator); break;
        case INS_STA_ABS: mem.write(addressing_mode_absolute(mem), Accumulator); break;
        case INS_STA_ABSX: mem.write(addressing_mode_absolute_X(mem), Accumulator); break;
        case INS_STA_ABSY: mem.write(addressing_mode_absolute_Y(mem), Accumulator); break;
        case INS_STA_INDX: mem.write(addressing_mode_indexed_indirect(mem), Accumulator); break;
        case INS_STA_INDY: mem.write(addressing_mode_indirect_indexed(mem), Accumulator); break;

        // STX
        case INS_STX_ZP: mem.write(addressing_mode_zero_page(mem), registerX); break;
        case INS_STX_ZPY: mem.write(addressing_mode_zero_page_Y(mem), registerX); break;
        case INS_STX_ABS: mem.write(addressing_mode_absolute(mem), registerX); break;

        // STY
        case INS_STY_ZP: mem.write(addressing_mode_zero_page(mem), registerY); break;
        case INS_STY_ZPX: mem.write(addressing_mode_zero_page_X(mem), registerY); break;
        case INS_STY_ABS: mem.write(addressing_mode_absolute(mem), registerY); break;

        // NOP
        case INS_NOP: break;

        // Stack Instruction
        case INS_PHA:{
            mem.write(StackPointer, Accumulator);
            StackPointer--;
        } break;

        case INS_PLA:{
            Accumulator = mem.read(StackPointer);
            set_zero_and_negative_flag(Accumulator);
            StackPointer++;
        } break;     

        case INS_PHP:{
            byte flags = CarryFlag | (ZeroFlag << 1) | (InterruptDisable << 2) | (DecimalMode << 3) | (BreakCommand << 4) | (OverflowFlag << 6) | (NegativeFlag << 7);
            mem.write(StackPointer, flags);
            StackPointer--;
        }break;
        
        case INS_PLP:{
            byte flags = mem.read(StackPointer);
            CarryFlag = flags & 0x1;
            ZeroFlag = (flags >> 1) & 0x1;
            InterruptDisable = (flags >> 2) & 0x1;
            DecimalMode = (flags >> 3) & 0x1;
            BreakCommand = (flags >> 4) & 0x1;
            OverflowFlag = (flags >> 6) & 0x1;
            NegativeFlag = (flags >> 7) & 0x1;
            StackPointer++;
        }break;

        default:{
            cout << "CPU : Operation code " << hex << int(OpCode) << " not handle" << endl;
        }break;
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

// Arithmetic
void CPU::arithmetic_shift_left(Memory& mem, word addr){
    byte data = mem.read(addr);
    CarryFlag = (data & 0x80) >> 7;
    data = data << 1;
    mem.write(addr, data);
    NegativeFlag = data & 0x80;
}

// Load Register
void CPU::load_register(const Memory& mem, byte& cpuRegister, word addr){
    cpuRegister = mem.read(addr);
    set_zero_and_negative_flag(cpuRegister);
}

void CPU::set_zero_and_negative_flag(byte value){
    ZeroFlag = !value;
    NegativeFlag = value & 0x80;
}

// Addressing mode
word CPU::addressing_mode_immediate(){
    // Return value of ProgramCounter, then increment it
    return ProgramCounter++;
}

word CPU::addressing_mode_zero_page(const Memory& mem){
    // Get address of memory in ZeroPage (top 8 bits of the addr is always 0x00--)
    return fetch_byte(mem) & 0x00FF; 
}

word CPU::addressing_mode_zero_page_X(const Memory& mem){
    // Get address of memory in ZeroPage offset by registerX, address wrap around at 0xFF
    return (fetch_byte(mem) + registerX) & 0x00FF; 
}

word CPU::addressing_mode_zero_page_Y(const Memory& mem){
    // Get address of memory in ZeroPage offset by registerY, address wrap around at 0xFF
    return (fetch_byte(mem) + registerY) & 0x00FF; 
}

word CPU::addressing_mode_relative(const Memory& mem){

    return 0x00;
}

word CPU::addressing_mode_absolute(const Memory& mem){
    return fetch_word(mem);
}

word CPU::addressing_mode_absolute_X(const Memory& mem){
    return fetch_word(mem) + registerX;
}

word CPU::addressing_mode_absolute_Y(const Memory& mem){
    return fetch_word(mem) + registerY;
}

word CPU::addressing_mode_indexed_indirect(const Memory& mem){
    // 6502 is little endian
    /*byte addrFromMemLeast = mem.read((registerX + addr) & 0xFF);
    byte addrFromMemMost  = mem.read((registerX + addr + 0x01) & 0xFF);
    return (addrFromMemLeast | (addrFromMemMost << 8));*/
    word addr = fetch_byte(mem);
    return (mem.read((registerX + addr + 0x01) & 0xFF) << 8) | mem.read((registerX + addr) & 0xFF);
}

word CPU::addressing_mode_indirect_indexed(const Memory& mem){
    /*byte addrFromMemLeast = mem.read(addr);
    byte addrFromMemMost  = mem.read((addr + 0x01) & 0xFF);
    return (addrFromMemLeast | (addrFromMemMost << 8)) + registerY;*/
    word addr = fetch_byte(mem);
    return (mem.read((addr + 0x01) & 0xFF) << 8) | mem.read(addr) + registerY;
}