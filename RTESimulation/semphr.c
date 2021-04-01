#include "semphr.h"

char * create_mutex(void)
{
	char *mutex = NULL; 
	mutex = (char*)malloc(sizeof(char));
	*mutex = 1; //Mutex available
	return mutex;
}

char take_mutex(char* mutex_handle)
{
	if (*mutex_handle == 1)
	{
		*mutex_handle = 0;
		return 1;
	}
	return 0; // Mutex not taken
}

char give_mutex(char* mutex_handle)
{
	if (*mutex_handle == 0)
	{
		*mutex_handle = 1;
		return 1;
	}
	return 0; // Mutex not given
}