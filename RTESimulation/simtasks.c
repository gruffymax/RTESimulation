#include "simtasks.h"
#include "cinterface.h"
#include "simulation.h"


static void sensor_0_state_machine(enum sensor_state_e* state0);
static void sensor_1_state_machine(enum sensor_state_e* state1);
static char gate_0_state_machine(enum gate_state_e* state0);
static char gate_1_state_machine(enum gate_state_e* state1);


extern uint32_t sim_tick;
extern BOOL simulation_run;
extern BOOL simulation_pause;
extern SEMPHR gate_open_semphr0;
extern SEMPHR gate_open_semphr1;

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
	if (simulation_run)
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
		send_task_to_sleep(10);
	}
}

void thread_task_gate_control(void)
{
	static enum gate_state_e state0 = gate_idle_state;
	static enum gate_state_e state1 = gate_idle_state;
	static char gate0_requested_state = 1; // Default to closed;
	static char gate1_requested_state = 1; // Default to closed;
	static char gate_state = 0;
	if (simulation_run)
	{
		gate0_requested_state = gate_0_state_machine(&state0);
		gate1_requested_state = gate_1_state_machine(&state1);
		gate_state = gate0_requested_state | gate1_requested_state << 1;
		setGates(gate_state);
		send_task_to_sleep(10);
	}
}

void thread_task_count_sensor(void)
{
	static char previous_state0 = 0;
	static char previous_state1 = 0;
	if (simulation_run)
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

		send_task_to_sleep(10);
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
		give_semphr(gate_open_semphr0);
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
		give_semphr(gate_open_semphr1);
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
		if (take_semphr(gate_open_semphr0) == 1)
		{
			start_ticks = sim_tick;
			*state0 = delay_state;
		}
		break;

	case delay_state:
		if (sim_tick >= start_ticks + 3800)
		{
			*state0 = open_state;
		}
		break;

	case open_state:
		*state0 = wait_state;
		end_ticks = sim_tick;
		return 0;

	case wait_state:
		if (sim_tick >= end_ticks + 1500)
		{
			//Sleep(1500);
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
		if (take_semphr(gate_open_semphr1) == 1)
		{
			start_ticks = sim_tick;
			*state1 = delay_state;
		}
		break;

	case delay_state:
		if (sim_tick >= start_ticks + 3800)
		{
			*state1 = open_state;
		}
		break;
	case open_state:
		*state1 = wait_state;
		end_ticks = sim_tick;
		return 0;

	case wait_state:
		if (sim_tick >= end_ticks + 1500)
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