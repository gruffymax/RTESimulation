#include "semphr.h"

SEMPHR create_semphr(void)
{
	char* semphr = NULL;
	semphr = (char*)malloc(sizeof(char));
	*semphr = 1;
	return semphr;
}
char take_semphr(SEMPHR semphr_handle)
{
	if (*semphr_handle == 1)
	{
		*semphr_handle = 0;
		return 1; // Semaphore successfully taken
	}
	return 0; // Semaphore not taken
}

char give_semphr(SEMPHR semphr_handle)
{
	if (*semphr_handle == 0)
	{
		*semphr_handle = 1;
		return 1; // Semaphore successfully given
	}
	return 0; // Semaphore not given
}