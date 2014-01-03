#include "../drivers/screen.h"

void main() {
	//char* video_memory = (char*) 0xb8000;
	//*video_memory = 'X';

	char* message = "Witamy! - RowanberryOS Team ;D";
	print(message);
	print_at(message, 70, 24);
	print_at(message, 70, 24);
	print(message);
}
