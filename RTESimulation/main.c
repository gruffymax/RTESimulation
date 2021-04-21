#include <stdio.h>
#include <stdint.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <process.h>
#include "simulation.h"
#include "ui_display.h"
#include "simtasks.h"
#include "semphr.h"

//Prototypes
void thread_display(void);

//Semaphores
SEMPHR gate_open_semphr0 = NULL;
SEMPHR gate_open_semphr1 = NULL;

//Global Variables
extern uint32_t sim_tick; // Defined in simulation.h

//Variables
BOOL simulation_run = 1;
BOOL simulation_pause = 0;

//main
int main()
{
    // Initialistion
    init_screen_buffers();                              // Our function to create screen buffer handles etc
    gate_open_semphr0 = create_semphr(0);
    gate_open_semphr1 = create_semphr(0);

    _beginthread(thread_tick, 4, NULL);                 // Start the simulation ticker running
    _beginthread(thread_simulation, 16, NULL);          // Start the simulation thread
    _beginthread(thread_display, 128, NULL);
    //_beginthread(thread_task_read_sensors, 64, NULL);   // Start the "Read Sensor" Task
    //_beginthread(thread_task_gate_control, 64, NULL);   // Start the "Gate Control" task
    //_beginthread(thread_task_count_sensor, 64, NULL);   // Start the "Count Sensor" task
    init_tasks();
    start_scheduler();

    free(gate_open_semphr0);
    free(gate_open_semphr1);

}

void thread_display(void)
{
    while (simulation_run)
    {
        update_display();
        get_key_press();
        Sleep(20);
    }
}
