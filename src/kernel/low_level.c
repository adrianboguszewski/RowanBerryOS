#include "low_level.h"

// A handy C wrapper function that reads a byte from the specified port
u8int port_byte_in(u16int port) {
    // "=a" (result) means : put AL register in variable RESULT when finished
    // "d" (port) means : load EDX with port
    u8int result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result ;
}

void port_byte_out(u16int port, u8int data) {
    // "a" (data) means : load EAX with data
    // "d" (port) means : load EDX with port
    __asm__("out %%al, %%dx" : : "a" (data) , "d" (port));
}

u16int port_word_in(u16int port) {
    u16int result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result ;
}

void port_word_out(u16int port, u16int data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

u8int memory_byte(void* addr)
{
    u8int result;
    __asm__("movl (%%esi), %%eax" : "=a"(result) : "S"(addr));
    return result;
}

void read_disk(u32int words, u16int reg, void* memory_buf)
{
    __asm__("rep insw"
        : 
        : "c"(words), "d"(reg), "D"(memory_buf));
}

void write_disk(u32int words, u16int reg, void* memory_buf)
{
    __asm__("write: outsw\t\n"
        "dec %%ecx\t\n"
        "jg write"
        : 
        : "c"(words), "d"(reg), "S"(memory_buf)); 
}
