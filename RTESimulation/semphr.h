#ifndef SEMPHR_H
#define SEMPHR_H

#include <stdint.h>
#include <stdlib.h>

typedef char* MUTEX;

MUTEX create_mutex(void);
char take_mutex(MUTEX mutex_handle);
char give_mutex(MUTEX mutex_handle);

#endif // SEMPHR_H