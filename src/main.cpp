#include <iostream>
#include "cpu.h"
#include "memory.h"
#include "unit_test.h"

using namespace std;

int main() {
    CPU cpu;
    Memory mem;

    mem.clear();
    cpu.reset(mem);

    // Testing if all instruction are working, CPU is halted if not
    if(!run_all_test(cpu, mem)) { return 1;}

    return 0;
}