#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
//#include "belt.h"


//prototypes
int ConveyorOne();
int ConveyorTwo();
void init_screen_buffers(void);
COORD set_cursor(int X, int Y);


//Global variables
int LargeBlock;
int SmallBlock;
int increment;
HANDLE hStdout, hMainMenuBuffer, hConv1Buffer;

//main
int main()
{
    init_screen_buffers(); // Our function to create scfreen buffer handles etc
    
    int choice;
    char text_buffer[100];

    SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(0,0)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Please select the option you wish to choose:"); // Create text buffer to display
    WriteConsoleA(hMainMenuBuffer, text_buffer, strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.
    
    SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5,1)); // Move cursor to a new position
    sprintf_s(text_buffer, 100, "[1] - Conveyor 1"); // Create text buffer
    WriteConsoleA(hMainMenuBuffer, text_buffer, strlen(text_buffer), NULL, NULL); // Put text buffer to new cursor position

    SetConsoleCursorPosition(hMainMenuBuffer, set_cursor(5, 2));

    //printf("[2] - Conveyor 2\n");
    //printf("[3] - Shutdown\n");
    scanf_s("%d", &choice);
    

    if (choice == 1)
    {
       // system("cls");
        //printf("1");
        ConveyorOne();
    }
    else if (choice == 2)
    {
        system("cls");
        printf("2");
    }
    else if (choice == 3)
    {
        system("cls");
        printf("3");
    }
    else
    {
        printf("Wrong input\n");
        system("cls");
    }
}

int ConveyorOne(void)
{
    char text_buffer[100];
    SetConsoleActiveScreenBuffer(hConv1Buffer);

    SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 0)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "Conveyor 1:"); // Create text buffer to display
    WriteConsoleA(hConv1Buffer, text_buffer, strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 1)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Large blocks:  %d", LargeBlock); // Create text buffer to display
    WriteConsoleA(hConv1Buffer, text_buffer, strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    SetConsoleCursorPosition(hConv1Buffer, set_cursor(0, 2)); // Move cursor to Top-Left corner of buffer
    sprintf_s(text_buffer, 100, "No. Small blocks:  %d", SmallBlock); // Create text buffer to display
    WriteConsoleA(hConv1Buffer, text_buffer, strlen(text_buffer), NULL, NULL); // Put text buffer onto screen at the cursor position.

    //printf("Conveyor 1:\n");
    //printf("No. Large blocks:  %d", LargeBlock);
    //printf("No. Small blocks:  %d", SmallBlock);


    system("cls");
    printf("Conveyor 1:\n");
    printf("No. Large blocks:  %d\n", LargeBlock);
    printf("No. Small blocks:  %d\n", SmallBlock);
    scanf_s("%d\n", &increment);
    if (increment == 1 )
    {
        LargeBlock = LargeBlock++;
      
    }
    else if (increment == 2)
    {
        SmallBlock = SmallBlock++;
        
    }
}

int ConveyorTwo(void)
{
    
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