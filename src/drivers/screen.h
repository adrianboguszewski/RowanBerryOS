#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f	// Attribute byte for our default colour scheme.

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void print(char* message);
void print_at(char* message, int col, int row);
void clear_screen();
void print_char(char character, int col, int row, char attribute_byte);
int get_screen_offset(int col, int row);
int get_cursor();
void set_cursor(int offset);
int handle_scrolling(int cursor_offset);