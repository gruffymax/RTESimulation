#include "simulation.h"

static uint8_t block_dropper(void);

uint32_t ticks = 0;
extern BOOL simulation_run;
extern BOOL simulation_pause;

void start_scheduler(void)
{

}

void init_tasks(void)
{
	task[0].fp_task = &thread_task_read_sensors;
	task[0].id = 0;
	task[0].name = malloc(20);
	strcpy(task[0].name, "Read Sensor Task");
	task[0].priority = 1;
	task[0].state = Ready;


}

void thread_tick(void)
{
	while (simulation_run)
	{
		if (simulation_pause == 0)
		{
			ticks++;
		}
		Sleep(100);
	}	
}

void thread_simulation(void)
{
	static uint32_t old_tick = 0;
	uint8_t res = 0;
	set_gate0(1); // Start with closed gates
	set_gate1(1);

	while (simulation_run)
	{
		if (ticks > old_tick)
		{
			res = block_dropper();

			if (get_motor_state)
			{
				move_belt0_fwds();
				move_belt1_fwds();
			}

			old_tick = ticks;
		}
		Sleep(20);
	}
}

char sim_get_belt0(uint16_t element)
{
	return get_belt0_element(element);
}

char sim_get_belt1(uint16_t element)
{
	return get_belt1_element(element);
}

void stop_simulation(void)
{
	simulation_pause = 1;
}

void run_simulation(void)
{
	simulation_pause = 0;
}

static uint8_t block_dropper(void)
{
	static uint8_t block0 = 0; //0 = small, 1 = big;
	static uint8_t block1 = 1;
	static uint32_t time_to_drop = 10;
	uint8_t res = 1;

	if (ticks >= time_to_drop)
	{
		if (block0)
		{
			res = place_large_block_belt0();
			block0 = 0;
		}
		else
		{
			res = place_small_block_belt0();
			block0 = 1;
		}

		if (block1)
		{
			res = place_large_block_belt1();
			block1 = 0;
		}
		else
		{
			res = place_small_block_belt1();
			block1 = 1;
		}

		time_to_drop = time_to_drop + 40;

		return res;
	}
	return 0;
}

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