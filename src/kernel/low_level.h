#ifndef _LOW_LEVEL_H
#define _LOW_LEVEL_H

typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

/**/
unsigned char port_byte_in(unsigned short port);
/**/
void port_byte_out(unsigned short port, unsigned char data);
/**/
unsigned short port_word_in(unsigned short port);
/**/
void port_word_out(unsigned short port, unsigned short data);
/*return byte from memory under given address*/
unsigned char memory_byte(void* adr);
/*low level reading disk*/
void read_disk(unsigned int words, unsigned short reg, void* memory_buf);
/*low level writing disk*/
void write_disk(unsigned int words, unsigned short reg, void* memory_buf);

#endif
