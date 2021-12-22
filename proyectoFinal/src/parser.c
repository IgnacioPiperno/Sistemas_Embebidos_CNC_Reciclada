/*
 * parser.c
 *
 */

#include "parser.h"


/*
 * This function parses a line recieved in string
 */
status_t gc_parse(char *line, gblock_t *gblock){


	// Initialize auxiliary variables
	command_t axis_command = AXIS_COMMAND_NONE;
	uint8_t char_counter = 0;
	char letter; // command type letter
	uint8_t int_value = 0; // command number
	float value; // position value for an axis

	while (line[char_counter] != '\0') { // Loop until no more g-code words in line.

		// Import the next g-code word, expecting a letter followed by a value. Otherwise, error out.
		letter = line[char_counter];
		if((letter < 'A') || (letter > 'Z')) { FAIL(STATUS_EXPECTED_COMMAND_LETTER); } // [Expected word letter]
			char_counter++;
		if (!read_float(line, &char_counter, &value)) { FAIL(STATUS_BAD_COMMAND_NUMBER_FORMAT); } // [Expected word value]
		int_value = trunc(value);

	    // Check if the g-code word is supported or errors due to modal group violations or has
	    // been repeated in the g-code block. If ok, update the command or record its value.
		switch(letter){
			case 'G':
				switch(int_value){
					case 0:
						gblock->type = AXIS_COMMAND_FAST_LINEAR_MOTION;
						axis_command = AXIS_COMMAND_MOTION_MODE;
						gblock->vel = 100;
						break;
					case 1:
						gblock->type = AXIS_COMMAND_CONTROLLED_LINEAR_MOTION;
						axis_command = AXIS_COMMAND_MOTION_MODE;
						break;

					case 28:
						axis_command = AXIS_COMMAND_HOMING;
						break;

					case 90:
						gblock->coord = COORD_ABSOLUTE;
						break;

					case 91:
						gblock->coord = COORD_RELATIVE;
						break;

					case 17: case 18: case 19: // not supported yet
						FAIL(STATUS_GCODE_UNSUPPORTED_COMMAND);

					case 2: case 3: // not supported yet
						FAIL(STATUS_GCODE_UNSUPPORTED_COMMAND);

					default:
						FAIL(STATUS_GCODE_UNSUPPORTED_COMMAND);
				}
				break;

				case 'M':
					switch(int_value){
						case 0:
						case 1:
						case 2: //not supported yet
						FAIL(STATUS_GCODE_UNSUPPORTED_COMMAND);

						default:
						FAIL(STATUS_GCODE_UNSUPPORTED_COMMAND);
					}
					break;

				// NOTE: All remaining letters assign values.
				default:
					if(axis_command == AXIS_COMMAND_MOTION_MODE){
						switch(letter){
							case 'X':
								gblock->target_pos.pX = value;
								break;
							case 'Y':
								gblock->target_pos.pY = value;
								break;

							case 'Z':
								gblock->target_pos.pZ = value;
								break;

							case 'F':
								if(value > 0 && value <= 100){
									gblock->vel = value;
								}
								else{
									FAIL(STATUS_GCODE_EXCEDED_SPEED_LIMITS);
								}
								break;

							default:
								FAIL(STATUS_GCODE_UNSUPPORTED_COMMAND);
						}

					}
					else{
						FAIL(STATUS_GCODE_INCORRECT_COMMAND_FORMAT)
					}

		}


	}
	return STATUS_GBLOCK_PARSED;
}
