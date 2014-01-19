#include "../drivers/screen.h"
#include "../drivers/hard_disk.h"
#include "../debug/debug.h"
#include "heap/heap.h"
#include "util.h"
#include "../const/machine.h"
#include "idt/idt_table.h"
#include "timer.h"
#include "../drivers/keyboard.h"

void run();

void main() 
{
    init_idt();
    init_timer(0);
    init_keyboard();
    read_sectors(0, 1, (void*)0x10000);
    print_memory((void*)0x10000, 128);
    char* message = "Witamy! - RowanBerryOS Team ;D\n";
    print(message);
    run();
//    heap* h = create_heap(HEAP_START, MAX_MEMORY_ADDRESS + 1);
//    print_memory((void*)0x10000, 64);
//    print_memory((void*)0x14000, 64);
}

// wait for key stroke
int getch () {
    int key = KEY_UNKNOWN;

    // wait for a keypress
    while(key == KEY_UNKNOWN)
    {
            key = kkybrd_get_last_key ();
    }
    // discard last keypress (we handled it) and return
    kkybrd_discard_last_key();
    return key;
}

// command prompt
void cmd() 
{
    print("\nCommand> ");
}

// gets next command
void get_cmd(char* buf, int n) 
{
    cmd();

    int key = KEY_UNKNOWN;
    boolean buf_char;

    // get command string
    int i = 0;
    while(i < n) 
    {
        // buffer the next char
        buf_char = true;

        // grab next char
        key = getch();

        // end of command if enter is pressed
        if(key == KEY_RETURN)
        {
            break;
        }
        // backspace
        if(key == KEY_BACKSPACE) 
        {
            // dont buffer this char
            buf_char = false;
            if(i > 0) 
            {
                remove_last_char();
            }
        }

        // only add the char if it is to be buffered
        if (buf_char) 
        {
            // convert key to an ascii char and put it in buffer
            char c = kkybrd_key_to_ascii(key);
            if(c != 0) { //insure its an ascii char
                buf[i++] = c;
                char sign[2] = { c, 0 };
                print(sign);
            }
        }
    }

    // null terminate the string
    buf[i] = '\0';
}

void run() {
    // command buffer
    char cmd_buf [100];

    while(1) 
    {
        // get command
        get_cmd(cmd_buf, 98);
    }
}
