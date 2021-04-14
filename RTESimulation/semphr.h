#ifndef SEMPHR_H
#define SEMPHR_H

#include <stdint.h>
#include <stdlib.h>

typedef char* SEMPHR;

SEMPHR create_semphr(char start_value);
char take_semphr(SEMPHR semphr_handle);
char give_semphr(SEMPHR semphr_handle);

#endif // SEMPHR_H