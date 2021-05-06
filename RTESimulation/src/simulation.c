#include "simulation.h"


static uint8_t block_dropper(void);
static uint32_t simulation_ticks = 0;

extern BOOL simulation_run;
extern BOOL simulation_pause;


void thread_simulation(void)
{
	static uint32_t next_drop;					//Local variables
	static uint32_t next_move;
	uint32_t now;
	uint8_t res = 0;
	set_gate0(1);
	set_gate1(1);
	next_drop = get_system_tick_ms() + 1000;	//Block timer ( every 1 second it drops a block)
	next_move = get_system_tick_ms() + 100;		//How fast the belt moves (every 0.1 second) - 100 steps - 10 seconds in total

	while (simulation_run)
	{
		if (!simulation_pause)
		{
			increment_simulation_ticks();		
			now = get_system_tick_ms();			//Retrieves current system time tick
			if (now >= next_drop)				//If system ticks greater or equal to next drop
			{									
				res = block_dropper();	
				next_drop = now + 2800;			//Next drop is longer
			}

			if (now >= next_move)
			{
				if (get_motor_state)
				{
					move_belt0_fwds();			//Forward function conv 1
					move_belt1_fwds();			//Forward function conv 2
				}
				next_move = now + 100;			//New move for belt calculated
			}
		}
		Sleep(20);								// Sleep 20ms
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
		res = place_large_block_belt0();	//Places large block on conv 1
		block0 = 0;
	}
	else
	{
		res = place_small_block_belt0();	//Places small block conv 1
		block0 = 1;
	}

	if (block1)
	{
		res = place_large_block_belt1();	//Places large block conv 2
		block1 = 0;
	}
	else
	{
		res = place_small_block_belt1();	//Places small block conv 2
		block1 = 1;
	}
	return res;
}

uint32_t get_system_tick_ms(void)
{
	return simulation_ticks;
}

void increment_simulation_ticks(void)
{
	simulation_ticks = simulation_ticks + 20;	//Calculates increment in system tick 
}