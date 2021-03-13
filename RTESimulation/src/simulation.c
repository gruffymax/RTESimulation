#include "simulation.h"

uint32_t ticks = 0;
int simulation_run;

void thread_tick(void)
{
	while (simulation_run)
	{
		ticks++;
		Sleep(100);
	}
}

void thread_simulation(void)
{
	uint32_t old_tick = 0;

	/* TESTING block placed here*/
	place_large_block_belt0();
	place_small_block_belt1();

	while (simulation_run)
	{
		if (ticks > old_tick)
		{
			if (get_motor_state)
			{
				move_belt0_fwds();
				move_belt1_fwds();
			}
			old_tick = ticks;
			Sleep(99);
		}
		
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