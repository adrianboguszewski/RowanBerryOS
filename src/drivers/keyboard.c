#include "keyboard.h"
#include "../kernel/idt/isr.h"
#include "screen.h"
#include "../kernel/low_level.h"

u8int scancode;                          // current scan code
boolean numlock, scrolllock, capslock;  // lock keys
boolean shift, alt, ctrl;               // shift, alt, and ctrl keys current state
int kkybrd_error = 0;                   // set if keyboard error
boolean kkybrd_bat_res = false;         // set if the Basic Assurance Test (BAT) failed
boolean kkybrd_diag_res = false;        // set if diagnostics failed
boolean kkybrd_resend_res = false;      // set if system should resend last command
boolean kkybrd_disable = false;         // set if keyboard is disabled

// original xt scan code set. Array index==make code
// change what keys the scan code corrospond to if your scan code set is different
int kkybrd_scancode_std [] = {
	// key			scancode
	KEY_UNKNOWN,            //0
	KEY_ESCAPE,		//1
	KEY_1,			//2
	KEY_2,			//3
	KEY_3,			//4
	KEY_4,			//5
	KEY_5,			//6
	KEY_6,			//7
	KEY_7,			//8
	KEY_8,			//9
	KEY_9,			//0xa
	KEY_0,			//0xb
	KEY_MINUS,		//0xc
	KEY_EQUAL,		//0xd
	KEY_BACKSPACE,          //0xe
	KEY_TAB,		//0xf
	KEY_Q,			//0x10
	KEY_W,			//0x11
	KEY_E,			//0x12
	KEY_R,			//0x13
	KEY_T,			//0x14
	KEY_Y,			//0x15
	KEY_U,			//0x16
	KEY_I,			//0x17
	KEY_O,			//0x18
	KEY_P,			//0x19
	KEY_LEFTBRACKET,//0x1a
	KEY_RIGHTBRACKET,//0x1b
	KEY_RETURN,		//0x1c
	KEY_LCTRL,		//0x1d
	KEY_A,			//0x1e
	KEY_S,			//0x1f
	KEY_D,			//0x20
	KEY_F,			//0x21
	KEY_G,			//0x22
	KEY_H,			//0x23
	KEY_J,			//0x24
	KEY_K,			//0x25
	KEY_L,			//0x26
	KEY_SEMICOLON,	//0x27
	KEY_QUOTE,		//0x28
	KEY_GRAVE,		//0x29
	KEY_LSHIFT,		//0x2a
	KEY_BACKSLASH,	//0x2b
	KEY_Z,			//0x2c
	KEY_X,			//0x2d
	KEY_C,			//0x2e
	KEY_V,			//0x2f
	KEY_B,			//0x30
	KEY_N,			//0x31
	KEY_M,			//0x32
	KEY_COMMA,		//0x33
	KEY_DOT,		//0x34
	KEY_SLASH,		//0x35
	KEY_RSHIFT,		//0x36
	KEY_KP_ASTERISK,        //0x37
	KEY_RALT,		//0x38
	KEY_SPACE,		//0x39
	KEY_CAPSLOCK,           //0x3a
	KEY_F1,			//0x3b
	KEY_F2,			//0x3c
	KEY_F3,			//0x3d
	KEY_F4,			//0x3e
	KEY_F5,			//0x3f
	KEY_F6,			//0x40
	KEY_F7,			//0x41
	KEY_F8,			//0x42
	KEY_F9,			//0x43
	KEY_F10,		//0x44
	KEY_KP_NUMLOCK,         //0x45
	KEY_SCROLLLOCK,         //0x46
	KEY_HOME,		//0x47
	KEY_KP_8,		//0x48	//keypad up arrow
	KEY_PAGEUP,		//0x49
	KEY_KP_2,		//0x50	//keypad down arrow
	KEY_KP_3,		//0x51	//keypad page down
	KEY_KP_0,		//0x52	//keypad insert key
	KEY_KP_DECIMAL,         //0x53	//keypad delete key
	KEY_UNKNOWN,            //0x54
	KEY_UNKNOWN,            //0x55
	KEY_UNKNOWN,            //0x56
	KEY_F11,		//0x57
	KEY_F12			//0x58
};

void init_keyboard()
{
    register_interrupt_handler(IRQ1, &keyboard_handler);
    
    // assume BAT test is good. If there is a problem, the IRQ handler where catch the error
    kkybrd_bat_res = true;
    scancode = 0;
    
    // set lock keys and led lights
    numlock = false;
    scrolllock = false;
    capslock = false;
    kkybrd_set_leds(numlock, scrolllock, capslock);
    
    // shift, ctrl, and alt keys
    shift = false;
    alt = false;
    ctrl = false;
}

