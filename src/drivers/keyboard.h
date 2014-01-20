#ifndef KEYBOARD_H
#define	KEYBOARD_H

#include "../const/types.h"

/*initialize keyboard*/
void init_keyboard();
/*keyboard interrupt handler*/
void keyboard_handler();
/*read status from keyboard controller*/
u8int kybrd_ctrl_read_status();
/*read keyboard encoder buffer*/
u8int kybrd_enc_read_buf();
/*send command byte to keyboard controller*/
void kybrd_ctrl_send_cmd(u8int cmd); 
/*send command byte to keyboard encoder*/
void kybrd_enc_send_cmd(u8int cmd);

/*returns scroll lock state*/
boolean	kkybrd_get_scroll_lock();
/*returns num lock state*/
boolean	kkybrd_get_numlock();
/*returns caps lock state*/
boolean	kkybrd_get_capslock();
/*returns status of control key*/
boolean	kkybrd_get_ctrl();
/*returns status of alt key*/
boolean	kkybrd_get_alt();
/*returns status of shift key*/
boolean	kkybrd_get_shift();

/*tells driver to ignore last resend request*/
void kkybrd_ignore_resend();
/*return if system should redo last commands*/
boolean kkybrd_check_resend();
/*return diagnostics test result*/
boolean kkybrd_get_diagnostic_res();
/*return BAT test result*/
boolean kkybrd_get_bat_res();
/*return last scan code*/
u8int kkybrd_get_last_scan();
/*sets leds*/
void kkybrd_set_leds(boolean num, boolean caps, boolean scroll);
/*get last key stroke*/
u32int kkybrd_get_last_key();
/*discards last scan*/
void kkybrd_discard_last_key();
/*convert key to an ascii character*/
char kkybrd_key_to_ascii(int code);
/*disables the keyboard*/
void disable_kkybrd();
/*enables the keyboard*/
void enable_kkybrd();
/*returns true if keyboard is disabled*/
boolean kkybrd_is_disabled();
/*reset the system*/
void kkybrd_reset_system();
/*run self test*/
boolean kkybrd_self_test();

// Keyboard encoder----------------------------------------------
#define	KYBRD_ENC_INPUT_BUF 0x60       // Read Input Buffer
#define	KYBRD_ENC_CMD_REG   0x60       // Send Command

// Keyboard encoder commands
#define	KYBRD_ENC_CMD_SET_LED                   0xED
#define	KYBRD_ENC_CMD_ECHO			0xEE
#define	KYBRD_ENC_CMD_SCAN_CODE_SET		0xF0
#define	KYBRD_ENC_CMD_ID			0xF2
#define	KYBRD_ENC_CMD_AUTODELAY			0xF3
#define	KYBRD_ENC_CMD_ENABLE			0xF4
#define	KYBRD_ENC_CMD_RESETWAIT			0xF5
#define	KYBRD_ENC_CMD_RESETSCAN			0xF6
#define	KYBRD_ENC_CMD_ALL_AUTO			0xF7
#define	KYBRD_ENC_CMD_ALL_MAKEBREAK		0xF8
#define	KYBRD_ENC_CMD_ALL_MAKEONLY		0xF9
#define	KYBRD_ENC_CMD_ALL_MAKEBREAK_AUTO	0xFA
#define	KYBRD_ENC_CMD_SINGLE_AUTOREPEAT		0xFB
#define	KYBRD_ENC_CMD_SINGLE_MAKEBREAK		0xFC
#define	KYBRD_ENC_CMD_SINGLE_BREAKONLY		0xFD
#define	KYBRD_ENC_CMD_RESEND			0xFE
#define	KYBRD_ENC_CMD_RESET			0xFF
//---------------------------------------------------------------


// Keyboard controller-------------------------------------------
#define KYBRD_CTRL_STATS_REG 0x64      // Status Register
#define KYBRD_CTRL_CMD_REG  0x64       // Send Command

