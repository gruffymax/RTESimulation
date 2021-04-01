#include "simtasks.h"
#include "cinterface.h"

extern uint32_t ticks;
extern BOOL simulation_run;
extern char* gate_open_mutex;

void thread_task_read_sensors(void)
{
	take_mutex(gate_open_mutex);
	while (simulation_run)
	{
		Sleep(10);
		//TODO
	}
}

void thread_task_gate_control(void)
{
	while (simulation_run)
	{
		while (take_mutex(gate_open_mutex) == 0)
		{
			// Wait here until mutex taken
		}
		Sleep(10);
		//TODO
	}
}