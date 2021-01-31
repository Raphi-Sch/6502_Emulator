#include "memory.h"

using namespace std;

byte Memory::read(word addr){
    return mem[addr];
}

void Memory::write(word addr, byte value){
    mem[addr] = value;
}

void Memory::clear(){
    for (word i = 0; i < 0xffff; i++){
        mem[i] = 0x00;
    }
}

void Memory::print(word start, word end){
    cout << "START MEMORY PRINT ------------------------------------" << endl;
    cout << "Offset\t00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F" << endl;
    
    for(word i = start; i <= end; i += 0x0010){
        cout << "0x" << setfill('0') << setw(4) << hex << (int)i << dec << "\t" ;

        for(word j = 0; j <= 0xf; j++){
            word addr = i | j;
            cout << hex << setw(2) << (int)mem[addr] << " ";
        }   

        cout << endl;
    }

    cout << "END MEMORY PRINT --------------------------------------" << endl;
}