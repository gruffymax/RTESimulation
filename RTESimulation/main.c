#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <process.h>
#include "simulation.h"


//Prototypes
void mainmenu(void);
void ConveyorOne(void);
void ConveyorTwo(void);
void init_screen_buffers(void);
void get_key_press(void);
void update_display(void);
void clear_display(HANDLE hbuffer);
COORD set_cursor(int X, int Y);

//Thread Prototypes
void thread_tick(void);

//Global Variables
extern uint32_t ticks;
extern int simulation_run;
extern int simulation_pause;

//Variables
int simulation_run = 1;
int simulation_pause = 0;
int LargeBlock;
int SmallBlock;
int increment;
int page;
int choice;
char text_buffer[200];
char Stopchoice[50];
HANDLE hStdout, hBackgroundBuffer, hDisplayBuffer, hStdin = NULL;


//main
int main()
{
    // Initialistion
    init_screen_buffers(); // Our function to create screen buffer handles etc
    _beginthread(thread_tick, 4, NULL); //Start the simulation ticker running
    _beginthread(thread_simulation, 16, NULL); //Start the simulation thread
    hStdin = GetStdHandle(STD_INPUT_HANDLE); // Get the stdin handle so we can get key presses

    while (simulation_run)
    {
        update_display();
        get_key_press();
        Sleep(20);
    }
}
void mainmenu(void)
{
    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 7)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Please select the option you wish to choose:"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(5, 8)); // Move cursor to a new position
    sprintf_s(text_buffer, 100, "[1] - Conveyor 1"); // Create text buffer
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(5, 9)); // Move cursor to a new position
    sprintf_s(text_buffer, 100, "[2] - Conveyor 2"); // Create text buffer
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(5, 10)); // Move cursor to a new position
    sprintf_s(text_buffer, 100, "[0] - Main Menu"); // Create text buffer
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(5, 11));
}
void ConveyorOne(void)
{
    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 7)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Conveyor 1:"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 8)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Large blocks:  %d", LargeBlock); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 9)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Small blocks:  %d", SmallBlock); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 10)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Option menu:");                                         // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);    // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 11));                            // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[0] - Main Menu");                                      // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 12));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[2] - Conveyor 2");                                    // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 13));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[q] - Stop Simulation");                                    // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 14));                           // Move cursor to Top-Left corner of buffer
}

void ConveyorTwo(void)
{
    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 7));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Conveyor 2:");                                         // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 8));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Large blocks:  %d", LargeBlock);                   // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 9));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Small blocks:  %d", SmallBlock);                   // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 10));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Option menu:");                                        // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 11));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[0] - Main Menu");                                     // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 12));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[1] - Conveyor 1");                                    // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 13));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[q] - Stop Simulation");                                    // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 14));                           // Move cursor to Top-Left corner of buffer
}

void get_key_press(void)
{
    BOOL res;
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
            case 'p':
                if (simulation_pause)
                {
                    simulation_pause = 0;
                }
                else
                {
                    simulation_pause = 1;
                }
                break;
            case 'q':
                simulation_run = 0;
                break;
            default:
                break;
            }
        }
    }
}
void init_screen_buffers(void)
{
    BOOL res = 0;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD fdwMode = ENABLE_WINDOW_INPUT;
    res = SetConsoleMode(hStdin, fdwMode);

    hBackgroundBuffer = CreateConsoleScreenBuffer(
        GENERIC_READ |           // read/write access
        GENERIC_WRITE,
        FILE_SHARE_READ |
        FILE_SHARE_WRITE,        // shared
        NULL,                    // default security attributes
        CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
        NULL);                   // reserved; must be NULL

    hDisplayBuffer = CreateConsoleScreenBuffer(
        GENERIC_READ |           // read/write access
        GENERIC_WRITE,
        FILE_SHARE_READ |
        FILE_SHARE_WRITE,        // shared
        NULL,                    // default security attributes
        CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE
        NULL);                   // reserved; must be NULL

    CONSOLE_CURSOR_INFO cur = { 1, 0 };
    SetConsoleCursorInfo(hDisplayBuffer, &cur);
    SetConsoleCursorInfo(hBackgroundBuffer, &cur);
    SetConsoleActiveScreenBuffer(hDisplayBuffer);
}

void clear_display(HANDLE hbuffer)
{
    CONSOLE_SCREEN_BUFFER_INFO bufferinfo;  //added 22/03/21
    DWORD cCharsWritten, dwConSize;         //added 22/03/21
    COORD coordScreen = { 0,0 };              //added 22/03/21

    GetConsoleScreenBufferInfo(hbuffer, &bufferinfo);   //-----ADDED 22/03/21----- attempt to add blank spaces
    dwConSize = bufferinfo.dwSize.X * bufferinfo.dwSize.Y;
    if (!FillConsoleOutputCharacter(hbuffer,            // Handle to console screen buffer
        (TCHAR)' ',                                     // Character to write to the buffer
        dwConSize,                                      // Number of cells to write
        coordScreen,                                    // Coordinates of first cell
        &cCharsWritten))                                // Receive number of characters written 
    {
        while (1); //Error occured, halt here
    }

}

COORD set_cursor(int X, int Y)
{
    COORD pos = { X, Y };
    return pos;
}

void update_display(void)
{
    /* Variables */
    CONSOLE_SCREEN_BUFFER_INFO bufferinfo;
    GetConsoleScreenBufferInfo(hDisplayBuffer, &bufferinfo);
    SMALL_RECT srcRect = { 0, 0, bufferinfo.dwSize.X - 1, bufferinfo.dwSize.Y - 1 };
    int display_size = bufferinfo.dwSize.X * bufferinfo.dwSize.Y * sizeof(CHAR_INFO);
    CHAR_INFO *chiBuffer = malloc(display_size);
    COORD coordBufsize = { bufferinfo.dwSize.X, bufferinfo.dwSize.Y };
    COORD coordBufCoord = { 0, 0 };
    char update_buffer[110] = { 0 };
    int i = 0;

    clear_display(hBackgroundBuffer);
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
    
    for (i = 0; i < BELT_LENGTH_U; i++)
    {
        sprintf_s(update_buffer, 100, "%d", sim_get_belt0(i));
        SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(i + 4, 0));
        WriteConsoleA(hBackgroundBuffer, update_buffer, (DWORD)strlen(update_buffer), NULL, NULL);

        sprintf_s(update_buffer, 100, "%d", sim_get_belt1(i));
        SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(i + 4, 5));
        WriteConsoleA(hBackgroundBuffer, update_buffer, (DWORD)strlen(update_buffer), NULL, NULL);
    }

    ReadConsoleOutput(hBackgroundBuffer, chiBuffer, coordBufsize, coordBufCoord, &srcRect); //Copy background screen buffer
    WriteConsoleOutput(hDisplayBuffer, chiBuffer, coordBufsize, coordBufCoord, &srcRect);   //Paste screen onto disply buffer
    
    free(chiBuffer); //Free up memory
}

