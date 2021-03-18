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
int ConveyorOne();
int ConveyorTwo();
void init_screen_buffers();
int Screen_Update();

COORD set_cursor(int X, int Y);
INPUT_RECORD irInBuff;
DWORD fdwMode;
BOOL res = 0;
void update_display(void);

//thread prototypes
void thread_tick(void);

//Global variables
extern uint32_t ticks;
extern int simulation_run;

int simulation_run = 1;
int LargeBlock;
int SmallBlock;
int increment;
int page;
int choice;
char text_buffer[200];
char Stopchoice[50];
HANDLE hStdout, hMainMenuBuffer, hConv1Buffer, hConv2Buffer, hStdin = NULL;

/*initialisation*/




//main
int main()
{
    // Initialistion
     init_screen_buffers(); // Our function to create screen buffer handles etc
    _beginthread(thread_tick, 4, NULL); //Start the simulation ticker running
    _beginthread(thread_simulation, 16, NULL); //Start the simulation thread
    hStdin = GetStdHandle(STD_INPUT_HANDLE);



    uint32_t old_tick = 0;
    char key_press[16];
    int chars_out = 0;
    INPUT_RECORD irInBuff;
    INPUT_RECORD NewBuff;
    DWORD fdwMode;
    BOOL res = 0;

    fdwMode = ENABLE_WINDOW_INPUT;
    res = SetConsoleMode(hStdin, fdwMode);

    while (1)
    {
        if (ticks > old_tick)
        {
            update_display();
            SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(0, 7)); // Move cursor to Top-Left corner of buffer
            sprintf_s(text_buffer, 100, "Please select the option you wish to choose:"); // Create text buffer to display
            WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

            SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 8)); // Move cursor to a new position
            sprintf_s(text_buffer, 100, "[1] - Conveyor 1"); // Create text buffer
            WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

            SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 9)); // Move cursor to a new position
            sprintf_s(text_buffer, 100, "[2] - Conveyor 2"); // Create text buffer
            WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

            SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 10)); // Move cursor to a new position
            sprintf_s(text_buffer, 100, "[3] - Exit"); // Create text buffer
            WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

            SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 11));
            // TODO
            GetNumberOfConsoleInputEvents(hStdin, &chars_out);
            if (chars_out != 0)
            {
                res = ReadConsoleInput(hStdin, &irInBuff, 1, &chars_out, NULL);

                if (irInBuff.EventType == KEY_EVENT )
                {
                    if (irInBuff.Event.KeyEvent.uChar.AsciiChar == 'q')
                    {
                        page = 1;
                        system("cls");
                        SetConsoleActiveScreenBuffer(hConv1Buffer);

                        SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 7)); // Move cursor to Top-Left corner of buffer
                        sprintf_s(text_buffer, 100, "Conveyor 1:"); // Create text buffer to display
                        WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

                        SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 8)); // Move cursor to Top-Left corner of buffer
                        sprintf_s(text_buffer, 100, "No. Large blocks:  %d", LargeBlock); // Create text buffer to display
                        WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

                        SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 9)); // Move cursor to Top-Left corner of buffer
                        sprintf_s(text_buffer, 100, "No. Small blocks:  %d", SmallBlock); // Create text buffer to display
                        WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

                        SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 10)); // Move cursor to Top-Left corner of buffer
                        sprintf_s(text_buffer, 100, "Option menu:");                                         // Create text buffer to display
                        WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);    // Put text buffer onto screen at the cursor position.

                        SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 11));                            // Move cursor to Top-Left corner of buffer
                        sprintf_s(text_buffer, 100, "[1] - Main Menu");                                      // Create text buffer to display
                        WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

                        SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 12));                           // Move cursor to Top-Left corner of buffer
                        sprintf_s(text_buffer, 100, "[2] - Conveyor 2");                                    // Create text buffer to display
                        WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

                        SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 13));                           // Move cursor to Top-Left corner of buffer
                        sprintf_s(text_buffer, 100, "[3] - Stop Simulation");                                    // Create text buffer to display
                        WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

                        SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 14));                           // Move cursor to Top-Left corner of buffer
                    }
                }
            }
            old_tick = ticks;
            Sleep(99);
        }

        
        /*SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(0, 6)); // Move cursor to Top-Left corner of buffer
        sprintf_s(text_buffer, 100, "Please select the option you wish to choose:"); // Create text buffer to display
        WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

        SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 7)); // Move cursor to a new position
        sprintf_s(text_buffer, 100, "[1] - Conveyor 1"); // Create text buffer
        WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

        SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 8)); // Move cursor to a new position
        sprintf_s(text_buffer, 100, "[2] - Conveyor 2"); // Create text buffer
        WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

        SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 9)); // Move cursor to a new position
        sprintf_s(text_buffer, 100, "[3] - Exit"); // Create text buffer
        WriteConsoleA(hMainMenuBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

        SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 10));
        scanf_s("%d", &choice);*/

    }


    /*do {
        system("cls");
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
            fflush(stdin);
            system("cls");
            return ConveyorOne();
        }
        else if (choice == 2)
        {
            fflush(stdin);
            system("cls");
            return ConveyorTwo();
        }
        else if (choice == 3)
        {
            fflush(stdin);
            return 0;
        }
    } while (choice != 1 || choice != 2 || choice != 3); //Do while loop to handle wrong integer inputs*/
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

    SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 8));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[3] - Stop Simulation");                                    // Create text buffer to display
    WriteConsoleA(hConv1Buffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 9));                           // Move cursor to Top-Left corner of buffer
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
        update_display();
    }
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
    BOOL UpdateWindow(
        HWND hWnd
    );

    
    SetConsoleActiveScreenBuffer(hMainMenuBuffer);
}

COORD set_cursor(int X, int Y)
{
    COORD pos = { X, Y };
    return pos;
}

void update_display()
{
    uint32_t old_tick = 0;
    char update_buffer[100];
    int i = 0;
    SetConsoleActiveScreenBuffer(hMainMenuBuffer);
    UpdateWindow(hMainMenuBuffer);
    if (ticks > old_tick)
    {
        for (i = 0; i < BELT_LENGTH_U; i++)
        {
            sprintf_s(update_buffer, 100, "%d", sim_get_belt0(i));
            SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(i, 0));
            WriteConsoleA(hMainMenuBuffer, update_buffer, (DWORD)strlen(update_buffer), NULL, NULL);
            sprintf_s(update_buffer, 100, "%d", sim_get_belt1(i));
            SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(i, 5));
            WriteConsoleA(hMainMenuBuffer, update_buffer, (DWORD)strlen(update_buffer), NULL, NULL);
        }
    }
    old_tick = ticks;
}


int Screen_Update()
{

}

/* 11111111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000>
 *           ^                   ^         ^                                       ^                   ^
 *                               S         S
 *                               1         2                                       G                   C
 *
 *           v                   v         v                                       v                   v
 * 00000111110000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000>
 */
/*
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
    / Initialistion 
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

    fdwMode = ENABLE_WINDOW_INPUT;
    res = SetConsoleMode(hStdin, fdwMode);

    while (simulation_run)
    {
        if (ticks > old_tick)
        {
            update_display();
            // TODO
            GetNumberOfConsoleInputEvents(hStdin, &chars_out);
            if (chars_out != 0)
            {
                res = ReadConsoleInput(hStdin, &irInBuff, 1, &chars_out, NULL);

                if (irInBuff.EventType == KEY_EVENT)
                {
                    if (irInBuff.Event.KeyEvent.uChar.AsciiChar == 'q')
                    {
                        simulation_run = 0;
                    }
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

*/
