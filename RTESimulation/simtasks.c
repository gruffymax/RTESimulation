#include "simtasks.h"
#include "cinterface.h"
#include "simulation.h"
#include "circular_buffer.h"


/*PRIVATE FUNCTIONS*/
static void sensor_0_state_machine(enum sensor_state_e* state0, char* belt0sensor);
static void sensor_1_state_machine(enum sensor_state_e* state1, char* belt1sensor);
static char gate_0_state_machine(enum gate_state_e* state0);
static char gate_1_state_machine(enum gate_state_e* state1);

/*GLOBAL VARIABLES*/
extern BOOL simulation_run;
extern BOOL simulation_pause;
extern HANDLE semphr_gate_0;
extern HANDLE semphr_gate_1;

extern int SmallBlock;
extern int LargeBlock0;
extern int LargeBlock1;
extern int SmallBlock0;
extern int SmallBlock1;

enum sensor_state_e {sensor_idle_state, transition_state, small_state, big_state};
enum gate_state_e {gate_idle_state, delay_state, open_state, wait_state};


void thread_task_read_sensors(void)
{
	static enum sensor_state_e state0 = sensor_idle_state;					//Local variable states
	static enum sensor_state_e state1 = sensor_idle_state;
	while (simulation_run)													//while loop for simulation
	{
		char belt0sensor;													//local variables
		char belt1sensor;
		if (!simulation_pause)												//If statement checking for a simulation pause
		{
			resetSizeSensors(0);											//Goes to functions designated
			resetSizeSensors(1);
			belt0sensor = readSizeSensors(0);
			belt1sensor = readSizeSensors(1);

			sensor_0_state_machine(&state0, &belt0sensor);
			sensor_1_state_machine(&state1, &belt1sensor);
		}
		Sleep(10);															//Sleep for 10 ms
	}
}

void thread_task_gate_control(void)
{
	static enum gate_state_e state0 = gate_idle_state;
	static enum gate_state_e state1 = gate_idle_state;
	char gate0_requested_state = 1;											//Default to closed;
	char gate1_requested_state = 1;											//Default to closed;
	char gate_state = 0;
	while (simulation_run)													
	{
		if (!simulation_pause)
		{
			gate0_requested_state = gate_0_state_machine(&state0);			//'Asking' permission from the thread to adjust gate - from sempahore
			gate1_requested_state = gate_1_state_machine(&state1);
			gate_state = gate0_requested_state | gate1_requested_state << 1; //Getting bit information for the gates combinations - e.g. leaving both gates open gives a 0 output
			setGates(gate_state);
		}
		Sleep(10);															//Sleep for 10ms
	}
}

void thread_task_count_sensor(void)
{
	char previous_state0 = 0;	//Local variables
	char previous_state1 = 0;
	while (simulation_run)		//While simulation is running
	{
		if (!simulation_pause)	//Series of if statements checking for simulation stopping
		{
			resetCountSensor(0);
			resetCountSensor(1);

			if (readCountSensor(0))	//Reading sensors - conv 1
			{
				if (previous_state0 == 0)
				{
					LargeBlock0++;	//Increments large block variable
				}

				previous_state0 = 1;
			}
			else
			{
				previous_state0 = 0;
			}

			if (readCountSensor(1))	//Reading sensors - conv 2
			{
				if (previous_state1 == 0)
				{
					LargeBlock1++;	//Increments large block variable
				}

				previous_state1 = 1;
			}
			else
			{
				previous_state1 = 0;
			}
		}
		Sleep(10);
	}
}

