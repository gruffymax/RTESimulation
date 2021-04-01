#ifndef SEMPHR_H
#define SEMPHR_H

#include <stdint.h>

char* create_mutex(void);
char take_mutex(char* mutex_handle);
char give_mutex(char* mutex_handle);

#endif // SEMPHR_H