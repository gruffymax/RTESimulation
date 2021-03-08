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

//Global variables
int LargeBlock;
int SmallBlock;


//main
int main()
{
    int a = 1;
    int b = 2;
    int c = 3;
    int choice;
    



    MENU:
    printf("Please select the option you wish to choose:\n");
    printf("[1] - Conveyor 1\n");
    printf("[2] - Conveyor 2\n");
    printf("[3] - Shutdown\n");
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
        goto MENU;
    }
}

int ConveyorOne()
{
    printf("Conveyor 1:\n");
    printf("No. Large blocks:  %d", LargeBlock);
    printf("No. Small blocks:  %d", LargeBlock);


}

int ConveyorTwo()
{

}










/*HANDLE hStdout, hNewScreenBuffer;
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

return 0;*/