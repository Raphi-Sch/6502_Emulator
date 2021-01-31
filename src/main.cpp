#include <iostream>
//#include "cpu.h"
#include "unit_test.h"

using namespace std;

int main() {
    CPU cpu;
    Memory mem;

    mem.clear();
    
    // Setting start of prgm in the reset vector
    mem.write(0xfffc, 0x00);
    mem.write(0xfffd, 0x02);
    cpu.reset(mem);

    run_all_test(cpu, mem);

    return 0;
}