void keyboard_handler() 
{
    //boolean extended;
    
    // read scan code only if the kybrd controller output buffer is full (scan code is in it)
    if(kybrd_ctrl_read_status() & KYBRD_CTRL_STATS_MASK_OUT_BUF) 
    {
        
        
        // read the scan code
        int code = kybrd_enc_read_buf();

        // is this an extended code? If so, set it and return
        if(code == 0xE0 || code == 0xE1)
        {
            //extended = true;
        }
        else 
        {
            // either the second byte of an extended scan code or a single byte scan code
            //extended = false;

            // test if this is a break code (Original XT Scan Code Set specific)
            if(code & 0x80) //test bit 7
            {	
                // convert the break code into its make code equivelant
                code -= 0x80;

                // grab the key
                int key = kkybrd_scancode_std[code];

                // test if a special key has been released & set it
                switch (key) 
                {
                    case KEY_LCTRL:
                    case KEY_RCTRL:         ctrl = false;
                                            break;

                    case KEY_LSHIFT:
                    case KEY_RSHIFT:        shift = false;
                                            break;

                    case KEY_LALT:
                    case KEY_RALT:          alt = false;
                                            break;
                }
            }
            else 
            {
                // this is a make code - set the scan code
                scancode = code;

                // grab the key
                int key = kkybrd_scancode_std[code];
                // test if user is holding down any special keys & set it
                switch(key) 
                {
                    case KEY_LCTRL:
                    case KEY_RCTRL:         ctrl = true;
                                            break;

                    case KEY_LSHIFT:
                    case KEY_RSHIFT:        shift = true;
                                            break;

                    case KEY_LALT:
                    case KEY_RALT:          alt = true;
                                            break;

                    case KEY_CAPSLOCK:      capslock = (capslock) ? 0 : 1;
                                            kkybrd_set_leds(numlock, capslock, scrolllock);
                                            break;

                    case KEY_KP_NUMLOCK:    numlock = (numlock) ? 0 : 1;
                                            kkybrd_set_leds(numlock, capslock, scrolllock);
                                            break;

                    case KEY_SCROLLLOCK:    scrolllock = (scrolllock) ? 0 : 1;
                                            kkybrd_set_leds(numlock, capslock, scrolllock);
                                            break;
                }
            }
        }

        // watch for errors
        switch(code) 
        {
            case KYBRD_ERR_BAT_FAILED:          kkybrd_bat_res = false;
                                                break;

            case KYBRD_ERR_DIAG_FAILED:         kkybrd_diag_res = false;
                                                break;

            case KYBRD_ERR_RESEND_CMD:          kkybrd_resend_res = true;
                                                break;
        }
    }
}

u8int kybrd_ctrl_read_status() 
{
    return port_byte_in(KYBRD_CTRL_STATS_REG);
}

u8int kybrd_enc_read_buf() 
{
    return port_byte_in(KYBRD_ENC_INPUT_BUF);
}

