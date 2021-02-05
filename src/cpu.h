#include <cstdint>
#include "memory.h"

// Reference : http://www.obelisk.me.uk/6502/ http://www.emulator101.com/6502-addressing-modes.html

typedef uint8_t byte;
typedef uint16_t word;

class CPU{
    // Register are public for testing purpose
    public:
        // CPU Functions
        void reset(Memory& mem);
        void step_run(Memory& mem);
        void execute_operation(Memory &mem, byte OpCode);     

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

        // Operation Codes
        static constexpr byte
            // ADC
            INS_ADC_IM   = 0x69,
            INS_ADC_ZP   = 0x65,
            INS_ADC_ZPX  = 0x75,
            INS_ADC_ABS  = 0x6D,
            INS_ADC_ABSX = 0x7D,
            INS_ADC_ABSY = 0x79,
            INS_ADC_INDX = 0x61,
            INS_ADC_INDY = 0x71,

            // AND
            INS_AND_IM   = 0x29,
            INS_AND_ZP   = 0x25,
            INS_AND_ZPX  = 0x35,
            INS_AND_ABS  = 0x2D,
            INS_AND_ABSX = 0x3D,
            INS_AND_ABSY = 0x39,
            INS_AND_INDX = 0x21,
            INS_AND_INDY = 0x31,

            // ASL
            INS_ASL_ACC  = 0x0A,
            INS_ASL_ZP   = 0x06,
            INS_ASL_ZPX  = 0x16,
            INS_ASL_ABS  = 0x0E,
            INS_ASL_ABSX = 0x1E,

            // BCC
            INS_BCC = 0x90,

            // BCS
            INS_BCS = 0xB0,

            // BEQ
            INS_BEQ = 0xF0,

            // BIT
            INS_BIT_ZP  = 0x24,
            INS_BIT_ABS = 0x2C,

            // BMI
            INS_BMI = 0x30,

            // BNE
            INS_BNE = 0xD0,

            // BPL
            INS_BPL = 0x10,

            // BRK
            INS_BRK = 0x00,

            // BVC
            INS_BVC = 0x50,

            // BVS
            INS_BVS = 0x70,

            // CLC
            INS_CLC = 0x18,

            // CLD
            INS_CLD = 0xD8,

            // CLI
            INS_CLI = 0x58,

            // CLV
            INS_CLV = 0xB8,

            // CMP
            INS_CMP_IM   = 0xC9,
            INS_CMP_ZP   = 0xC5,
            INS_CMP_ZPX  = 0xD5,
            INS_CMP_ABS  = 0xCD,
            INS_CMP_ABSX = 0xDD,
            INS_CMP_ABSY = 0xD9,
            INS_CMP_INDX = 0xC1,
            INS_CMP_INDY = 0xD1,

            // CPX
            INS_CPX_IM  = 0xE0,
            INS_CPX_ZP  = 0xE4,
            INS_CPX_ABS = 0xEC,

            // CPY
            INS_CPY_IM  = 0xC0,
            INS_CPY_ZP  = 0xC4,
            INS_CPY_ABS = 0xCC,

            // DEC
            INS_DEC_ZP   = 0xC6,
            INS_DEC_ZPX  = 0xD6,
            INS_DEC_ABS  = 0xCE,
            INS_DEC_ABSX = 0xDE,

            // DEX
            INS_DEX = 0xCA,

            // DEY
            INS_DEY = 0x88,

            // EOR
            INS_EOR_IM   = 0x49,
            INS_EOR_ZP   = 0x45,
            INS_EOR_ZPX  = 0x55,
            INS_EOR_ABS  = 0x4D,
            INS_EOR_ABSX = 0x5D,
            INS_EOR_ABSY = 0x59,
            INS_EOR_INDX = 0x41,
            INS_EOR_INDY = 0x51,

            // INC
            INS_INC_ZP   = 0xE6,
            INS_INC_ZPX  = 0xF6,
            INS_INC_ABS  = 0xEE,
            INS_INC_ABSX = 0xFE,

            // INX
            INS_INX = 0xE8,

            // INY
            INS_INY = 0xC8,

            // JMP
            INS_JMP_ABS = 0x4C,
            INS_JMP_IND = 0x6C,

            // JSR
            INS_JSR = 0x20,

            // LDA
            INS_LDA_IM   = 0xA9,
            INS_LDA_ZP   = 0xA5,
            INS_LDA_ZPX  = 0xB5,
            INS_LDA_ABS  = 0xAD,
            INS_LDA_ABSX = 0xBD,
            INS_LDA_ABSY = 0xB9,
            INS_LDA_INDX = 0xA1,
            INS_LDA_INDY = 0xB1,

