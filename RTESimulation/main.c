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
void mainmenu(void);
void ConveyorOne(void);
void ConveyorTwo(void);
void init_screen_buffers(void);
int Screen_Update(void);
void get_key_press(void);

COORD set_cursor(int X, int Y);
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
HANDLE hStdout, hSimulationBuffer, hSimulationBuffer, hSimulationBuffer, hStdin = NULL;
CONSOLE_SCREEN_BUFFER_INFO bufferinfo;  //added 22/03/21
DWORD cCharsWritten, dwConSize;         //added 22/03/21
COORD coordScreen = {0,0};              //added 22/03/21

//main
int main()
{
    // Initialistion
     init_screen_buffers(); // Our function to create screen buffer handles etc
    _beginthread(thread_tick, 4, NULL); //Start the simulation ticker running
    _beginthread(thread_simulation, 16, NULL); //Start the simulation thread
    hStdin = GetStdHandle(STD_INPUT_HANDLE);



    uint32_t old_tick = 0;
    INPUT_RECORD irInBuff;

    DWORD fdwMode;
    BOOL res = 0;

    fdwMode = ENABLE_WINDOW_INPUT;
    res = SetConsoleMode(hStdin, fdwMode);

    while (1)
    {
        if (ticks > old_tick)
        {
            update_display();
            get_key_press();    
            GetConsoleScreenBufferInfo(hStdout, &bufferinfo);   //-----ADDED 22/03/21----- attempt to add blank spaces
            dwConSize = bufferinfo.dwSize.X * bufferinfo.dwSize.Y;
            if (!FillConsoleOutputCharacter(hStdout,            // Handle to console screen buffer
                (TCHAR)' ',                                     // Character to write to the buffer
                dwConSize,                                      // Number of cells to write
                coordScreen,                                    // Coordinates of first cell
                &cCharsWritten))                                // Receive number of characters written 
            

            
            old_tick = ticks;
            Sleep(100);
         }

        
        /*SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 6)); // Move cursor to Top-Left corner of buffer
        sprintf_s(text_buffer, 100, "Please select the option you wish to choose:"); // Create text buffer to display
        WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

        SetConsoleCursorPosition(hSimulationBuffer, set_cursor(5, 7)); // Move cursor to a new position
        sprintf_s(text_buffer, 100, "[1] - Conveyor 1"); // Create text buffer
        WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

        SetConsoleCursorPosition(hSimulationBuffer, set_cursor(5, 8)); // Move cursor to a new position
        sprintf_s(text_buffer, 100, "[2] - Conveyor 2"); // Create text buffer
        WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

        SetConsoleCursorPosition(hSimulationBuffer, set_cursor(5, 9)); // Move cursor to a new position
        sprintf_s(text_buffer, 100, "[3] - Exit"); // Create text buffer
        WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

        SetConsoleCursorPosition(hSimulationBuffer, set_cursor(5, 10));
        scanf_s("%d", &choice);*/

    }


    /*do {
        system("cls");
        SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 0)); // Move cursor to Top-Left corner of buffer
        sprintf_s(text_buffer, 100, "Please select the option you wish to choose:"); // Create text buffer to display
        WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

        SetConsoleCursorPosition(hSimulationBuffer, set_cursor(5, 1)); // Move cursor to a new position
        sprintf_s(text_buffer, 100, "[1] - Conveyor 1"); // Create text buffer
        WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

        SetConsoleCursorPosition(hSimulationBuffer, set_cursor(5, 2)); // Move cursor to a new position
        sprintf_s(text_buffer, 100, "[2] - Conveyor 2"); // Create text buffer
        WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

        SetConsoleCursorPosition(hSimulationBuffer, set_cursor(5, 3)); // Move cursor to a new position
        sprintf_s(text_buffer, 100, "[3] - Exit"); // Create text buffer
        WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

        SetConsoleCursorPosition(hSimulationBuffer, set_cursor(5, 4));
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
void mainmenu(void)
{
    system("cls");
    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 7)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Please select the option you wish to choose:"); // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(5, 8)); // Move cursor to a new position
    sprintf_s(text_buffer, 100, "[1] - Conveyor 1"); // Create text buffer
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(5, 9)); // Move cursor to a new position
    sprintf_s(text_buffer, 100, "[2] - Conveyor 2"); // Create text buffer
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(5, 10)); // Move cursor to a new position
    sprintf_s(text_buffer, 100, "[0] - Exit"); // Create text buffer
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position


    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(5, 11));
}
void ConveyorOne(void)
{
    system("cls");
    SetConsoleActiveScreenBuffer(hSimulationBuffer);

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 7)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Conveyor 1:"); // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 8)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Large blocks:  %d", LargeBlock); // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 9)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Small blocks:  %d", SmallBlock); // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 10)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Option menu:");                                         // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);    // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 11));                            // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[1] - Main Menu");                                      // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 12));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[2] - Conveyor 2");                                    // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 13));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[0] - Stop Simulation");                                    // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 14));                           // Move cursor to Top-Left corner of buffer
}

void ConveyorTwo(void)
{
    system("cls");
    SetConsoleActiveScreenBuffer(hSimulationBuffer);

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 7));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Conveyor 2:");                                         // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 8));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Large blocks:  %d", LargeBlock);                   // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 9));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Small blocks:  %d", SmallBlock);                   // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 10));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Option menu:");                                        // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 11));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[1] - Main Menu");                                     // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 12));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[2] - Conveyor 1");                                    // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 13));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[0] - Stop Simulation");                                    // Create text buffer to display
    WriteConsoleA(hSimulationBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hSimulationBuffer, set_cursor(0, 14));                           // Move cursor to Top-Left corner of buffer
}

void get_key_press(void)
{
    INPUT_RECORD irInBuff;
    int chars_out = 0;

    GetNumberOfConsoleInputEvents(hStdin, &chars_out);
    if (chars_out != 0)
    {
        res = ReadConsoleInput(hStdin, &irInBuff, 1, &chars_out, NULL);

        if (irInBuff.EventType == KEY_EVENT && irInBuff.Event.KeyEvent.bKeyDown == 1)
        {
            switch (irInBuff.Event.KeyEvent.uChar.AsciiChar)
            {
            case '1':
                page = 1;
                break;
            case '2':
                page = 2;
                break;
            case '0':
                page = 0;
                break;
            default:
                break;
            }
        }
    }
}
void init_screen_buffers(void)
{
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    hSimulationBuffer = CreateConsoleScreenBuffer(
        GENERIC_READ |           // read/write access
        GENERIC_WRITE,
        FILE_SHARE_READ |
        FILE_SHARE_WRITE,        // shared
        NULL,                    // default security attributes
        CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
        NULL);                   // reserved; must be NULL
 
    CONSOLE_CURSOR_INFO cur = { 1, 0 };
    SetConsoleCursorInfo(hSimulationBuffer, &cur);
    SetConsoleActiveScreenBuffer(hSimulationBuffer);
}

COORD set_cursor(int X, int Y)
{
    COORD pos = { X, Y };
    return pos;
}

void update_display(void)
{
    uint32_t old_tick = 0;
    char update_buffer[100];
    int i = 0;
    SetConsoleActiveScreenBuffer(hSimulationBuffer);
    if (ticks > old_tick)
    {
        switch (page)
        {
            case 1:
                ConveyorOne();
                break;
            case 2:
                ConveyorTwo();
                break;
            case 0:
                mainmenu();
                break;
            default:
                break;
        }
        /*for (i = 0; i < BELT_LENGTH_U; i++)
        {
            sprintf_s(update_buffer, 100, "%d", sim_get_belt0(i));
            SetConsoleCursorPosition(hSimulationBuffer, set_cursor(i, 0));
            WriteConsoleA(hSimulationBuffer, update_buffer, (DWORD)strlen(update_buffer), NULL, NULL);
            sprintf_s(update_buffer, 100, "%d", sim_get_belt1(i));
            SetConsoleCursorPosition(hSimulationBuffer, set_cursor(i, 5));
            WriteConsoleA(hSimulationBuffer, update_buffer, (DWORD)strlen(update_buffer), NULL, NULL);
        }*/
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
HANDLE hStdout, hSimulationBuffer, hSimulationBuffer, hStdin = NULL;

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

    hSimulationBuffer = CreateConsoleScreenBuffer(
        GENERIC_READ |           // read/write access
        GENERIC_WRITE,
        FILE_SHARE_READ |
        FILE_SHARE_WRITE,        // shared
        NULL,                    // default security attributes
        CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
        NULL);                   // reserved; must be NULL

    hSimulationBuffer = CreateConsoleScreenBuffer(
        GENERIC_READ |           // read/write access
        GENERIC_WRITE,
        FILE_SHARE_READ |
        FILE_SHARE_WRITE,        // shared
        NULL,                    // default security attributes
        CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
        NULL);
    SetConsoleActiveScreenBuffer(hSimulationBuffer);
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(hSimulationBuffer, &cursor_info);

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
            SetConsoleCursorPosition(hSimulationBuffer, set_cursor(i, 0));
            WriteConsoleA(hSimulationBuffer, text_buffer, strlen(text_buffer), NULL, NULL);
            sprintf_s(text_buffer, 100, "%d", sim_get_belt1(i));
            SetConsoleCursorPosition(hSimulationBuffer, set_cursor(i, 5));
            WriteConsoleA(hSimulationBuffer, text_buffer, strlen(text_buffer), NULL, NULL);
        }
    }
}

*/
