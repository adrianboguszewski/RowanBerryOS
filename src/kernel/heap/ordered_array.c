#include "ordered_array.h"
#include "../util.h"
#include "../../const/machine.h"
#include "heap.h"

ordered_array place_ordered_array(void *addr, u32int max_size)
{
   ordered_array to_ret;
   to_ret.array = (u32int*)addr;
   memory_set(to_ret.array, 0, max_size * sizeof(u32int*));
   to_ret.size = 0;
   to_ret.max_size = max_size;
   return to_ret;
}

void insert_ordered_array(u32int item, ordered_array *array)
{
   u32int i = 0;
   while (i < array->size && array->array[i] < item)
       i++;
   if (i == array->size) // just add at the end of the array.
       array->array[array->size++] = item;
   else
   {
       u32int j;
       for(j = array->size; j > i; j--)
           array->array[j] = array->array[j - 1];

       array->array[i] = item;
       array->size++;
   }
}

u32int lookup_ordered_array(u32int i, ordered_array *array)
{
   return array->array[i];
}

void remove_ordered_array(u32int i, ordered_array *array)
{
   while (i < array->size)
   {
       array->array[i] = array->array[i+1];
       i++;
   }
   array->size--;
} 
