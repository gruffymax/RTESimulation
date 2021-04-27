#include "simtasks.h"
#include "cinterface.h"
#include "simulation.h"



static void sensor_0_state_machine(enum sensor_state_e* state0);
static void sensor_1_state_machine(enum sensor_state_e* state1);
static char gate_0_state_machine(enum gate_state_e* state0);
static char gate_1_state_machine(enum gate_state_e* state1);


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
	static enum sensor_state_e state0 = sensor_idle_state;
	static enum sensor_state_e state1 = sensor_idle_state;
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

			sensor_0_state_machine(&state0, &belt0sensor);
			sensor_1_state_machine(&state1, &belt1sensor);
		}
		Sleep(10);
	}
}

void thread_task_gate_control(void)
{
	static enum gate_state_e state0 = gate_idle_state;
	static enum gate_state_e state1 = gate_idle_state;
	char gate0_requested_state = 1; // Default to closed;
	char gate1_requested_state = 1; // Default to closed;
	char gate_state = 0;
	while (simulation_run)
	{
		gate0_requested_state = gate_0_state_machine(&state0);
		gate1_requested_state = gate_1_state_machine(&state1);
		gate_state = gate0_requested_state | gate1_requested_state << 1;
		setGates(gate_state);
		Sleep(10);
	}
}

void thread_task_count_sensor(void)
{
	char previous_state0 = 0;
	char previous_state1 = 0;
	while (simulation_run)
	{
		resetCountSensor(0);
		resetCountSensor(1);

		if (readCountSensor(0))
		{
			if (previous_state0 == 0)
			{
				LargeBlock0++;
			}
			
			previous_state0 = 1;
		}
		else
		{
			previous_state0 = 0;
		}

		if (readCountSensor(1))
		{
			if (previous_state1 == 0)
			{
				LargeBlock1++;
			}

			previous_state1 = 1;
		}
		else
		{
			previous_state1 = 0;
		}

		Sleep(10);
	}
}

static void sensor_0_state_machine(enum sensor_state_e *state0, char *belt0sensor)
{
	switch (*state0)
	{
	case sensor_idle_state:
		if (*belt0sensor == 1)
		{
			*state0 = transition_state;
		}
		break;
	case transition_state:
		if (*belt0sensor == 0)
		{
			*state0 = small_state;
			break;
		}
		if (*belt0sensor == 3)
		{
			*state0 = big_state;
			break;
		}
		break;
	case small_state:
		SmallBlock0++;
		*state0 = sensor_idle_state;
		break;
	case big_state:
		ReleaseSemaphore(semphr_gate_0, 1, NULL); // Give the semaphore to signal the gate to open
		*state0 = sensor_idle_state;
		break;
	default:
		*state0 = sensor_idle_state;
		break;
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
		ReleaseSemaphore(semphr_gate_1, 1, NULL); // Give the semaphore to signal the gate to open
		*state1 = sensor_idle_state;
		break;
	default:
		*state1 = sensor_idle_state;
		break;
	}
}

static char gate_0_state_machine(enum gate_state_e * state0)
{
	static uint32_t start_ticks = 0;
	static uint32_t end_ticks = 0;

	switch (*state0)
	{
	case gate_idle_state:
		if (WaitForSingleObject(semphr_gate_0, 0) == 0)
		{
			start_ticks = get_system_tick_ms();
			*state0 = delay_state;
		}
		break;

	case delay_state:
		if ( get_system_tick_ms() >= start_ticks + 3800)
		{
			*state0 = open_state;
		}
		break;

	case open_state:
		*state0 = wait_state;
		end_ticks = get_system_tick_ms();
		return 0;

	case wait_state:
		if (get_system_tick_ms() >= end_ticks + 1500)
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
			*state1 = delay_state;
		}
		break;

	case delay_state:
		if (get_system_tick_ms() >= start_ticks + 3800)
		{
			*state1 = open_state;
		}
		break;
	case open_state:
		*state1 = wait_state;
		end_ticks = get_system_tick_ms();
		return 0;

	case wait_state:
		if (get_system_tick_ms() >= end_ticks + 1500)
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