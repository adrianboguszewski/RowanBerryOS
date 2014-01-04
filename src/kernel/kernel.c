#include "../drivers/screen.h"

void main() {
    char* message = "Witamy! - RowanberryOS Team ;D";
    print(message);
    print_at(message, 70, 24);
    print_at(message, 70, 24);
    print(message);
    read_sectors(1, 1, 0x10000);
}
