#ifndef _DEBUG_H
#define _DEBUG_H

void print_registers();
void print_memory(void* start, int bytes);
void print_msg(char* msg);
void print_byte(unsigned char b);
void print_word(unsigned short b);
void print_dword(unsigned int b);

#endif