            // LDX
            INS_LDX_IM   = 0xA2,
            INS_LDX_ZP   = 0xA6,
            INS_LDX_ZPY  = 0xB6,
            INS_LDX_ABS  = 0xAE,
            INS_LDX_ABSY = 0xBE,

            // LDY
            INS_LDY_IM   = 0xA0,
            INS_LDY_ZP   = 0xA4,
            INS_LDY_ZPX  = 0xB4,
            INS_LDY_ABS  = 0xAC,
            INS_LDY_ABSX = 0xBC,

            // LSR
            INS_LSR_ACC  = 0x4A,
            INS_LSR_ZP   = 0x46,
            INS_LSR_ZPX  = 0x56,
            INS_LSR_ABS  = 0x4E,
            INS_LSR_ABSX = 0x5E,

            // NOP
            INS_NOP = 0xEA,

            // ORA
            INS_ORA_IM   = 0x09,
            INS_ORA_ZP   = 0x05,
            INS_ORA_ZPX  = 0x15,
            INS_ORA_ABS  = 0x0D,
            INS_ORA_ABSX = 0x1D,
            INS_ORA_ABSY = 0x19,
            INS_ORA_INDX = 0x01,
            INS_ORA_INDY = 0x11,

            // PHA
            INS_PHA = 0x48,

            // PHP
            INS_PHP = 0x08,

            // PLA
            INS_PLA = 0x68,

            // PLP
            INS_PLP = 0x28,

            // ROL
            INS_ROL_ACC  = 0x2A,
            INS_ROL_ZP   = 0x26,
            INS_ROL_ZPX  = 0x36,
            INS_ROL_ABS  = 0x2E,
            INS_ROL_ABSX = 0x3E,

            // ROR
            INS_ROR_ACC  = 0x6A,
            INS_ROR_ZP   = 0x66,
            INS_ROR_ZPX  = 0x76,
            INS_ROR_ABS  = 0x6E,
            INS_ROR_ABSX = 0x7E,

            // RTI
            INS_RTI = 0x40,

            // RTS
            INS_RTS = 0x60,

            // SBC
            INS_SBC_IM   = 0xE9,
            INS_SBC_ZP   = 0xE5,
            INS_SBC_ZPX  = 0xF5,
            INS_SBC_ABS  = 0xED,
            INS_SBC_ABSX = 0xFD,
            INS_SBC_ABSY = 0xF9,
            INS_SBC_INDX = 0xE1,
            INS_SBC_INDY = 0xF1,

            // SEC
            INS_SEC = 0x38,

            // SED
            INS_SED = 0xF8,

            // SEI
            INS_SEI = 0x78,

            // STA
            INS_STA_ZP   = 0x85,
            INS_STA_ZPX  = 0x95,
            INS_STA_ABS  = 0x8D,
            INS_STA_ABSX = 0x9D,
            INS_STA_ABSY = 0x99,
            INS_STA_INDX = 0x81,
            INS_STA_INDY = 0x91,

            // STX
            INS_STX_ZP  = 0x86,
            INS_STX_ZPY = 0x96,
            INS_STX_ABS = 0x8E,

            // STY
            INS_STY_ZP  = 0x84, 
            INS_STY_ZPX = 0x94,
            INS_STY_ABS = 0x8C,

            // TAX
            INS_TAX = 0xAA,
            
            // TAY
            INS_TAY = 0xA8,

            // TSX
            INS_TSX = 0xBA,

            // TXA
            INS_TXA = 0x8A,

            // TXS
            INS_TXS = 0x9A,

            // TYA
            INS_TYA = 0x98;

    private:
        // Fetch byte/word from memory space
        byte fetch_byte(const Memory& mem);
        word fetch_word(const Memory& mem);

        // Load register
        void load_register(const Memory& mem, byte& cpuRegister, word addr);
        void load_register_set_zero_and_negative_flag(byte value);

        // Addressing modes
        inline word addressing_mode_immediate();
        inline word addressing_mode_zero_page(const Memory&);
        inline word addressing_mode_zero_page_X(const Memory&);
        inline word addressing_mode_zero_page_Y(const Memory&);
        inline word addressing_mode_relative(const Memory&);
        inline word addressing_mode_absolute(const Memory&);
        inline word addressing_mode_absolute_X(const Memory&);
        inline word addressing_mode_absolute_Y(const Memory&);
        inline word addressing_mode_indexed_indirect(const Memory&);
        inline word addressing_mode_indirect_indexed(const Memory&);
};