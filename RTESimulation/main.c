#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>
#include "simulation.h"
#include "ui_display.h"
#include "simtasks.h"


//Semaphores
HANDLE semphr_gate_0;
HANDLE semphr_gate_1;

//Global Variables
extern uint32_t ticks; // Defined in simulation.h

//Variables
BOOL simulation_run = 1;
BOOL simulation_pause = 0;

//main
int main()
{

    // Initialistion
    init_screen_buffers();                              // Our function to create screen buffer handles etc
    semphr_gate_0 = CreateSemaphore(NULL, 0, 1, NULL);  // Create a semaphore for gate 0. Starting at 0
    semphr_gate_1 = CreateSemaphore(NULL, 0, 1, NULL);  // Create a semaphore for gate 1. Starting at 0

    _beginthread(&thread_simulation, 16, NULL);          // Start the simulation thread
    _beginthread(&thread_task_read_sensors, 64, NULL);   // Start the "Read Sensor" Task
    _beginthread(&thread_task_gate_control, 64, NULL);   // Start the "Gate Control" task
    _beginthread(&thread_task_count_sensor, 64, NULL);   // Start the "Count Sensor" task
    
    while (simulation_run)
    {
        update_display();
        get_key_press();
        Sleep(20);
    }
}


