/* cinterface.c
 * Gareth Waymark  762102
 * Aaron Whiteaway 904147
 *
 *
 */

#include "cinterface.h"
#include "belt.h"
#include "motor.h"
#include "gates.h"

static char size_sensor_result0;
static char size_sensor_result1;
static char count_sensor_result0;
static char count_sensor_result1;

/* Sensor reading functions */
char readSizeSensors(char conveyor)
{
	if (conveyor == 0)
	{
		return size_sensor_result0;
	}
	else if (conveyor == 1)
	{
		return size_sensor_result1;
	}
	else
	{
		return beltERROR;
	}
}

char readCountSensor(char conveyor)
{
	if (conveyor == 0)
	{
		return count_sensor_result0;

	}
	else if (conveyor == 1)
	{
		return count_sensor_result1;
	}
	else
	{
		return beltERROR;
	}
}

void resetSizeSensors(char conveyor)
{
	char result = 0x0;
	if (conveyor == 0)
	{
		if (get_belt0_element(SIZE_SENSOR1_POS))
		{
			result = 0x1;
		}

		if (get_belt0_element(SIZE_SESNOR2_POS))
		{
			result = result | 0x2;
		}
		size_sensor_result0 = result;
	}

	if (conveyor == 1)
	{
		if (get_belt1_element(SIZE_SENSOR1_POS))
		{
			result = 0x1;
		}

		if (get_belt1_element(SIZE_SESNOR2_POS))
		{
			result = result | 0x2;
		}
		size_sensor_result1 = result;
	}
}
void resetCountSensor(char conveyor)
{

	if (conveyor == 0)
	{
		count_sensor_result0 = 0;
		if (get_belt0_element(COUNT_SENSOR_POS))
		{
			count_sensor_result0 = 1;
		}
	}

	if (conveyor == 1)
	{
		count_sensor_result1 = 0;
		if (get_belt1_element(COUNT_SENSOR_POS))
		{
			count_sensor_result1 = 1;
		}
	}
}

/* Gate & motor control functions */
void setGates(char state)
{
	set_gate0(state & 0x1);
	set_gate1((state & 0x2) >> 1);
}

void startMotor(void)
{
	set_motor_state(1);
}

void stopMotor(void)
{
	set_motor_state(0);
}
