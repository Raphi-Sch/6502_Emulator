#include <iostream>
#include "cpu.h"

using namespace std;

int main() {
    CPU cpu;
    Memory mem;

    mem.clear();

    // Setting start of prgm in the reset vector
    mem.write(0xfffc, 0x00);
    mem.write(0xfffd, 0x02);

    cpu.reset(mem);


    // Test PRGM
    cout << "Prgm Counter : 0x" << hex << setfill('0') << setw(4)<< cpu.get_program_counter() << endl;

    cpu.increment_program_counter();

    cout << "Prgm Counter : 0x" << hex << setfill('0') << setw(4)<< cpu.get_program_counter() << endl;

    
    return 0;
}