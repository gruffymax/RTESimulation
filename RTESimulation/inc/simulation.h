#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdint.h>
#include <process.h>
#include <windows.h>
#include "belt.h"
#include "motor.h"
#include "gates.h"

void thread_tick(void);
void thread_simulation(void);
char sim_get_belt0(uint16_t element);
char sim_get_belt1(uint16_t element);
void stop_simulation(void);
void run_simulation(void);


#endif // SIMULATION_H
