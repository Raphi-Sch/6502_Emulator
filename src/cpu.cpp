#include "cpu.h"

using namespace std;

void CPU::execute_operation(Memory &mem, byte OpCode){
    switch(OpCode){
        case INS_LDA_IM:
            load_register(mem, Accumulator);
            break;

        case INS_LDA_ZP:{
            byte addr = fetch_byte(mem);
            load_register_zero_page(mem, Accumulator, addr, 0x00);
        } break;

        case INS_LDA_ZPX:

            break;

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

void CPU::set_zero_and_negative_flag(byte value){
    ZeroFlag = !value;
    NegativeFlag = (value & (1 << 7));
}

void CPU::load_register(const Memory& mem, byte& CpuRegister){
    CpuRegister = fetch_byte(mem);
    set_zero_and_negative_flag(CpuRegister);
}

void CPU::load_register_zero_page(const Memory& mem, byte& CpuRegister, byte addr, byte offset){
    byte calculated_addr = addr + offset;
    CpuRegister = mem.read(calculated_addr);
    set_zero_and_negative_flag(CpuRegister);
}