// Status masks
#define KYBRD_CTRL_STATS_MASK_OUT_BUF	1	//00000001
#define KYBRD_CTRL_STATS_MASK_IN_BUF	2	//00000010
#define KYBRD_CTRL_STATS_MASK_SYSTEM	4	//00000100
#define KYBRD_CTRL_STATS_MASK_CMD_DATA	8	//00001000
#define KYBRD_CTRL_STATS_MASK_LOCKED	0x10	//00010000
#define KYBRD_CTRL_STATS_MASK_AUX_BUF	0x20	//00100000
#define KYBRD_CTRL_STATS_MASK_TIMEOUT	0x40	//01000000
#define KYBRD_CTRL_STATS_MASK_PARITY	0x80	//10000000

// Keyboard controller commands
#define KYBRD_CTRL_CMD_READ		0x20
#define KYBRD_CTRL_CMD_WRITE		0x60
#define KYBRD_CTRL_CMD_SELF_TEST	0xAA
#define KYBRD_CTRL_CMD_INTERFACE_TEST	0xAB
#define KYBRD_CTRL_CMD_DISABLE		0xAD
#define KYBRD_CTRL_CMD_ENABLE		0xAE
#define KYBRD_CTRL_CMD_READ_IN_PORT	0xC0
#define KYBRD_CTRL_CMD_READ_OUT_PORT	0xD0
#define KYBRD_CTRL_CMD_WRITE_OUT_PORT	0xD1
#define KYBRD_CTRL_CMD_READ_TEST_INPUTS	0xE0
#define KYBRD_CTRL_CMD_SYSTEM_RESET	0xFE
#define KYBRD_CTRL_CMD_MOUSE_DISABLE	0xA7
#define KYBRD_CTRL_CMD_MOUSE_ENABLE	0xA8
#define KYBRD_CTRL_CMD_MOUSE_PORT_TEST	0xA9
#define KYBRD_CTRL_CMD_MOUSE_WRITE	0xD4
//---------------------------------------------------------------

// Scan error codes----------------------------------------------
#define KYBRD_ERR_BUF_OVERRUN		0
#define KYBRD_ERR_ID_RET		0x83AB
#define KYBRD_ERR_BAT			0xAA	// note: can also be L. shift key make code
#define KYBRD_ERR_ECHO_RET		0xEE
#define KYBRD_ERR_ACK			0xFA
#define KYBRD_ERR_BAT_FAILED		0xFC
#define KYBRD_ERR_DIAG_FAILED		0xFD
#define KYBRD_ERR_RESEND_CMD		0xFE
#define KYBRD_ERR_KEY			0xFF
//---------------------------------------------------------------

// Keycodes------------------------------------------------------
// Alphanumeric keys
#define KEY_SPACE       ' '
#define KEY_0           '0'
#define KEY_1           '1'
#define KEY_2           '2'
#define KEY_3           '3'
#define KEY_4           '4'
#define KEY_5           '5'
#define KEY_6           '6'
#define KEY_7           '7'
#define KEY_8           '8'
#define KEY_9           '9'

#define KEY_A           'a'
#define KEY_B           'b'
#define KEY_C           'c'
#define KEY_D           'd'
#define KEY_E           'e'
#define KEY_F           'f'
#define KEY_G           'g'
#define KEY_H           'h'
#define KEY_I           'i'
#define KEY_J           'j'
#define KEY_K           'k'
#define KEY_L           'l'
#define KEY_M           'm'
#define KEY_N           'n'
#define KEY_O           'o'
#define KEY_P           'p'
#define KEY_Q           'q'
#define KEY_R           'r'
#define KEY_S           's'
#define KEY_T           't'
#define KEY_U           'u'
#define KEY_V           'v'
#define KEY_W           'w'
#define KEY_X           'x'
#define KEY_Y           'y'
#define KEY_Z           'z'

#define KEY_RETURN      '\r'
#define KEY_ESCAPE      0x1001
#define KEY_BACKSPACE   '\b'

