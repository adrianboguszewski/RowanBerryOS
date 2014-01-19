#ifndef ORDERED_ARRAY_H
#define	ORDERED_ARRAY_H

#include "../../const/types.h"

typedef struct
{
   u32int* array;
   u32int size;
   u32int max_size;
} ordered_array;

/*place array in memory*/
ordered_array create_ordered_array(void* addr, u32int max_size);
/*insert element to array*/
void insert_ordered_array(u32int item, ordered_array* array);
/*return value under given index*/
u32int lookup_ordered_array(u32int i, ordered_array* array);
/*remove item from array*/
void remove_ordered_array(u32int i, ordered_array* array);

#endif	

