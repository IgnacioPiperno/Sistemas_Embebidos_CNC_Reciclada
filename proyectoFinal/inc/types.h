/*
 * types.h
 *
 */

#ifndef PROYECTOFINAL_INC_TYPES_H_
#define PROYECTOFINAL_INC_TYPES_H_

#include "sapi.h"

#define FAIL(status) return(status); // macro function for failed operations

typedef enum{
	COORD_ABSOLUTE,
	COORD_RELATIVE

}coord_t;

typedef enum{
	STATUS_OK = 0, 							// code 0
	STATUS_EXPECTED_COMMAND_LETTER, 		// code 1
	STATUS_BAD_COMMAND_NUMBER_FORMAT, 		// code 2
	STATUS_GCODE_UNSUPPORTED_COMMAND, 		// code 3
	STATUS_GCODE_EXCEDED_SPEED_LIMITS, 		// code 4
	STATUS_GCODE_INCORRECT_COMMAND_FORMAT, 	// code 5
	STATUS_GBLOCK_PARSED, 					// code 6
	STATUS_GBLOCK_EXCEDED_LENGTH, 			// code 7
	STATUS_LINE_OK, 						// code 8
	STATUS_PAUSED, 							// code 9 (no implemented function yet)
	STATUS_RUNING, 							// code 10 not used yet
	STATUS_PROGRAM_ENDED, 					// code 11
	STATUS_READ_LINE_TIMEOUT				// code 12
}status_t;

typedef enum{
	AXIS_COMMAND_NONE,
	AXIS_COMMAND_MOTION_MODE,
	AXIS_COMMAND_FAST_LINEAR_MOTION,
	AXIS_COMMAND_CONTROLLED_LINEAR_MOTION,
	AXIS_COMMAND_HOMING

}command_t;

typedef struct{
	 float pX;
	 float pY;
	 float pZ;

}position_t;

typedef struct{
	 command_t type; 		// Instruction type
	 position_t target_pos; 	// Target position of axis
	 float vel;			// Movement speed
	 coord_t coord; 		// Relative or absolute coordinate system flag

}gblock_t;

typedef struct{
	gpioMap_t step_pin; // STEP pin connection for motor
	gpioMap_t dir_pin;	// DIR pin connection for motor
}motorConnection_t;




#endif /* PROYECTOFINAL_INC_TYPES_H_ */
