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
void init_screen_buffer(void);


//Global variables
int LargeBlock;
int SmallBlock;
int increment;


//main
int main()
{
    //int a = 1;
    //int b = 2;
    //int c = 3;
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

int ConveyorOne(void)
{
BLOCK:
    system("cls");
    printf("Conveyor 1:\n");
    printf("No. Large blocks:  %d\n", LargeBlock);
    printf("No. Small blocks:  %d\n", SmallBlock);
    scanf_s("%d\n", &increment);
    if (increment == 1 )
    {
        LargeBlock = LargeBlock++;
        goto BLOCK;
    }
    else if (increment == 2)
    {
        SmallBlock = SmallBlock++;
        goto BLOCK;
    }
}

int ConveyorTwo(void)
{

}


void init_screen_buffer(void)
{

}








