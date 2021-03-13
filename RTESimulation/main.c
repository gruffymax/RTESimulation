#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
//#include <process.h>
//#include "simulation.h"


//prototypes
int ConveyorOne();
int ConveyorTwo();
void init_screen_buffers(void);
int Stop();
COORD set_cursor(int X, int Y);
//void update_display(void);


//Global variables
//extern uint32_t ticks;
//extern int simulation_run;

//int simulation_run = 1;
int LargeBlock;
int SmallBlock;
int increment;
int choice;
int choice;
char text_buffer[200];
char Stopchoice[50];
HANDLE hStdout, hMainMenuBuffer, hConv1Buffer, hConv2Buffer, hStopBuffer;

//main
int main()
{
    init_screen_buffers();
    do {
        //system("cls");
        SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(0, 0)); // Move cursor to Top-Left corner of buffer
        sprintf_s(text_buffer, 100, "Please select the option you wish to choose:"); // Create text buffer to display
        WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

        SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 1)); // Move cursor to a new position
        sprintf_s(text_buffer, 100, "[1] - Conveyor 1"); // Create text buffer
        WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

        SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 2)); // Move cursor to a new position
        sprintf_s(text_buffer, 100, "[2] - Conveyor 2"); // Create text buffer
        WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

        SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 3)); // Move cursor to a new position
        sprintf_s(text_buffer, 100, "[3] - Exit"); // Create text buffer
        WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

        SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 4));
        scanf_s("%d", &choice);

        if (choice == 1)
        {
            //system("cls");
            //printf("1");
            ConveyorOne();
        }
        else if (choice == 2)
        {
            //system("cls");
            ConveyorTwo();
        }
        else if (choice == 3)
        {
            return 0;
        }
    } while (choice != 1 || choice != 2 || choice != 3); //Do while loop to handle wrong integer inputs
}

int ConveyorOne()
{
    SetConsoleActiveScreenBuffer(hConv1Buffer);

    SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 0)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Conveyor 1:"); // Create text buffer to display
    WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 1)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Large blocks:  %d", LargeBlock); // Create text buffer to display
    WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 2)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Small blocks:  %d", SmallBlock); // Create text buffer to display
    WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 5)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Option menu:");                                         // Create text buffer to display
    WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);    // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 6));                            // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[1] - Main Menu");                                      // Create text buffer to display
    WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 7));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[2] - Conveyor 2");                                    // Create text buffer to display
    WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 7));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[3] - Stop Simulation");                                    // Create text buffer to display
    WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 8));                           // Move cursor to Top-Left corner of buffer
    scanf_s("%d", &choice);
    if (choice == 1)
    {
        return main();
    }
    else if (choice == 2)
    {
        return ConveyorTwo();
    }
    else if (choice == 3)
    {
        return 0;
    }
    
   


        //printf("Conveyor 1:\n");
        //printf("No. Large blocks:  %d", LargeBlock);
        //printf("No. Small blocks:  %d", SmallBlock);


       // system("cls");
       //printf("Conveyor 1:\n");
       // printf("No. Large blocks:  %d\n", LargeBlock);
       // printf("No. Small blocks:  %d\n", SmallBlock);
        return 0;
}

int ConveyorTwo()
{
    SetConsoleActiveScreenBuffer(hConv2Buffer);

    SetConsoleCursorPosition(hConv2Buffer, set_cursor(0, 0));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Conveyor 2:");                                         // Create text buffer to display
    WriteConsoleA(hConv2Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hConv2Buffer, set_cursor(0, 1));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Large blocks:  %d", LargeBlock);                   // Create text buffer to display
    WriteConsoleA(hConv2Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hConv2Buffer, set_cursor(0, 2));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Small blocks:  %d", SmallBlock);                   // Create text buffer to display
    WriteConsoleA(hConv2Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hConv2Buffer, set_cursor(0, 5));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Option menu:");                                        // Create text buffer to display
    WriteConsoleA(hConv2Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hConv2Buffer, set_cursor(0, 6));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[1] - Main Menu");                                     // Create text buffer to display
    WriteConsoleA(hConv2Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hConv2Buffer, set_cursor(0, 7));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[2] - Conveyor 1");                                    // Create text buffer to display
    WriteConsoleA(hConv2Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hConv2Buffer, set_cursor(0, 8));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[3] - Stop Simulation");                                    // Create text buffer to display
    WriteConsoleA(hConv2Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hConv2Buffer, set_cursor(0, 9));                           // Move cursor to Top-Left corner of buffer
    scanf_s("%d", &choice);

    if (choice == 1)
    {
       return main();     
    }
    else if (choice == 2)
    {
        return ConveyorOne();
    }
    else if (choice == 3)
    {
        return 0;
    }
    return 0;
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
  
    hConv2Buffer = CreateConsoleScreenBuffer(
        GENERIC_READ |           // read/write access
        GENERIC_WRITE,
        FILE_SHARE_READ |
        FILE_SHARE_WRITE,        // shared
        NULL,                    // default security attributes
        CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
        NULL);
    
    hStopBuffer = CreateConsoleScreenBuffer(
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





/*void update_display(void)
{
    uint32_t old_tick = 0;
    char text_buffer[100];
    int i = 0;
    if (ticks > old_tick)
    {
        for (i = 0; i < BELT_LENGTH_U; i++)
        {
            sprintf_s(text_buffer, 100, "%d", sim_get_belt0(i));
            SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(i, 0));
            WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);
            sprintf_s(text_buffer, 100, "%d", sim_get_belt1(i));
            SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(i, 5));
            WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);
        }
    }
    old_tick = ticks;
}*/

/* 11111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000>
 *           ^                   ^         ^                                       ^                   ^
 *                               S         S
 *                               1         2                                       G                   C
 *
 *           v                   v         v                                       v                   v
 * 00000111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000>
 */