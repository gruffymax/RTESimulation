#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <process.h>
#include "simulation.h"


//prototypes
void init_screen_buffers(void);
COORD set_cursor(int X, int Y);
void update_display(void);

// Thread prototypes
void thread_tick(void);


//Global variables
extern uint32_t ticks;
extern int simulation_run;

int simulation_run = 1;
HANDLE hStdout, hMainMenuBuffer, hConv1Buffer, hStdin = NULL;

//main
int main()
{
    /* Initialistion */
    init_screen_buffers(); // Our function to create screen buffer handles etc
    _beginthread(thread_tick, 4, NULL); //Start the simulation ticker running
    _beginthread(thread_simulation, 16, NULL); //Start the simulation thread
    hStdin = GetStdHandle(STD_INPUT_HANDLE);



    uint32_t old_tick = 0;
    char key_press[16];
    int chars_out = 0;
    INPUT_RECORD irInBuff;
    DWORD fdwMode;
    BOOL res = 0;

    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    res = SetConsoleMode(hStdin, fdwMode);
    
    while (simulation_run)
    {
        if (ticks > old_tick)
        {
            update_display();
            // TODO
            res = ReadConsoleInput(hStdin, &irInBuff, 1, &chars_out, NULL);
            
            if (irInBuff.EventType == KEY_EVENT)
            {
                if (irInBuff.Event.KeyEvent.uChar.AsciiChar == 'q')
                {
                    simulation_run = 0;
                }
            }
            old_tick = ticks;
            Sleep(99);
        }
    }

    SetConsoleActiveScreenBuffer(hStdout);
    printf("Simulation exited. Goodbye\n\r");
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
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(hMainMenuBuffer, &cursor_info);

}

COORD set_cursor(int X, int Y)
{
    COORD pos = { X, Y };
    return pos;
}

void update_display(void)
{
    char text_buffer[100];
    int i;
    {
        for (i = 0; i < BELT_LENGTH_U; i++)
        {
            sprintf_s(text_buffer, 100, "%d", sim_get_belt0(i));
            SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(i, 0));
            WriteConsoleA(hMainMenuBuffer, text_buffer, strlen(text_buffer), NULL, NULL);
            sprintf_s(text_buffer, 100, "%d", sim_get_belt1(i));
            SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(i, 5));
            WriteConsoleA(hMainMenuBuffer, text_buffer, strlen(text_buffer), NULL, NULL);
        }
    }
}

/* 11111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000>
 *           ^                   ^         ^                                       ^                   ^
 *                               S         S
 *                               1         2                                       G                   C
 *
 *           v                   v         v                                       v                   v
 * 00000111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000>
 */