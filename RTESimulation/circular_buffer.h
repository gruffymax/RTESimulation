#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>

#define C_BUFFER_LENGTH 8

char add_to_circular_buffer0(uint32_t value);
uint32_t get_next_value_circular_buffer0(void);
void pop_head_circular_buffer0(void);
char add_to_circular_buffer1(uint32_t value);
uint32_t get_next_value_circular_buffer1(void);
void pop_head_circular_buffer1(void);



#endif //CIRCULAR_BUFFER_H
