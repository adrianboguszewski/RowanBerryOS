#include "../drivers/screen.h"
#include "../drivers/hard_disk.h"
#include "../debug/debug.h"
#include "heap/heap.h"
#include "util.h"
#include "../const/machine.h"

void main() {
    char* message = "Witamy! - RowanBerryOS Team ;D\n";
    print(message);
    heap* h = create_heap(HEAP_START, MAX_MEMORY_ADDRESS + 1);
    print("\n");
    u32int* a = alloc(4, h);
    u32int* b = alloc(32, h);
    u32int* c = alloc(4, h);
    free(b, h);
    u32int* d = alloc(2, h);
    print_memory((void*)0x10000, 64);
    print("\n");
    print_memory((void*)0x14000, 128);
    print("\n");
    print_memory((void*)0x01fffff0, 32);
    
}