void kybrd_ctrl_send_cmd(u8int cmd) 
{
    // wait for kybrd controller input buffer to be clear
    while(1)
    {
        if((kybrd_ctrl_read_status() & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0)
        {
            break;
        }
    }
    port_byte_out(KYBRD_CTRL_CMD_REG, cmd);
}

void kybrd_enc_send_cmd(u8int cmd) 
{
    // wait for kybrd controller input buffer to be clear
    while(1)
    {
        if((kybrd_ctrl_read_status() & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0)
        {
            break;
        }
    }
    // send command byte to kybrd encoder
    port_byte_out(KYBRD_ENC_CMD_REG, cmd);
}

boolean	kkybrd_get_scroll_lock() 
{
    return scrolllock;
}

boolean	kkybrd_get_numlock() 
{
    return numlock;
}

boolean	kkybrd_get_capslock()	
{
    return capslock;
}

boolean	kkybrd_get_ctrl()	
{
    return ctrl;
}

boolean	kkybrd_get_alt() 
{
    return alt;
}

boolean	kkybrd_get_shift()
{
    return shift;
}

void kkybrd_ignore_resend()
{
    kkybrd_resend_res = false;
}

boolean kkybrd_check_resend() 
{
    return kkybrd_resend_res;
}

boolean kkybrd_get_diagnostic_res() 
{
    return kkybrd_diag_res;
}

boolean kkybrd_get_bat_res() 
{
    return kkybrd_bat_res;
}

u8int kkybrd_get_last_scan()	
{	
    return scancode;
}

void kkybrd_set_leds(boolean num, boolean caps, boolean scroll) 
{
    u8int data = 0;

    // set or clear the bit
    data = (scroll) ? (data | 1) : (data & 1);
    data = (num) ? (num | 2) : (num & 2);
    data = (caps) ? (num | 4) : (num & 4);

    // send the command -- update keyboard Light Emetting Diods (LEDs)
    kybrd_enc_send_cmd(KYBRD_ENC_CMD_SET_LED);
    kybrd_enc_send_cmd(data);
}

u32int kkybrd_get_last_key() 
{
    return (scancode != INVALID_SCANCODE) ? (kkybrd_scancode_std[scancode]) : (KEY_UNKNOWN);
}

void kkybrd_discard_last_key() 
{
    scancode = INVALID_SCANCODE;
}

char kkybrd_key_to_ascii(int code)
{
    u8int key = code;

    // insure key is an ascii character
    if ((unsigned)(key) <= 0x7F) 
    {
        // if shift key is down or caps lock is on, make the key uppercase
        if(shift || capslock)
        {
            if(key >= 'a' && key <= 'z')
            {
                key -= 32;
            }
        }
        if(shift && !capslock)
        {
            if (key >= '0' && key <= '9')
            {
                switch (key) 
                {
                    case '0':       key = KEY_RIGHTPARENTHESIS;
                                    break;

                    case '1':       key = KEY_EXCLAMATION;
                                    break;

                    case '2':       key = KEY_AT;
                                    break;

                    case '3':       key = KEY_EXCLAMATION;
                                    break;

                    case '4':       key = KEY_HASH;
                                    break;

                    case '5':       key = KEY_PERCENT;
                                    break;

                    case '6':       key = KEY_CARRET;
                                    break;

                    case '7':       key = KEY_AMPERSAND;
                                    break;

                    case '8':       key = KEY_ASTERISK;
                                    break;

                    case '9':       key = KEY_LEFTPARENTHESIS;
                                    break;
                }
            }
            else 
            {
                switch(key) 
                {
                    case KEY_COMMA:     key = KEY_LESS;
                                        break;

                    case KEY_DOT:       key = KEY_GREATER;
                                        break;

                    case KEY_SLASH:     key = KEY_QUESTION;
                                        break;

                    case KEY_SEMICOLON: key = KEY_COLON;
                                        break;

                    case KEY_QUOTE:     key = KEY_QUOTEDOUBLE;
                                        break;

                    case KEY_LEFTBRACKET: key = KEY_LEFTCURL;
                                        break;

                    case KEY_RIGHTBRACKET: key = KEY_RIGHTCURL;
                                        break;

                    case KEY_GRAVE:     key = KEY_TILDE;
                                        break;

                    case KEY_MINUS:     key = KEY_UNDERSCORE;
                                        break;

                    case KEY_PLUS:      key = KEY_EQUAL;
                                        break;

                    case KEY_BACKSLASH: key = KEY_BAR;
                                        break;
                }
            }
        }
        // return the key
        return key;
    }

    // scan code != a valid ascii char so no convertion is possible
    return 0;
}

void disable_kkybrd() 
{
    kybrd_ctrl_send_cmd(KYBRD_CTRL_CMD_DISABLE);
    kkybrd_disable = true;
}

void enable_kkybrd() 
{
    kybrd_ctrl_send_cmd (KYBRD_CTRL_CMD_ENABLE);
    kkybrd_disable = false;
}

boolean kkybrd_is_disabled() 
{
    return kkybrd_disable;
}

void kkybrd_reset_system() 
{
    // writes 11111110 to the output port (sets reset system line low)
    kybrd_ctrl_send_cmd(KYBRD_CTRL_CMD_WRITE_OUT_PORT);
    kybrd_enc_send_cmd(0xfe);
}

boolean kkybrd_self_test() 
{
    // send command
    kybrd_ctrl_send_cmd(KYBRD_CTRL_CMD_SELF_TEST);

    // wait for output buffer to be full
    while(1)
    {
        if(kybrd_ctrl_read_status() & KYBRD_CTRL_STATS_MASK_OUT_BUF)
        {
            break;
        }
    }
    // if output buffer == 0x55, test passed
    return (kybrd_enc_read_buf() == 0x55) ? 1 : 0;
}