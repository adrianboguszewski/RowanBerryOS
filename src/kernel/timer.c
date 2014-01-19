#include "timer.h"
#include "idt/isr.h"
#include "low_level.h"
#include "../const/registers.h"
#include "../drivers/screen.h"

static u32int tick = 0;

void timer_callback(registers_t regs)
{
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
    
    // This byte (0x36) sets the PIT to repeating mode 
    // (so that when the divisor counter reaches zero it's automatically refreshed) 
    // and tells it we want to set the divisor value. 
    port_byte_out(REG_PIT_COMMAND, 0x36);       // send command byte
    
    u8int mask = 0xff;
    
    port_byte_out(REG_PIT_CHANNEL0, (u8int)(divisor & mask));           // send the frequency divisor
    port_byte_out(REG_PIT_CHANNEL0, (u8int)((divisor >> 8) & mask));
}

void sleep(u32int ms) 
{
    u32int ticks = ms + tick;
    while(ticks > tick);
}