/* motor.c
 * Gareth Waymark  762102
 * Aaron Whiteaway 904147
 *
 *
 */

static char motor_state = 0; // Stopped

void set_motor_state(char state)
{
	motor_state = state;
}

char get_motor_state(void)
{
	return motor_state;
}
