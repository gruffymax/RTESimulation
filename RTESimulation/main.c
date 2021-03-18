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
char grab_key_presses(void);
BOOL update_system_state(char key_press);

// Thread prototypes
void thread_tick(void);


//Global variables
extern uint32_t ticks;
extern int simulation_run;
extern int simulation_pause;

int simulation_run = 1;
int simulation_pause = 0;

HANDLE hStdout, hMainMenuBuffer, hConv1Buffer, hStdin = NULL;

//main
int main()
{
    uint32_t old_tick = 0;

    /* Initialistion */
    init_screen_buffers(); // Our function to create screen buffer handles etc
    /* Start Threads */
    _beginthread(thread_tick, 4, NULL); //Start the simulation ticker running
    _beginthread(thread_simulation, 16, NULL); //Start the simulation thread
    
    while (simulation_run)
    {
        if (ticks > old_tick)
        {
            update_display();

            old_tick = ticks;
            
        }
        update_system_state(grab_key_presses());
        Sleep(100);
    }

    SetConsoleActiveScreenBuffer(hStdout);
    printf("Simulation exited. Goodbye\n\r");
}
void init_screen_buffers(void)
{
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD fdwMode = ENABLE_WINDOW_INPUT;
    BOOL res = 0;

    res = SetConsoleMode(hStdin, fdwMode); //Configure StdIn to accept keypresses only
    
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

char grab_key_presses(void)
{
    BOOL res = 0;
    int chars_out = 0;
    INPUT_RECORD irInBuff[100];

    GetNumberOfConsoleInputEvents(hStdin, &chars_out);
    if (chars_out != 0)
    {
        res = ReadConsoleInput(hStdin, irInBuff, 100, &chars_out, NULL);

        for (int i = 0; i < chars_out; i++)
        {
            if (irInBuff[i].EventType == KEY_EVENT && irInBuff[i].Event.KeyEvent.bKeyDown == 1)
            {
                return irInBuff[i].Event.KeyEvent.uChar.AsciiChar;
            }
        }
    }
    return 0;
}

BOOL update_system_state(char key_press)
{
    switch (key_press)
    {
        case 'q':
            simulation_run = 0;
            break;

        case 'p':
            if (simulation_pause == 0)
            {
                simulation_pause = 1;
            }
            else
            {
                simulation_pause = 0;
            }
            break;

        default:
            break;
    }
    return 1;
}

/* 11111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000>
 *           ^                   ^         ^                                       ^                   ^
 *                               S         S
 *                               1         2                                       G                   C
 *
 *           v                   v         v                                       v                   v
 * 00000111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000>
 */