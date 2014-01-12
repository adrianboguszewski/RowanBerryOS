#include "../low_level.h"
#include "../util.h"
#include "../../drivers/screen.h"
#include "isr.h"

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
   print("recieved interrupt: ");
   char* result = "0x  \n";
   byte_to_hex(regs.int_no, result);
   print(result);
} 
