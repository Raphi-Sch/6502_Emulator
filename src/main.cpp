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

    run_all_test(cpu, mem);

    return 0;
}