#include <iostream>

#ifndef CPU_H
    #define CPU_H
    #include "cpu.h"
#endif

#include "unit_test.h"

using namespace std;

int main() {
    CPU cpu;
    Memory mem;

    mem.clear();
    

    cpu.reset(mem);

    run_all_test(cpu, mem);

    return 0;
}