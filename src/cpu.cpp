#include "cpu.h"

using namespace std;

void CPU::execute_operation(Memory &mem, byte OpCode){
    switch(OpCode){
        // ACD
        case INS_ADC_IM: {
            byte data = fetch_byte(mem);
            word tmp = Accumulator + data + CarryFlag;
            CarryFlag = tmp > 0xFF;
            Accumulator = tmp & 0xFF;
            set_zero_and_negative_flag(Accumulator);
        } break;

        case INS_ADC_ZP: add_with_carry(mem, addressing_mode_zero_page(mem)); break;
        case INS_ADC_ZPX: add_with_carry(mem, addressing_mode_zero_page_X(mem)); break;
        case INS_ADC_ABS: add_with_carry(mem, addressing_mode_absolute(mem)); break;
        case INS_ADC_ABSX: add_with_carry(mem, addressing_mode_absolute_X(mem)); break;
        case INS_ADC_ABSY: add_with_carry(mem, addressing_mode_absolute_Y(mem)); break;
        case INS_ADC_INDX: add_with_carry(mem, addressing_mode_indexed_indirect(mem)); break;
        case INS_ADC_INDY: add_with_carry(mem, addressing_mode_indirect_indexed(mem)); break;

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
        case INS_BCC: if(!CarryFlag) relative_displacement(mem); break;

        // BCS
        case INS_BCS: if(CarryFlag) relative_displacement(mem); break;

        // BEQ
        case INS_BEQ: if(ZeroFlag) relative_displacement(mem); break;

        // BIT
        case INS_BIT_ZP: bit_test(mem, addressing_mode_zero_page(mem)); break;
        case INS_BIT_ABS: bit_test(mem, addressing_mode_absolute(mem)); break;

        // BMI
        case INS_BMI: if(NegativeFlag) relative_displacement(mem); break;

        // BNE
        case INS_BNE: if(!ZeroFlag) relative_displacement(mem); break;

        // BPL
        case INS_BPL: if(!NegativeFlag) relative_displacement(mem); break;

        // BRK
        case INS_BRK: {
            stack_push(mem, ProgramCounter);
            stack_push(mem, flags_save());
            ProgramCounter = fetch_word(mem);
            BreakCommand = 1;
        } break;

        // BVC
        case INS_BVC: if(!OverflowFlag) relative_displacement(mem); break;

        // BVS
        case INS_BVS: if(OverflowFlag) relative_displacement(mem); break;

        // CLC
        case INS_CLC: CarryFlag = 0; break;

        // CLD
        case INS_CLD: DecimalMode = 0; break;

        // CLI
        case INS_CLI: InterruptDisable = 0; break;

        // CLV
        case INS_CLV: OverflowFlag = 0; break;

        // DEX
        case INS_DEX: registerX--; break;

        // DEY
        case INS_DEY: registerY--; break;

        // INX
        case INS_INX: registerX++; break;

        // INY
        case INS_INY: registerY++; break;

        // JSR
        case INS_JSR: {
            stack_push(mem, ProgramCounter & 0xFF);
            stack_push(mem, ProgramCounter & 0xFF00);
            ProgramCounter = fetch_word(mem);
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

        // NOP
        case INS_NOP: break;

        // PHA
        case INS_PHA: stack_push(mem, Accumulator); break;

        // PLA
        case INS_PLA:{
            Accumulator = stack_pull(mem);
            set_zero_and_negative_flag(Accumulator);
        } break;     

        // PHP
        case INS_PHP: stack_push(mem, flags_save()); break;
        
        // PLP
        case INS_PLP: flags_restore(stack_pull(mem)); break;

        // RTI
        case INS_RTI: {
            flags_restore(stack_pull(mem));
            ProgramCounter = stack_pull(mem);
        } break;

        // RTS
        case INS_RTS: ProgramCounter = (stack_pull(mem) + (stack_pull(mem) << 8)) - 1; break;

        // SEC
        case INS_SEC: CarryFlag = 1; break;

        // SED
        case INS_SED: DecimalMode = 1; break;

        // SEI
        case INS_SEI: InterruptDisable = 1; break;

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

        // TAX
        case INS_TAX: {
            registerX = Accumulator;
            set_zero_and_negative_flag(registerX);
        } break;

        // TAY
        case INS_TAY: {
            registerY = Accumulator;
            set_zero_and_negative_flag(registerY);
        }

        // TSX
        case INS_TSX: {
            registerX = StackPointer;
            set_zero_and_negative_flag(registerX);
        } break;

        // TXA
        case INS_TXA: {
            Accumulator = registerX;
            set_zero_and_negative_flag(Accumulator);
        } break;

        // TXS
        case INS_TXS: StackPointer = registerX; break;

        // TYA
        case INS_TYA: {
            Accumulator = registerY;
            set_zero_and_negative_flag(Accumulator);
        }

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

void CPU::add_with_carry(Memory& mem, word addr){
    byte data = mem.read(addr);
    word tmp = Accumulator + data + CarryFlag;
    CarryFlag = tmp > 0xFF;
    mem.write(addr, tmp);
}

void CPU::bit_test(Memory& mem, word addr){
    byte tmp = Accumulator & mem.read(addr);
    ZeroFlag = !tmp;
    OverflowFlag = (tmp >> 6) & 0x1;
    NegativeFlag = (tmp >> 7) & 0x1;
}

void CPU::relative_displacement(const Memory& mem){
    byte offset = fetch_byte(mem);
    ((offset & 0x80) >> 7) ? ProgramCounter -= offset : ProgramCounter += offset;
}

// Stack
void CPU::stack_push(Memory& mem, byte data){
    mem.write(0x0100 + StackPointer, data);
    StackPointer--;
}

byte CPU::stack_pull(Memory& mem){
    StackPointer++;
    return mem.read(StackPointer);
}

// Flags
byte CPU::flags_save(){
    return CarryFlag | (ZeroFlag << 1) | (InterruptDisable << 2) | (DecimalMode << 3) | (BreakCommand << 4) | (OverflowFlag << 6) | (NegativeFlag << 7);
}

void CPU::flags_restore(byte flags){
    CarryFlag = flags & 0x1;
    ZeroFlag = (flags >> 1) & 0x1;
    InterruptDisable = (flags >> 2) & 0x1;
    DecimalMode = (flags >> 3) & 0x1;
    BreakCommand = (flags >> 4) & 0x1;
    OverflowFlag = (flags >> 6) & 0x1;
    NegativeFlag = (flags >> 7) & 0x1;
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