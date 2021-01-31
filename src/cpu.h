#include <cstdint>
#include "memory.h"

typedef uint8_t byte;
typedef uint16_t word;

class CPU{
    public:
        void reset(Memory &mem);

        // Program Counter
        word get_program_counter();
        void set_program_counter(word addr);
        void increment_program_counter();

        // Stack Pointer
        byte get_stack_pointer();
        void increment_stack_pointer();
        void decrement_stack_pointer();

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