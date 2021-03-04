#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include "belt.h"

int main(void)
{
    HANDLE hStdout, hNewScreenBuffer;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    hNewScreenBuffer = CreateConsoleScreenBuffer(
        GENERIC_READ |           // read/write access
        GENERIC_WRITE,
        FILE_SHARE_READ |
        FILE_SHARE_WRITE,        // shared
        NULL,                    // default security attributes
        CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
        NULL);                   // reserved; must be NULL

    COORD pos = { 5, 2 };

    char buffer[50];
    strcpy_s(buffer, 50, "Hello World");
    SetConsoleCursorPosition(hNewScreenBuffer, pos);
    WriteConsoleA(hNewScreenBuffer, buffer, strlen(buffer), NULL, NULL);

    getch();

    SetConsoleActiveScreenBuffer(hNewScreenBuffer);

    getch();
    SetConsoleActiveScreenBuffer(hStdout);

    return 0;
}