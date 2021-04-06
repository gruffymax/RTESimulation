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
			Sleep(10);
		}
		
		uint32_t start_time = ticks;
		uint32_t end_time = start_time + 60;
		while (ticks < end_time)
		{
			//Wait for 6 seconds
			Sleep(10);
		}

		setGates(1);

		Sleep(10);
		//TODO
	}
}