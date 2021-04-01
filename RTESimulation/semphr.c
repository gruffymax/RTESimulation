#include "semphr.h"

char* create_mutex(void)
{
	char* mutex = malloc(sizeof(char));
	*mutex = 1; //Mutex available
	return mutex;
}

char take_mutex(char* mutex_handle)
{
	if (*mutex_handle == 0)
	{
		*mutex_handle = 0;
		return 0;
	}
	return 1; //Error
}

char give_mutex(char* mutex_handle)
{
	if (*mutex_handle == 0)
	{
		*mutex_handle = 1;
		return 0;
	}
	return 1; //Error
}