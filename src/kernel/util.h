#ifndef _UTIL_H
#define _UTIL_H

/**/
void memory_copy(char* source, char* dest, int no_bytes);
/*return hex character from integer number*/
char get_hex_from_int(unsigned char s);
/*change int to hex*/
void dword_to_hex(int source, char* dest);
/*change short to hex*/
void word_to_hex(unsigned short source, char* dest);
/*change byte to hex*/
void byte_to_hex(unsigned char source, char* dest);

#endif
