#ifndef DEBUG_H
#define DEBUG_H

/*print all general purposed registers and flags register*/
void print_registers();
/*print memory content under given address*/
void print_memory(void* start, int bytes);
/*print error message*/
void print_msg(char* msg);
/*print variable size of byte*/
void print_byte(unsigned char b);
/*print variable size of word*/
void print_word(unsigned short b);
/*print variable size of dword*/
void print_dword(unsigned int b);
/*print message "I reached" */
void print_db();
#endif
