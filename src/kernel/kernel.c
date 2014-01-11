#include "../drivers/screen.h"
#include "../drivers/hard_disk.h"
#include "../debug/debug.h"
#include "../boot/idt/idt_table.h"

void main() {
    init_idt();
    char* message = "Witamy! - RowanBerryOS Team ;D\n";
    print(message);
    __asm__("int $0x1");
    __asm__("int $0x0d");
    /*print_at(message, 70, 24);
    print_at(message, 70, 24);
    print(message);
    print_registers();
    read_sectors(0, 1, (void*)0x10000);
    print_memory((void*)0x10000, 32);
    write_sectors(30, 1, (void*)0x10000);
    write_sectors(31, 1, (void*)0x10000);
    read_sectors(30, 2, (void*)0x20000);
    print_memory((void*)0x20000, 528);*/
    
    
}
