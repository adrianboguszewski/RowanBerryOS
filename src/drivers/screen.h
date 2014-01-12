#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f    // Attribute byte for our default colour scheme.

#include "../const/types.h"

/**/
void print(char* message);
/**/
void print_at(char* message, s8int col, s8int row);
/**/
void clear_screen();
/**/
void print_char(char character, s8int col, s8int row, u8int attribute_byte);
/**/
u32int get_screen_offset(s8int col, s8int row);
/**/
u32int get_cursor();
/**/
void set_cursor(u32int offset);
/**/
u32int handle_scrolling(u32int cursor_offset);

#endif
