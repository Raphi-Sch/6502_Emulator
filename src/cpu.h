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
        void set_zero_and_negative_flag(byte value);
        void execute_operation(Memory &mem, byte OpCode);

        // Operation Codes
        static constexpr byte
            INS_LDA_IM = 0xA9;
};