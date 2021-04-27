#include "simulation.h"


static uint8_t block_dropper(void);


extern BOOL simulation_run;
extern BOOL simulation_pause;


void thread_simulation(void)
{
	static uint32_t next_drop;
	static uint32_t next_move;
	uint32_t now;
	uint8_t res = 0;
	set_gate0(1); // Start with closed gates
	set_gate1(1);
	next_drop = get_system_tick_ms() + 1000;
	next_move = get_system_tick_ms() + 100;

	while (simulation_run)
	{
		now = get_system_tick_ms();
		if (now >= next_drop)
		{
			res = block_dropper();
			next_drop = now + 3000;
		}

		if (now >= next_move)
		{
			if (get_motor_state)
			{
				move_belt0_fwds();
				move_belt1_fwds();
			}
			next_move = now + 100;
		}

		Sleep(20); // A little sleep to save processor time.
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
	/* A simple block dropper function that drops alternate large/small blocks
	 * onto the belts.
	 */
	static uint8_t block0 = 0; //0 = small, 1 = big;
	static uint8_t block1 = 1;
	uint8_t res = 1;

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
	return res;
}

uint32_t get_system_tick_ms(void)
{
	ULONGLONG current_time;
	QueryUnbiasedInterruptTime(&current_time);
	current_time = current_time / 10000;
	return (uint32_t)current_time;
}