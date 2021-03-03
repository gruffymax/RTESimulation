/* belt.h
 * Gareth Waymark  762102
 * Aaron Whiteaway 904147
 *
 * This header describes the interface used to interact with the
 * conveyer belts.
 * It defines, stores and manages the blocks on the belts.
 *
 * Belt length and sensor positions are stored as times. I.e. it
 * will take 10 seconds for the block to move from start to finish
 * on a 10 second belt.
 *
 * A discrete unit is the smallest unit of length in the simulation. It
 * is the the number of steps in 1 second multiplied by the length of the belt
 * in seconds. I.e. for a system tick of 100ms there are 10 steps in 1 second.
 * 10s belt length * 1/100ms = 100 units
 */

#ifndef INC_BELT_H_
#define INC_BELT_H_

#include <stdint.h>

/* Adjustable definitions */
#define SMALL_BLOCK_U 		5 	// Length of small block in units
#define LARGE_BLOCK_U 		10 	// Length of large block in units
#define BELT_LENGTH_S 		10 	// Length of belt in seconds
#define STEP_LENGTH_MS 		100 // Period of system tick in milliseconds
#define SIZE_SENSOR1_POS	30	// Position of 1st sensor
#define SIZE_SESNOR2_POS	40	// Position of 2nd sensor
#define COUNT_SENSOR_POS	100 // Position of count sensor

/* Calculated definitions */
#define BELT_LENGTH_U (BELT_LENGTH_S * (1000 / STEP_LENGTH_MS) + LARGE_BLOCK_U) // Belt length in units
#define beltOK 		0x0
#define beltFAIL 	0x1
#define beltERROR 	0xFF

/* get_belt0_element
 * Returns 0x0 if the supplied element is empty
 * Returns 0x1 if the supplied element is occupied
 * Returns 0xFF if element exceeds range
 */
char get_belt0_element(uint16_t element);

/* get_belt1_element
 * Returns 0x0 if the supplied element is empty
 * Returns 0x1 if the supplied element is occupied
 * Returns 0xFF if element exceeds range
 */
char get_belt1_element(uint16_t element);

/* clear_belt0
 * Clears all blocks from the belt
 */
void clear_belt0(void);

/* clear_belt1
 * Clears all blocks from the belt
 */
void clear_belt1(void);

/* place_large_block_belt0
 * Attempts to place a large block on belt 0
 * Returns 0 if OK
 * Returns 1 if FAIL (Block detected in starting zone
 */
char place_large_block_belt0(void);

/* place_large_block_belt1
 * Attempts to place a large block on belt 0
 * Returns 0 if OK
 * Returns 1 if FAIL (Block detected in starting zone
 */
char place_large_block_belt1(void);

/* place_small_block_belt0
 * Attempts to place a small block on belt 0
 * Returns 0 if OK
 * Returns 1 if FAIL (Block detected in starting zone
 */
char place_small_block_belt0(void);

/* place_small_block_belt1
 * Attempts to place a small block on belt 0
 * Returns 0 if OK
 * Returns 1 if FAIL (Block detected in starting zone
 */
char place_small_block_belt1(void);

/* move_belt0_fwds
 * Moves the belt forwards 1 unit
 */
void move_belt0_fwds(void);

/* move_belt1_fwds
 * Moves the belt forwards 1 unit
 */
void move_belt1_fwds(void);

#endif /* INC_BELT_H_ */
