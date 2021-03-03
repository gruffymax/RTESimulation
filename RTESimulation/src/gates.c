/* gates.c
 * Gareth Waymark  762102
 * Aaron Whiteaway 904147
 *
 *
 */

static char status_gate0 = 0; //Open
static char status_gate1 = 0; //Open

void set_gate0(char state)
{
	status_gate0 = state;
}

void set_gate1(char state)
{
	status_gate1 = state;
}

char get_gate0(void)
{
	return status_gate0;
}

char get_gate1(void)
{
	return status_gate1;
}
