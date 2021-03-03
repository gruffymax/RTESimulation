/* gates.h
 * Gareth Waymark  762102
 * Aaron Whiteaway 904147
 *
 */

#ifndef INC_GATES_H_
#define INC_GATES_H_

/* set_gate0
 * Set the state of gate 0
 * 1 = Closed
 * 0 = Open
 */
void set_gate0(char state);

/* set_gate1
 * Set the state of gate 1
 * 1 = Closed
 * 0 = Open
 */
void set_gate1(char state);

/* get_gate0
 * Returns 1 if Closed
 * Returns 0 if Open
 */
char get_gate0(void);

/* get_gate1
 * Returns 1 if Closed
 * Returns 0 if Open
 */
char get_gate1(void);

#endif /* INC_GATES_H_ */
