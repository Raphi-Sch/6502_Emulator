#include <iostream>
#include "memory.h"

using namespace std;

int main() {
    Memory mem;
    mem.clear();

    mem.write(0x0000, 0xAB);
    mem.write(0x000f, 0xAA);

    mem.print(0x0000, 0x00ff);
    
    
    return 0;
}