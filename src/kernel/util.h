#ifndef UTIL_H
#define UTIL_H

#define NULL 0

#include "../const/types.h"

#include "low_level.h"

/*Copy bytes from one place to another.*/
void memory_copy(void* source, void* dest, u32int no_bytes);
/*Write len copies of val into dest.*/
void memset(void *dest, s8int val, u32int len);
/*return hex character from integer number*/
char get_hex_from_int(u8int s);
/*change int to hex*/
void dword_to_hex(u32int source, char* dest);
/*change short to hex*/
void word_to_hex(u16int source, char* dest);
/*change byte to hex*/
void byte_to_hex(u8int source, char* dest);

#endif
