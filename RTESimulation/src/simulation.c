#include "simulation.h"

static uint8_t block_dropper(void);

uint32_t ticks = 0;
extern BOOL simulation_run;
extern BOOL simulation_pause;

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
