/* motor.h
 * Gareth Waymark  762102
 * Aaron Whiteaway 904147
 *
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

/* set_motor_state
 * Sets the motor state
 * 1 = Running
 * 0 = Stopped
 */
void set_motor_state(char state);

/* get_motor_state
 * Returns 0 = Stopped
 * Returns 1 = Running
 */
char get_motor_state(void);

#endif /* INC_MOTOR_H_ */
