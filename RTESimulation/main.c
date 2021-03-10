#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "belt.h"
#include <string.h>
#include <process.h>

int tick = 0;
int run = 1;
void tick_thread(void* pMyID);
void update_display_thread(void* pMyID);

HANDLE hStdout, hScreenBuffer;

int main(void)
{
	
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE); // Get stdout console handle
	hScreenBuffer = CreateConsoleScreenBuffer(
        GENERIC_READ |           // read/write access
        GENERIC_WRITE,
        FILE_SHARE_READ |
        FILE_SHARE_WRITE,        // shared
        NULL,                    // default security attributes
        CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
        NULL); // Creates a new screen buffer

    SetConsoleActiveScreenBuffer(hScreenBuffer); // Change current console buffer

    _beginthread(tick_thread, 0, NULL);
    _beginthread(update_display_thread, 0, NULL);

    int key = 0;
    while (run)
    {
        key = _getch();
        if (tolower(key) == 'q')
        {
            run = 0;
        }
    }

	return 0;
}

void tick_thread(void* pMyID)
{
    while (run)
    {
        tick++;
        Sleep(100);
    }
}

void update_display_thread(void* pMyID)
{
    COORD pos = { 0,0 };
    static int old_tick = 0;
    char buffer[20];
    while (run)
    {
        SetConsoleCursorPosition(hScreenBuffer, pos);
        sprintf_s(buffer, 20, "Current tick = %d", tick);
        if (tick > old_tick)
        {
            WriteConsoleA(hScreenBuffer, buffer, strlen(buffer), NULL, NULL);
            old_tick = tick;
        }
    }
}