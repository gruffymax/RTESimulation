#include "ui_display.h"
#include <string.h>
#include <stdio.h>
#include "simulation.h"
#include <windows.h>

/* Global Variables */
extern int simulation_run;
extern int simulation_pause;

/* Variables */
HANDLE hStdout, hBackgroundBuffer, hDisplayBuffer, hStdin = NULL;
char text_buffer[200];
int page;
int LargeBlock0;
int LargeBlock1;
int SmallBlock0;
int SmallBlock1;

void mainmenu(void)
{
    /*MAIN MENU OPTIONS*/
    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(0, 7)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Please select the option you wish to choose:"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(5, 8)); // Move cursor to a new position
    sprintf_s(text_buffer, 100, "[1] - Conveyor 1 & 2"); // Create text buffer
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(5, 9)); // Move cursor to a new position
    sprintf_s(text_buffer, 100, "[p] - Pause Simulation"); // Create text buffer
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(5, 10)); // Move cursor to a new position
    sprintf_s(text_buffer, 100, "[q] - Stop Simulation"); // Create text buffer
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(33, 1)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "^"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(33, 2)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "s1"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(33, 4)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "v"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(43, 1)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "^"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(43, 2)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "s2"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(43, 4)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "v"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(83, 1)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "^"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(83, 2)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "G"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(83, 4)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "v"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(103, 1)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "^"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(103, 2)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "CS"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(103, 4)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "v"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(103, 4)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "v"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);
    
    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(114, 0)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, ">>END"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(114, 5)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, ">>END"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(5, 11));
}

void Conveyor(void)
{
    int x1 = 0;
    int x2 = 80;
    int y1 = 7;

    /*CONVEYOR 1 PRINTING*/
    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(x1, y1)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Conveyor 1:"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(x1, y1+1)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Large blocks:  %d", LargeBlock0); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(x1, y1+2)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Small blocks:  %d", SmallBlock0); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.
    
    /*OPTION MENU*/
    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(x1 + 40, y1+3)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Simulation: ");                                         // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);    // Put text buffer onto screen at the cursor position.
    if (simulation_pause)
    {
        strcpy_s(text_buffer, 100, "Paused");
    }
    else
    {
        strcpy_s(text_buffer, 100, "Running");
    }
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);    // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(x1+40, y1+5)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Option menu:");                                         // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);    // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(x1+40, y1+6));                            // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[0] - Main Menu");                                      // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);
    
    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(x1+40, y1+7));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[p] - Pause Simulation");                                    // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(x1+40, y1+8));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "[q] - Stop Simulation");                                    // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(x1, y1+9));                           // Move cursor to Top-Left corner of buffer
   
   /*CONVEYOR 2 PRINTING*/
    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(x2, y1));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Conveyor 2:");                                         // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(x2, y1+1));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Large blocks:  %d", LargeBlock1);                   // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(x2, y1+2));                           // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Small blocks:  %d", SmallBlock1);                   // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);   // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(x2, y1+7));                           // Move cursor to Top-Left corner of buffer

   /*CONVEYOR MARKS*/
    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(33, 1)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "^"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(33, 2)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "s1"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(33, 4)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "v"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(43, 1)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "^"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(43, 2)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "s2"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(43, 4)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "v"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(83, 1)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "^"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(83, 2)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "G"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(83, 4)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "v"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(103, 1)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "^"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(103, 2)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "CS"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(103, 4)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "v"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(103, 4)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "v"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(114, 0)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, ">>END"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);

    SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(114, 5)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, ">>END"); // Create text buffer to display
    WriteConsoleA(hBackgroundBuffer, text_buffer, (DWORD)strlen(text_buffer), NULL, NULL);
}

void get_key_press(void)
{
    BOOL res;
    INPUT_RECORD irInBuff;
    int chars_out = 0;

    GetNumberOfConsoleInputEvents(hStdin, &chars_out);
    if (chars_out != 0)
    {
        res = ReadConsoleInput(hStdin, &irInBuff, 1, &chars_out);

        if (irInBuff.EventType == KEY_EVENT && irInBuff.Event.KeyEvent.bKeyDown == 1)
        {
            switch (irInBuff.Event.KeyEvent.uChar.AsciiChar)
            {
            case '1':
                page = 1;
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
    hStdin = GetStdHandle(STD_INPUT_HANDLE); // Get the stdin handle so we can get key presses
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
    /* VARIABLES */
    CONSOLE_SCREEN_BUFFER_INFO bufferinfo;
    GetConsoleScreenBufferInfo(hDisplayBuffer, &bufferinfo);
    SMALL_RECT srcRect = { 0, 0, bufferinfo.dwSize.X - 1, bufferinfo.dwSize.Y - 1 };
    int display_size = bufferinfo.dwSize.X * bufferinfo.dwSize.Y * sizeof(CHAR_INFO);
    CHAR_INFO* chiBuffer = malloc(display_size);
    COORD coordBufsize = { bufferinfo.dwSize.X, bufferinfo.dwSize.Y };
    COORD coordBufCoord = { 0, 0 };
    char update_buffer[110] = { 0 };
    int i = 0;

    clear_display(hBackgroundBuffer);
    switch (page)
    {
    case 1:
        Conveyor();
        break;
    case 0:
        mainmenu();
        break;
    default:
        break;
    }

        for (i = 0; i < BELT_LENGTH_U; i++)
        {
            if (i == GATE_POS && get_gate0() == 1)
            {
                // Gate is closed
                strcpy_s(update_buffer, 100, "|");
                SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(i + 3, 0));
                WriteConsoleA(hBackgroundBuffer, update_buffer, (DWORD)strlen(update_buffer), NULL, NULL); 
            }
            else
            {
                // Gate is open
                sprintf_s(update_buffer, 100, "%d", sim_get_belt0(i));
                SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(i + 3, 0));
                WriteConsoleA(hBackgroundBuffer, update_buffer, (DWORD)strlen(update_buffer), NULL, NULL);
            }
            
            if (i == GATE_POS && get_gate1() == 1)
            {
                // Gate is closed
                strcpy_s(update_buffer, 100, "|");
                SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(i + 3, 5));
                WriteConsoleA(hBackgroundBuffer, update_buffer, (DWORD)strlen(update_buffer), NULL, NULL);
            }
            else
            {
                // Gate is open
                sprintf_s(update_buffer, 100, "%d", sim_get_belt1(i));
                SetConsoleCursorPosition(hBackgroundBuffer, set_cursor(i + 3, 5));
                WriteConsoleA(hBackgroundBuffer, update_buffer, (DWORD)strlen(update_buffer), NULL, NULL);
            }
            
        }
    
    ReadConsoleOutput(hBackgroundBuffer, chiBuffer, coordBufsize, coordBufCoord, &srcRect); //Copy background screen buffer
    WriteConsoleOutput(hDisplayBuffer, chiBuffer, coordBufsize, coordBufCoord, &srcRect);   //Paste screen onto disply buffer

    free(chiBuffer); //Free up memory
}
