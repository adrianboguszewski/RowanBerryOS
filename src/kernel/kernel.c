#include "../drivers/screen.h"
#include "../drivers/hard_disk.h"
#include "../debug/debug.h"
#include "heap/heap.h"
#include "util.h"
#include "../const/machine.h"
#include "../boot/idt/idt_table.h"

void main() 
{
    init_idt();
    char* message = "Witamy! - RowanBerryOS Team ;D\n";
    print(message);
    heap* h = create_heap(HEAP_START, MAX_MEMORY_ADDRESS + 1);
    __asm__("int $0x1");
    __asm__("int $0x0d");   
}
