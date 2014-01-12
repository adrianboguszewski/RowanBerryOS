#ifndef UTIL_H
#define UTIL_H

#define NULL 0

#include "../const/types.h"

/*copy bytes from one place to another. */
void memory_copy(void* source, void* dest, int no_bytes);
/*set value in memory*/
void memory_set(void* dest, s8int value, u32int bytes);
/*return hex character from integer number*/
char get_hex_from_int(unsigned char s);
/*change int to hex*/
void dword_to_hex(unsigned int source, char* dest);
/*change short to hex*/
void word_to_hex(unsigned short source, char* dest);
/*change byte to hex*/
void byte_to_hex(unsigned char source, char* dest);

#endif
