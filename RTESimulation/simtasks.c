#include "simtasks.h"
#include "cinterface.h"


extern uint32_t ticks;
extern BOOL simulation_run;
extern BOOL simulation_pause;
extern char* gate_open_mutex;

void thread_task_read_sensors(void)
{
	
	while (simulation_run)
	{
		char sensor0;
		char sensor1;
		if (!simulation_pause)
		{
			resetSizeSensors(0);
			resetSizeSensors(1);
			sensor0 = readSizeSensors(0);
			sensor1 = readSizeSensors(1);

			while (sensor0 == 1)
			{
				resetSizeSensors(0);
				sensor0 = readSizeSensors(0);
				Sleep(10);
			}
			if (sensor0 == 0)
			{
				//Small block
			}
			else if (sensor0 == 3)
			{
				give_mutex(gate_open_mutex);
			}
			else
			{
				//Error
			}
		}

		Sleep(10);
		
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
		uint32_t end_time = start_time + 70;
		while (ticks < end_time)
		{
			//Wait for 6 seconds
			Sleep(10);
		}

		setGates(3);

		Sleep(10);
		//TODO
	}
}