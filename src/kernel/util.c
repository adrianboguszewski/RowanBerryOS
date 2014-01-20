#include "../const/types.h"
#include "util.h"

void memory_copy(void* source, void* dest, u32int no_bytes) 
{
    for(int i=0; i<no_bytes; i++) 
        *((u8int*)(dest+i)) = *((u8int*)(source+i));
}

void memset(void *dest, s8int val, u32int len)
{
    u8int *temp = (u8int *)dest;
    for ( ; len != 0; len--) 
        *temp++ = val;
}

char get_hex_from_int(u8int s)
{
    if(s < 10)
        return s+= '0';
    else
        return s+= 'a' - 10;
}

void dword_to_hex(u32int source, char* dest)
{
    u32int mask = 0x0000000f;
    for(int i = 0; i < 8; i++)
    {
        dest[9 - i] = get_hex_from_int((u8int)(source & mask));
        source >>= 4;
    }
}

void word_to_hex(u16int source, char* dest)
{
    u16int mask = 0x000f;
    for(int i = 0; i < 4; i++)
    {
        dest[5 - i] = get_hex_from_int((u8int)(source & mask));
        source >>= 4;
    }
}

void byte_to_hex(u8int source, char* dest)
{
    u8int mask = 0x0f;
    for(int i = 0; i < 2; i++)
    {
        dest[3 - i] = get_hex_from_int(source & mask);
        source >>= 4;
    }
}
