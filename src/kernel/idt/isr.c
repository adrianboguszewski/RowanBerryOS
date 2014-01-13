#include "../low_level.h"
#include "../util.h"
#include "../../drivers/screen.h"
#include "isr.h"
#include "../../const/registers.h"

isr_t interrupt_handler[256];

// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
   print("received interrupt: ");
   char* result = "0x  \n";
   byte_to_hex(regs.int_no, result);
   print(result);
} 

void irq_handler(registers_t regs)
{
    if(regs.int_no >= 40)
        port_byte_out(REG_PIC2_COMMAND, 0x20);  // send end of interrupt signal to slave

    port_byte_out(REG_PIC1_COMMAND, 0x20);      // send end of interrupt signal to master

    if(interrupt_handler[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handler[regs.int_no];
        handler(regs);
    }
}

void register_interrupt_handler(u8int n, isr_t handler)
{
    interrupt_handler[n] = handler;
}