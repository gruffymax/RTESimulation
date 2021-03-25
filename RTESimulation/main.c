#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <process.h>
#include "simulation.h"


//Global Variables
extern uint32_t ticks; // Defined in simulation.h

//Variables
int simulation_run = 1;
int simulation_pause = 0;

//main
int main()
{
    // Initialistion
    init_screen_buffers(); // Our function to create screen buffer handles etc
    _beginthread(thread_tick, 4, NULL); //Start the simulation ticker running
    _beginthread(thread_simulation, 16, NULL); //Start the simulation thread
    

    while (simulation_run)
    {
        update_display();
        get_key_press();
        Sleep(20);
    }
}


