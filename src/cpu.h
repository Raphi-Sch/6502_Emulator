#include <cstdint>
#include "memory.h"

typedef uint8_t byte;
typedef uint16_t word;

class CPU{
    public:
        // Reset
        void reset(Memory &mem);
        void execute(Memory &mem, byte OpCode);

    private:
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
};