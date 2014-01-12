#include "heap.h"
#include "ordered_array.h"
#include "../../const/machine.h"
#include "../util.h"
#include "../../debug/debug.h"

heap* create_heap(u32int start, u32int end_addr) 
{
    heap* h = (heap*)start;
    // Initialise the index.
    h->index = place_ordered_array((void*)(start + sizeof(heap)), HEAP_INDEX_SIZE);

    // Shift the start address forward to resemble where we can start putting data.
    start += sizeof (u32int*)*HEAP_INDEX_SIZE + sizeof(heap);

    // Write the start, end and max addresses into the heap structure.
    h->start_address = start;
    h->end_address = end_addr;

    // We start off with one large hole in the index.
    header *hole = (header*) start;
    hole->size = end_addr - start;
    hole->magic = HEAP_MAGIC;
    hole->is_hole = 1;
    footer *foot = (footer*)(start + end_addr - start - sizeof(footer));
    foot->head = hole;
    foot->magic = HEAP_MAGIC;
    insert_ordered_array((u32int) hole, &h->index);

    return h;
}

s32int find_smallest_hole(u32int size, heap* h) 
{
    // Find the smallest hole that will fit.
    u32int i = 0;
    while (i < h->index.size) {
        header* head = (header*) lookup_ordered_array(i, &h->index);

        if (head->size >= size)
            break;

        i++;
    }

    if (i == h->index.size)
        return -1; // We got to the end and didn't find anything.
    else
        return i;
}

void* alloc(u32int size, heap* h) 
{
    u32int new_size = size + sizeof (header) + sizeof (footer);
    s32int iterator = find_smallest_hole(new_size, h);
    
    if (iterator == -1) // If we didn't find a suitable hole
    {
        print_msg("No enough memory space\n");
        return NULL;
    }

    header *orig_hole_header = (header *) lookup_ordered_array(iterator, &h->index);
    u32int orig_hole_pos = (u32int) orig_hole_header;
    u32int orig_hole_size = orig_hole_header->size;
    // Here we work out if we should split the hole we found into two parts.
    // Is the original hole size - requested hole size less than the overhead for adding a new hole?
    if (orig_hole_size - new_size < sizeof (header) + sizeof (footer)) {
        // Then just increase the requested size to the size of the hole we found.
        size += orig_hole_size - new_size;
        new_size = orig_hole_size;
    }
    remove_ordered_array(iterator, &h->index);

    // we make sure all the header and footer attributes are correct, along with magic numbers
    header *block_header = (header *) orig_hole_pos;
    block_header->magic = HEAP_MAGIC;
    block_header->is_hole = 0;
    block_header->size = new_size;

    footer *block_footer = (footer *) (orig_hole_pos + sizeof (header) + size);
    block_footer->magic = HEAP_MAGIC;
    block_footer->head = block_header;

    // We may need to write a new hole after the allocated block.
    // We do this only if the new hole would have positive size...
    if (orig_hole_size - new_size > 0) {
        header *hole_header = (header *) (orig_hole_pos + sizeof (header) + size + sizeof (footer));
        hole_header->magic = HEAP_MAGIC;
        hole_header->is_hole = 1;
        hole_header->size = orig_hole_size - new_size;
        footer *hole_footer = (footer *) ((u32int) hole_header + orig_hole_size - new_size - sizeof (footer));
        if ((u32int) hole_footer < h->end_address) {
            hole_footer->magic = HEAP_MAGIC;
            hole_footer->head = hole_header;
        }
        // Put the new hole in the index;
        insert_ordered_array((u32int) hole_header, &h->index);
    }

    return (void *) ((u32int) block_header + sizeof (header));
}

void free(void* p, heap* h) 
{
    // Exit gracefully for null pointers.
    if (p == NULL)
        return;

    // Get the header and footer associated with this pointer.
    header *head = (header*) ((u32int) p - sizeof (header));
    footer *foot = (footer*) ((u32int) head + head->size - sizeof (footer));

    // Sanity checks.
    if(!(head->magic == HEAP_MAGIC && foot->magic == HEAP_MAGIC))
    {
        print_msg("Memory error\n");
        return;
    }

    // Make us a hole.
    head->is_hole = 1;

    // Do we want to add this head into the 'free holes' index?
    char do_add = 1;

    // Unify left
    // If the thing immediately to the left of us is a foot...
    footer *test_foot = (footer*) ((u32int) head - sizeof (footer));
    if (test_foot->magic == HEAP_MAGIC && test_foot->head->is_hole) {
        u32int cache_size = head->size; // Cache our current size.
        head = test_foot->head; // Rewrite our head with the new one.
        foot->head = head; // Rewrite our foot to point to the new head.
        head->size += cache_size; // Change the size.
        do_add = 0; // Since this head is already in the index, we don't want to add it again.
    }

    // Unify right
    // If the thing immediately to the right of us is a head...
    header *test_head = (header*) ((u32int) foot + sizeof (footer));
    if (test_head->magic == HEAP_MAGIC && test_head->is_hole) {
        head->size += test_head->size; // Increase our size.
        test_foot = (footer*) ((u32int) test_head + // Rewrite it's foot to point to our head.
                test_head->size - sizeof (footer));
        test_foot->head = head;
        // Find and remove this head from the index.
        u32int iterator = 0;
        while ((iterator < h->index.size) && (lookup_ordered_array(iterator, &h->index) != (u32int) test_head))
            iterator++;

        // Make sure we actually found the item.
        if(iterator >= h->index.size)
        {
            print_msg("Iterator behind heap size");
            return;
        }
        // Remove it.
        remove_ordered_array(iterator, &h->index);
    }

    if (do_add == 1)
        insert_ordered_array((u32int) head, &h->index);
}