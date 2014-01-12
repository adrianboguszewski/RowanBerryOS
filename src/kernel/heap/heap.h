#ifndef HEAP_H
#define	HEAP_H

#define HEAP_START 0x10000                              // heap start address
#define HEAP_MAGIC 0x12345678
#define HEAP_INDEX_SIZE 0x1000

#include "../../const/types.h"
#include "ordered_array.h"

typedef struct
{
    u32int magic;       // magic number used for identification
    u8int is_hole;      // 1 if this is hole, 0 otherwise
    u32int size;        // size of the block, including footer
} header;

typedef struct
{
    u32int magic;       // the same as in header
    header* head;       // pointer to header of the block
} footer;

typedef struct
{
    ordered_array index; 
    u32int start_address;
    u32int end_address;
} heap;
/*create heap and place it in memory*/
heap* create_heap(u32int start, u32int end_addr);
/*alloc given number of bytes*/
void* alloc(u32int size, heap* h);
/*free memory*/
void free(void* address, heap* h);

#endif