static void sensor_0_state_machine(enum sensor_state_e *state0, char *belt0sensor)	//Private function passing through enumerated variable pointers
{
	switch (*state0)																//Switch statement for the point variable state0
	{
	case sensor_idle_state:															//Different cases for the different states
		if (*belt0sensor == 1)
		{
			*state0 = transition_state;												//Pointer position value equals transition state
		}
		break;
	case transition_state:
		if (*belt0sensor == 0)
		{
			*state0 = small_state;													//Pointer position value equals state xxxx
			break;
		}
		if (*belt0sensor == 3)
		{
			*state0 = big_state;													//Pointer position value equals state xxxx
			break;
		}
		break;
	case small_state:
		SmallBlock0++;																//increment small block
		*state0 = sensor_idle_state;
		break;
	case big_state:
		add_to_circular_buffer0(get_system_tick_ms() + GATE_OPEN_DELAY);			//Add something to the back of the circular buffer queue
		*state0 = sensor_idle_state;
		break;
	default:
		*state0 = sensor_idle_state;
		break;
	}

	if (get_system_tick_ms() >= get_next_value_circular_buffer0() && get_next_value_circular_buffer0() > 0)	//If system tick greater than or equal to next value of buffer and next value greater than 0
	{
		ReleaseSemaphore(semphr_gate_0, 1, NULL);									// Give the semaphore to signal the gate to open
		pop_head_circular_buffer0();												// Remove the head of the queue
	}
}

static void sensor_1_state_machine(enum sensor_state_e *state1, char *belt1sensor)	
{
	switch (*state1)
	{
	case sensor_idle_state:
		if (*belt1sensor == 1)
		{
			*state1 = transition_state;
		}
		break;
	case transition_state:
		if (*belt1sensor == 0)
		{
			*state1 = small_state;
			break;
		}
		if (*belt1sensor == 3)
		{
			*state1 = big_state;
			break;
		}
		break;
	case small_state:
		SmallBlock1++;
		*state1 = sensor_idle_state;
		break;
	case big_state:
		add_to_circular_buffer1(get_system_tick_ms() + GATE_OPEN_DELAY);
		*state1 = sensor_idle_state;
		break;
	default:
		*state1 = sensor_idle_state;
		break;
	}

	if (get_system_tick_ms() >= get_next_value_circular_buffer1() && get_next_value_circular_buffer1() > 0)
	{
		ReleaseSemaphore(semphr_gate_1, 1, NULL); // Give the semaphore to signal the gate to open
		pop_head_circular_buffer1();
	}
}

static char gate_0_state_machine(enum gate_state_e * state0)
{
	static uint32_t start_ticks = 0;					//Local variables
	static uint32_t end_ticks = 0;

	switch (*state0)									//Switch statement for state 0 pointer
	{
	case gate_idle_state:								//Switch cases 
		if (WaitForSingleObject(semphr_gate_0, 0) == 0)	//Checking for semaphore
		{
			start_ticks = get_system_tick_ms();			//	Resets ticks
			*state0 = open_state;
		}
		break;

	case open_state:
		*state0 = wait_state;
		end_ticks = get_system_tick_ms();				//Previous tick equals new tick
		return 0;

	case wait_state:
		if (get_system_tick_ms() >= end_ticks + GATE_CLOSE_DELAY)	//Checking system ticks against gate and end ticks time
		{
			*state0 = gate_idle_state;
			return 1;
		}
		return 0;

	default:
		*state0 = gate_idle_state;							
	}
	return 1;

}

static char gate_1_state_machine(enum gate_state_e * state1)
{
	static uint32_t start_ticks = 0;	
	static uint32_t end_ticks = 0;

	switch (*state1)
	{
	case gate_idle_state:
		if (WaitForSingleObject(semphr_gate_1, 0) == 0)
		{
			start_ticks = get_system_tick_ms();
			*state1 = open_state;
		}
		break;

	case open_state:
		*state1 = wait_state;
		end_ticks = get_system_tick_ms();
		return 0;

	case wait_state:
		if (get_system_tick_ms() >= end_ticks + GATE_CLOSE_DELAY)
		{
			*state1 = gate_idle_state;
			return 1;
		}
		return 0;

	default:
		*state1 = gate_idle_state;
	}
	return 1;
}