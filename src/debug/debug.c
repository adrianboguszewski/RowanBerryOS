#include "../kernel/util.h"
#include "../drivers/screen.h"
#include "../kernel/low_level.h"
#include "debug.h"

// defined in assembly
// void print_registers()

void print_memory(void* start, u32int bytes)
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

void print_byte(u8int b)
{
    char* result = "0x00 \n";
    byte_to_hex(b, result);
    print(result);
}

void print_word(u16int b)
{
    char* result = "0x0000 \n";
    word_to_hex(b, result);
    print(result);
}

void print_dword(u32int b)
{
    char* result = "0x00000000 \n";
    dword_to_hex(b, result);
    print(result);
}

void print_db()
{
    print("I reached");
}