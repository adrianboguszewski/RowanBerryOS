#include "../kernel/util.h"
#include "../drivers/screen.h"
#include "../kernel/low_level.h"
#include "debug.h"

// defined in assembly
// void print_registers()

void print_memory(void* start, int bytes)
{    
    unsigned char byte;
    char* result = "0x00 ";
    for(int i = 0; i < bytes; i++) 
    {
        byte = memory_byte(start + i);
        byte_to_hex(byte, result);
        print(result);
    }
}

void print_msg(char* msg)
{
    print(msg);
}