// Arrow keys
#define KEY_UP          0x1100
#define KEY_DOWN        0x1101
#define KEY_LEFT        0x1102
#define KEY_RIGHT       0x1103

// Function keys
#define KEY_F1          0x1201
#define KEY_F2          0x1202
#define KEY_F3          0x1203
#define KEY_F4          0x1204
#define KEY_F5          0x1205
#define KEY_F6          0x1206
#define KEY_F7          0x1207
#define KEY_F8          0x1208
#define KEY_F9          0x1209
#define KEY_F10         0x120a
#define KEY_F11         0x120b
#define KEY_F12         0x120b
#define KEY_F13         0x120c
#define KEY_F14         0x120d
#define KEY_F15         0x120e

#define KEY_DOT         '.'
#define KEY_COMMA       ','
#define KEY_COLON       ':'
#define KEY_SEMICOLON   ';'
#define KEY_SLASH       '/'
#define KEY_BACKSLASH   '\\'
#define KEY_PLUS        '+'
#define KEY_MINUS       '-'
#define KEY_ASTERISK    '*'
#define KEY_EXCLAMATION '!'
#define KEY_QUESTION    '?'
#define KEY_QUOTEDOUBLE '\"'
#define KEY_QUOTE       '\''
#define KEY_EQUAL       '='
#define KEY_HASH        '#'
#define KEY_PERCENT     '%'
#define KEY_AMPERSAND   '&'
#define KEY_UNDERSCORE  '_'
#define KEY_LEFTPARENTHESIS   '('
#define KEY_RIGHTPARENTHESIS  ')'
#define KEY_LEFTBRACKET       '['
#define KEY_RIGHTBRACKET      ']'
#define KEY_LEFTCURL    '{'
#define KEY_RIGHTCURL   '}'
#define KEY_DOLLAR      '$'
#define KEY_POUND       '£'
#define KEY_EURO        '$'
#define KEY_LESS        '<'
#define KEY_GREATER     '>'
#define KEY_BAR         '|'
#define KEY_GRAVE       '`'
#define KEY_TILDE       '~'
#define KEY_AT          '@'
#define KEY_CARRET      '^'

// Numeric keypad 
#define KEY_KP_0        '0'
#define KEY_KP_1        '1'
#define KEY_KP_2        '2'
#define KEY_KP_3        '3'
#define KEY_KP_4        '4'
#define KEY_KP_5        '5'
#define KEY_KP_6        '6'
#define KEY_KP_7        '7'
#define KEY_KP_8        '8'
#define KEY_KP_9        '9'
#define KEY_KP_PLUS     '+'
#define KEY_KP_MINUS    '-'
#define KEY_KP_DECIMAL  '.'
#define KEY_KP_DIVIDE   '/'
#define KEY_KP_ASTERISK '*'
#define KEY_KP_NUMLOCK  0x300f
#define KEY_KP_ENTER    0x3010

#define KEY_TAB         0x4000
#define KEY_CAPSLOCK    0x4001

// Modify keys
#define KEY_LSHIFT      0x4002
#define KEY_LCTRL       0x4003
#define KEY_LALT        0x4004
#define KEY_LWIN        0x4005
#define KEY_RSHIFT      0x4006
#define KEY_RCTRL       0x4007
#define KEY_RALT        0x4008
#define KEY_RWIN        0x4009

#define KEY_INSERT      0x400a
#define KEY_DELETE      0x400b
#define KEY_HOME        0x400c
#define KEY_END         0x400d
#define KEY_PAGEUP      0x400e
#define KEY_PAGEDOWN    0x400f
#define KEY_SCROLLLOCK  0x4010
#define KEY_PAUSE       0x4011

#define KEY_UNKNOWN     0
#define KEY_NUMKEYCODES
//---------------------------------------------------------------

#define INVALID_SCANCODE 0

#endif	/* KEYBOARD_H */

