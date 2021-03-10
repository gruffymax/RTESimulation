#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <process.h>
#include "cinterface.h"
#include "belt.h"


//prototypes
void init_screen_buffers(void);
COORD set_cursor(int X, int Y);
void update_screen(void);
// Thread prototypes
void thread_tick(void);


//Global variables
extern uint32_t ticks; //Define ticks as a global variable
uint32_t ticks = 0; // Declare ticks and initialise

HANDLE hStdout, hMainMenuBuffer, hConv1Buffer;

//main
int main()
{
    _beginthread(thread_tick, 4, NULL);

    init_screen_buffers(); // Our function to create scfreen buffer handles etc

    char text_buffer[100];

    SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(0, 0)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Please select the option you wish to choose:"); // Create text buffer to display
    WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 1)); // Move cursor to a new position
    sprintf_s(text_buffer, 100, "[1] - Conveyor 1"); // Create text buffer
    WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

    SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 2));
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(hMainMenuBuffer, &cursor_info); // Turn off the visible cursor

    place_large_block_belt0();

    uint32_t old_tick = 0;
    while (1)
    {
        if (ticks > old_tick)
        {
            move_belt0_fwds();
            update_screen();
            old_tick = ticks;
        }
    }
}
void init_screen_buffers(void)
{
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    hMainMenuBuffer = CreateConsoleScreenBuffer(
        GENERIC_READ |           // read/write access
        GENERIC_WRITE,
        FILE_SHARE_READ |
        FILE_SHARE_WRITE,        // shared
        NULL,                    // default security attributes
        CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
        NULL);                   // reserved; must be NULL
    
    hConv1Buffer = CreateConsoleScreenBuffer(
        GENERIC_READ |           // read/write access
        GENERIC_WRITE,
        FILE_SHARE_READ |
        FILE_SHARE_WRITE,        // shared
        NULL,                    // default security attributes
        CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
        NULL);
    SetConsoleActiveScreenBuffer(hMainMenuBuffer);

}

COORD set_cursor(int X, int Y)
{
    COORD pos = { X, Y };
    return pos;
}

void thread_tick(void)
{
    while (1)
    {
        ticks++;
        Sleep(100);
    }
}

void update_screen(void)
{
    SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(0, 5)); // Move cursor to Top-Left corner of buffer
    char text_buffer[100];
    int i = 0;
    for (i = 0; i < BELT_LENGTH_U; i++)
    {
        sprintf_s(text_buffer, 100, "%d", get_belt0_element(i));
        WriteConsoleA(hMainMenuBuffer, text_buffer, strlen(text_buffer), NULL, NULL);
    }
}