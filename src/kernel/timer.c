#include "timer.h"
#include "idt/isr.h"
#include "low_level.h"
#include "../const/registers.h"
#include "../drivers/screen.h"

void timer_callback(registers_t regs)
{
    static u32int tick = 0;
    tick++;
    print_time(tick);
}

void init_timer(u32int frequency)
{
    register_interrupt_handler(IRQ0, &timer_callback);
    
    u32int divisor;
    if(frequency != 0)
        // PIT has 1193180Hz clock
        divisor = 1193180 / frequency;
    else
        divisor = 0;
    
    port_byte_out(REG_PIT_COMMAND, 0x36);       // send command byte
    
    u8int mask = 0xff;
    
    port_byte_out(REG_PIT_CHANNEL0, (u8int)(divisor & mask));           // send the frequency divisor
    port_byte_out(REG_PIT_CHANNEL0, (u8int)((divisor >> 8) & mask));
}