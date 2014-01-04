#include "../drivers/screen.h"
#include "../drivers/hard_disk.h"
#include "../debug/debug.h"

void main() {
    char* message = "Witamy! - RowanBerryOS Team ;D\n";
    print(message);
    print_at(message, 70, 24);
    print_at(message, 70, 24);
    print(message);
    print_registers();
    read_sectors(1, 1, (void*)0x10000);
    print_memory((void*)0x7c00, 16);
}
