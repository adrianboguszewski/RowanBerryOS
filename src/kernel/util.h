#ifndef _UTIL_H
#define _UTIL_H

void memory_copy(char* source, char* dest, int no_bytes);
char get_hex_from_int(unsigned int s);
void dword_to_hex(int source, char* dest);
void word_to_hex(unsigned short source, char* dest);
void byte_to_hex(unsigned char source, char* dest);

#endif
