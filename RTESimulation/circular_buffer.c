#include "circular_buffer.h"

uint8_t bufferHead0 = 0;
uint8_t bufferTail0 = 0;
uint8_t item_count0 = 0;
uint32_t circular_buffer0[C_BUFFER_LENGTH];
uint8_t bufferHead1 = 0;
uint8_t bufferTail1 = 0;
uint8_t item_count1 = 0;
uint32_t circular_buffer1[C_BUFFER_LENGTH];

char add_to_circular_buffer0(uint32_t value)
{
    if (item_count0 == C_BUFFER_LENGTH)
    {
        return 1; //Buffer full error
    }

    circular_buffer0[bufferTail0] = value;
    if (bufferTail0 < C_BUFFER_LENGTH - 1)
    {
        bufferTail0++;
    }
    else
    {
        bufferTail0 = 0;
    }
    item_count0++;
    return 0;
}

uint32_t get_next_value_circular_buffer0(void)
{
    if (item_count0 > 0)
    {
        return circular_buffer0[bufferHead0];
    }
    else
    {
        return 0;
    }
}

void pop_head_circular_buffer0(void)
{
    uint32_t value = circular_buffer0[bufferHead0];
    if (bufferHead0 < C_BUFFER_LENGTH - 1)
    {
        bufferHead0++;
    }
    else
    {
        bufferHead0 = 0;
    }

    if (item_count0 > 0)
    {
        item_count0--;
    }
}

char add_to_circular_buffer1(uint32_t value)
{
    if (item_count1 == C_BUFFER_LENGTH)
    {
        return 1; //Buffer full error
    }

    circular_buffer1[bufferTail1] = value;
    if (bufferTail1 < C_BUFFER_LENGTH - 1)
    {
        bufferTail1++;
    }
    else
    {
        bufferTail1 = 0;
    }
    item_count1++;
    return 0;
}

uint32_t get_next_value_circular_buffer1(void)
{
    if (item_count1 > 0)
    {
        return circular_buffer1[bufferHead1];
    }
    else
    {
        return 0;
    }
}

void pop_head_circular_buffer1(void)
{
    uint32_t value = circular_buffer1[bufferHead1];
    if (bufferHead1 < C_BUFFER_LENGTH - 1)
    {
        bufferHead1++;
    }
    else
    {
        bufferHead1 = 0;
    }

    if (item_count1 > 0)
    {
        item_count1--;
    }
}