#include "simulation.h"
#include <string.h>

#define NO_OF_TASKS 3

static uint8_t block_dropper(void);
static int get_next_task(void);
static void update_sleep_states(void);

int next_task;
uint32_t sim_tick = 0;

extern BOOL simulation_run;
extern BOOL simulation_pause;

void start_scheduler(void)
{
    while (simulation_run)
    {
        if (!simulation_pause)
        {
            update_sleep_states();
            next_task = get_next_task();
            if (next_task != 0xFF)
            {
                task[next_task].state = Running;
                task[next_task].fp_task(); // Run task
                if (task[next_task].state == Running)
                {
                    task[next_task].state = Ready;
                }
            }
        }
        Sleep(5);
    }
}

static int get_next_task(void)
{
    int i;
    int priority = 2;
    while (priority > 0)
    {
        for (i = 0; i < NO_OF_TASKS; i++)
        {
            if (task[i].priority == priority && task[i].state == Ready)
            {
                return i;
            }
        }
        priority--;
    }
    return 0xFF;
}

static void update_sleep_states(void)
{
    int i;
    for (i = 0; i < NO_OF_TASKS; i++)
    {
        if (task[i].sleep_remaining > 0)
        {
            task[i].sleep_remaining--;
            task[i].state = Blocked;
        }
        else
        {
            task[i].sleep_remaining = 0;
            task[i].state = Ready;
        }
    }
}

void init_tasks(void)
{
    task[0].fp_task = &thread_task_read_sensors;
    task[0].id = 0;
    task[0].name = malloc(20);
    strcpy_s(task[0].name, 20,  "Read Sensor Task");
    task[0].priority = 1;
    task[0].state = Ready;
    task[0].sleep_remaining = 0;

    task[1].fp_task = &thread_task_gate_control;
    task[1].id = 1;
    task[1].name = malloc(20);
    strcpy_s(task[1].name, 20, "Gate Control Task");
    task[1].priority = 2;
    task[1].state = Ready;
    task[1].sleep_remaining = 0;

    task[2].fp_task = &thread_task_count_sensor;
    task[2].id = 2;
    task[2].name = malloc(20);
    strcpy_s(task[2].name, 20, "Count Sensor Task");
    task[2].priority = 1;
    task[2].state = Ready;
    task[2].sleep_remaining = 0;
}

void send_task_to_sleep(uint16_t duration)
{
    task[next_task].sleep_remaining = duration;
    task[next_task].state = Blocked;
}

void thread_tick(void)
{
    while (simulation_run)
    {
        if (!simulation_pause)
        {
            sim_tick++;
            Sleep(50);
        }
    }
}

void thread_simulation(void)
{
    static uint32_t old_tick = 0;
    uint8_t res = 0;
    set_gate0(1); // Start with closed gates
    set_gate1(1);

    while (simulation_run)
    {
        if (sim_tick > old_tick + 10)
        {
            res = block_dropper();

            if (get_motor_state)
            {
                move_belt0_fwds();
                move_belt1_fwds();
            }

            old_tick = sim_tick;
        }
    }
}

char sim_get_belt0(uint16_t element)
{
    return get_belt0_element(element);
}

char sim_get_belt1(uint16_t element)
{
    return get_belt1_element(element);
}

void stop_simulation(void)
{
    simulation_pause = 1;
}

void run_simulation(void)
{
    simulation_pause = 0;
}

static uint8_t block_dropper(void)
{
    static uint8_t block0 = 0; //0 = small, 1 = big;
    static uint8_t block1 = 1;
    static uint32_t time_to_drop = 10;
    uint8_t res = 1;

    if (sim_tick >= time_to_drop)
    {
        if (block0)
        {
            res = place_large_block_belt0();
            block0 = 0;
        }
        else
        {
            res = place_small_block_belt0();
            block0 = 1;
        }

        if (block1)
        {
            res = place_large_block_belt1();
            block1 = 0;
        }
        else
        {
            res = place_small_block_belt1();
            block1 = 1;
        }

        time_to_drop = time_to_drop + 400;

        return res;
    }
    return 0;
}

