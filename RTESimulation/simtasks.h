#ifndef SIMTASKS_H
#define SIMTASKS_H

#define GATE_OPEN_DELAY 3700
#define GATE_CLOSE_DELAY 1600

#include <stdint.h>
#include <windows.h>

void thread_task_read_sensors(void);
void thread_task_gate_control(void);
void thread_task_count_sensor(void);


#endif //SIMTASKS_H