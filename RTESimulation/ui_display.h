#ifndef UI_DISPLAY_H
#define UI_DISPLAY_H

#include <windows.h>

void mainmenu(void);
void ConveyorOne(void);
void ConveyorTwo(void);
void init_screen_buffers(void);
void get_key_press(void);
void update_display(void);
void print_context_information(void);

void clear_display(HANDLE hbuffer);
COORD set_cursor(int X, int Y);

#endif //UI_DISPLAY_H