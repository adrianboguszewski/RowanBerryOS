#ifndef _UTIL_H
#define _UTIL_H

#include "low_level.h"

/*Copy bytes from one place to another.*/
void memory_copy(char* source, char* dest, int no_bytes);
/*Write len copies of val into dest.*/
void memset(u8int *dest, u8int val, u32int len);
/*return hex character from integer number*/
char get_hex_from_int(unsigned char s);
/*change int to hex*/
void dword_to_hex(unsigned int source, char* dest);
/*change short to hex*/
void word_to_hex(unsigned short source, char* dest);
/*change byte to hex*/
void byte_to_hex(unsigned char source, char* dest);

#endif
