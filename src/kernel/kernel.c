#include "../drivers/screen.h"
#include "../drivers/hard_disk.h"
#include "../debug/debug.h"
#include "heap/heap.h"
#include "util.h"
#include "../const/machine.h"
#include "idt/idt_table.h"

void main() 
{
    init_idt();
    read_sectors(0, 1, (void*)0x10000);
    print_memory((void*)0x10000, 128);
    char* message = "Witamy! - RowanBerryOS Team ;D\n";
    print(message);
    heap* h = create_heap(HEAP_START, MAX_MEMORY_ADDRESS + 1);
    print_memory((void*)0x10000, 64);
    print_memory((void*)0x14000, 64);
    __asm__("int $0x1");
    __asm__("int $0x0d");   
}
