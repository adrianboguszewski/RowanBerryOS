#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f    // Attribute byte for our default colour scheme.

#include "../const/types.h"

/*print time at the upper right corner*/
void print_time(u32int time);
/*print string on screen*/
void print(char* message);
/*it's backspace function*/
void remove_last_char();
/*print string at given column and row*/
void print_at(char* message, s8int col, s8int row);
/*clear screen*/
void clear_screen();
/*print one character at given column and row with color and background*/
void print_char(char character, s8int col, s8int row, u8int attribute_byte);
/*get last character position*/
u32int get_screen_offset(s8int col, s8int row);
/*return cursor position*/
u32int get_cursor();
/*set cursor position*/
void set_cursor(u32int offset);
/*move rows bottom up*/
u32int handle_scrolling(u32int cursor_offset);

#endif
