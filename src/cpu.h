#include <cstdint>
#include "memory.h"

typedef uint8_t byte;
typedef uint16_t word;

class CPU{
    // Everything is public for testing purpose
    public:
        // Reset
        void reset(Memory& mem);
        void step_run(Memory& mem);       

        // Processor Registers
        word ProgramCounter;
        byte StackPointer;
        byte Accumulator;
        byte registerX;
        byte registerY;
        
        // Processor Status
        bool CarryFlag;
        bool ZeroFlag;
        bool InterruptDisable;
        bool DecimalMode;
        bool BreakCommand;
        bool OverflowFlag;
        bool NegativeFlag;

        // Functions
        byte fetch_byte(const Memory& mem);
        word fetch_word(const Memory& mem);
        void set_zero_and_negative_flag(byte value);
        void execute_operation(Memory &mem, byte OpCode);

        void load_register_with_next_byte(const Memory& mem, byte& cpuRegister);
        void load_register_with_byte_from_addr(const Memory& mem, byte& cpuRegister, word addr);

        word addressing_mode_indexed_indirect(const Memory& mem, byte addr);
        word addressing_mode_indirect_indexed(const Memory& mem, byte addr);

        // Operation Codes
        static constexpr byte
            // LDA
            INS_LDA_IM = 0xA9,
            INS_LDA_ZP = 0xA5,
            INS_LDA_ZPX = 0xB5,
            INS_LDA_ABS = 0xAD,
            INS_LDA_ABSX = 0xBD,
            INS_LDA_ABSY = 0xB9,
            INS_LDA_INDX = 0xA1,
            INS_LDA_INDY = 0xB1,

            // LDX
            INS_LDX_IM = 0xA2,
            INS_LDX_ZP = 0xA6,
            INS_LDX_ZPY = 0xB6,
            INS_LDX_ABS = 0xAE,
            INS_LDX_ABSY = 0xBE,

            // LDY
            INS_LDY_IM = 0xA0,
            INS_LDY_ZP = 0xA4,
            INS_LDY_ZPX = 0xB4,
            INS_LDY_ABS = 0xAC,
            INS_LDY_ABSX = 0xBC,

            // NOP
            INS_NOP = 0xEA;

};