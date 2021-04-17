#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdint.h>
#include <process.h>
#include <windows.h>
#include "belt.h"
#include "motor.h"
#include "gates.h"

enum task_state_e {Ready, Running, Suspended, Blocked};

struct task_queue_s
{
	void (*fp_task)(void); // Function pointer to the task
	int id;
	char* name;
	int priority; 
	enum task_state_e state; //Current state of the task
} task[3];

void start_scheduler(void);
void init_tasks(void);

void thread_tick(void);
void thread_simulation(void);
char sim_get_belt0(uint16_t element);
char sim_get_belt1(uint16_t element);
void stop_simulation(void);
void run_simulation(void);
void thread_task_read_sensors(void);


#endif // SIMULATION_H
