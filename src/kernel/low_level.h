#ifndef LOW_LEVEL_H
#define LOW_LEVEL_H

#include "../const/types.h"

/*receive byte from given port*/
u8int port_byte_in(u16int port);
/*send byte to port*/
void port_byte_out(u16int port, u8int data);
/*receive word from port*/
u16int port_word_in(u16int port);
/*send word to port*/
void port_word_out(u16int port, u16int data);
/*return byte from memory under given address*/
u8int memory_byte(void* adr);
/*low level reading disk*/
void read_disk(u32int words, u16int reg, void* memory_buf);
/*low level writing disk*/
void write_disk(u32int words, u16int reg, void* memory_buf);

#endif
