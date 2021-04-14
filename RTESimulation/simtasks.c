#include "simtasks.h"
#include "cinterface.h"


extern uint32_t ticks;
extern BOOL simulation_run;
extern BOOL simulation_pause;
extern SEMPHR gate_open_semphr0;
extern SEMPHR gate_open_semphr1;
extern SEMPHR gate_close_semphr0;
extern SEMPHR gate_close_semphr1;
enum sensor_state_e {idle_state, transition_state, small_state, big_state};
enum gate_state_e {idle_state, delay_state, open_state, wait_state, close_state };

void thread_task_read_sensors(void)
{
	static enum sensor_state_e state0 = idle_state;
	static enum sensor_state_e state1 = idle_state;
	while (simulation_run)
	{
		char belt0sensor;
		char belt1sensor;
		if (!simulation_pause)
		{
			resetSizeSensors(0);
			resetSizeSensors(1);
			belt0sensor = readSizeSensors(0);
			belt1sensor = readSizeSensors(1);

			switch (state0)
			{
			case idle_state:
				if (belt0sensor == 1)
				{
					state0 = transition_state;
				}
				break;
			case transition_state:
				if (belt0sensor == 0)
				{
					state0 = small_state;
					break;
				}
				if (belt0sensor == 3)
				{
					state0 = big_state;
					break;
				}
				break;
			case small_state:
				//TODO increment small block counter
				break;
			case big_state:
				give_semphr(gate_open_semphr0);
				state0 = idle_state;
				break;
			default:
				state0 = idle_state;
				break;
			}

			switch (state1)
			{
			case idle_state:
				if (belt1sensor == 1)
				{
					state1 = transition_state;
				}
				break;
			case transition_state:
				if (belt1sensor == 0)
				{
					state1 = small_state;
					break;
				}
				if (belt1sensor == 3)
				{
					state1 = big_state;
					break;
				}
				break;
			case small_state:
				//TODO increment small block counter
				break;
			case big_state:
				give_semphr(gate_open_semphr1);
				state1 = idle_state;
				break;
			default:
				state1 = idle_state;
				break;
			}
			
		}

		Sleep(10);
		
	}
}

void thread_task_gate_control(void)
{
	static enum gate_state_e state0 = idle_state;
	static enum gate_state_e state1 = idle_state;
	uint32_t start_ticks = 0;
	while (simulation_run)
	{
		switch (state0)
		{
			case idle_state:
				if (take_semphr == 1)
				{
					start_ticks = ticks;
					state0 = delay_state;
				}
				break;
			case delay_state:
				if (ticks >= start_ticks + 38)
				{
					state0 = open_state;
				}
				break;
			case open_state:
				setGates(0x02);
				state0 = wait_state;
				break;
		}

		Sleep(10);
		//TODO
	}
}