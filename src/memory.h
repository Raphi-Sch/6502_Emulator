#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <iostream>
#include <iomanip>

typedef uint8_t byte;
typedef uint16_t word;

class Memory{
    public:
        byte read(word addr) const;
        void write(word addr, byte value);
        void clear();
        void print(word start, word end);
    
    private:
        byte mem[0xffff];
        
};

#endif