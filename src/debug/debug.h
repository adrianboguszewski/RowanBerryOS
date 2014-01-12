#ifndef DEBUG_H
#define DEBUG_H

#include "../const/types.h"

/*print all general purposed registers and flags register*/
void print_registers();
/*print memory content under given address*/
void print_memory(void* start, u32int bytes);
/*print error message*/
void print_msg(char* msg);
/*print variable size of byte*/
void print_byte(u8int b);
/*print variable size of word*/
void print_word(u16int b);
/*print variable size of dword*/
void print_dword(u32int b);
/*print message "I reached" */
void print_db();
#endif
