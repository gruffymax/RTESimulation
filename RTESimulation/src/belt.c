/* belt.c
 * Gareth Waymark  762102
 * Aaron Whiteaway 904147
 *
 *
 */

#include "belt.h"

/* Static Private functions */
static char check_starting_zone(char belt);

/* Private belt arrays. Only accessible via public get/set functions */
static char belt0[BELT_LENGTH_U] = {0};
static char belt1[BELT_LENGTH_U] = {0};

char get_belt0_element(uint16_t element)
{
	if (element >= BELT_LENGTH_U)
	{
		return beltERROR; // beltERROR: element does not exist
	}
	else
	{
		return belt0[element];
	}
}

char get_belt1_element(uint16_t element)
{
	if (element >= BELT_LENGTH_U)
	{
		return beltERROR; // beltERROR: element does not exist
	}
	else
	{
		return belt1[element];
	}
}

void clear_belt0(void)
{
	uint16_t i = 0;
	for (i=0; i<BELT_LENGTH_U; i++)
	{
		belt0[i] = 0;
	}
}

void clear_belt1(void)
{
	uint16_t i = 0;
	for (i=0; i<BELT_LENGTH_U; i++)
	{
		belt1[i] = 0;
	}
}

char place_large_block_belt0(void)
{
	if (check_starting_zone(0) != beltOK)
	{
		return beltFAIL;
	}

	int i = 0;
	for (i=0; i<LARGE_BLOCK_U; i++)
	{
		belt0[i] = 1;
	}
	return beltOK;
}

char place_large_block_belt1(void)
{
	if (check_starting_zone(1) != beltOK)
	{
		return beltFAIL;
	}

	int i = 0;
	for (i=0; i<LARGE_BLOCK_U; i++)
	{
		belt1[i] = 0x1;
	}
	return beltOK;
}

char place_small_block_belt0(void)
{
	if (check_starting_zone(0) != beltOK)
	{
		return beltFAIL;
	}

	int i = 0;
	for (i=LARGE_BLOCK_U - SMALL_BLOCK_U; i<LARGE_BLOCK_U; i++)
	{
		belt0[i] = 0x1;
	}
	return beltOK;
}

char place_small_block_belt1(void)
{
	if (check_starting_zone(1) != beltOK)
	{
		return beltFAIL;
	}

	int i = 0;
	for (i=LARGE_BLOCK_U - SMALL_BLOCK_U; i<LARGE_BLOCK_U; i++)
	{
		belt1[i] = 0x1;
	}
	return beltOK;
}

static char check_starting_zone(char belt)
{
	int i = 0;
	for (i=0; i<LARGE_BLOCK_U; i++)
	{
		if (belt == 0x0)
		{
			if (belt0[i])
			{
				return beltFAIL; // beltERROR: Block detected
			}
		}
		else if (belt == 0x1)
		{
			if (belt1[i])
			{
				return beltFAIL;
			}
		}
		else
		{
			return beltERROR; // Belt value not 0 or 1
		}
	}
	return beltOK;
}

void move_belt0_fwds(void)
{
	uint16_t i = 0;
	for (i=BELT_LENGTH_U - 1; i>0; i--)
	{
		belt0[i] = belt0[i-1];
	}
	belt0[0] = 0;
}

void move_belt1_fwds(void)
{
	uint16_t i = 0;
	for (i=BELT_LENGTH_U - 1; i>0; i--)
	{
		belt1[i] = belt1[i-1];
	}
	belt1[0] = 0;
}
