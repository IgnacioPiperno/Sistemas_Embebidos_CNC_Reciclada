/*
 * interpolations.c
 *
 *  Created on: 15 dic. 2021
 *      Author: ipipe
 */

#include "motion_control.h"

// values shouldn't ve validated since its done in the parsing step
// linear move implemented with bresenham interpolation
void controlled_linear(position_t * curr_position, gblock_t block){

	// Set movement directions and deltas (in steps)
	// X axis
	uint16_t max_steps_X;
	uint16_t max_steps_Y;
	uint16_t max_steps_Z;
	if(block.target_pos.pX > curr_position->pX)
	{
		gpioWrite(MOTOR_X_DIR, POSITIVE_MOVE);
		max_steps_X = (uint16_t)((block.target_pos.pX - curr_position->pX)*STEPS_PER_MM_X);
	}
	else{
		gpioWrite(MOTOR_X_DIR, NEGATIVE_MOVE);
		max_steps_X = (uint16_t)(-(block.target_pos.pX - curr_position->pX)*STEPS_PER_MM_X);
	}

	// Y axis
	if(block.target_pos.pY > curr_position->pY)
	{
		gpioWrite(MOTOR_Y_DIR, POSITIVE_MOVE);
		max_steps_Y = (uint16_t)((block.target_pos.pY - curr_position->pY)*STEPS_PER_MM_Y);
	}
	else{
		gpioWrite(MOTOR_Y_DIR, NEGATIVE_MOVE);
		max_steps_Y = (uint16_t)(-(block.target_pos.pY - curr_position->pY)*STEPS_PER_MM_Y);
	}


	// Z axis
	if(block.target_pos.pZ > curr_position->pZ)
	{
		gpioWrite(MOTOR_Z_DIR, POSITIVE_MOVE);
		max_steps_Z = (uint16_t)((block.target_pos.pZ - curr_position->pZ)*STEPS_PER_MM_Z);
	}
	else{
		gpioWrite(MOTOR_Z_DIR, NEGATIVE_MOVE);
		max_steps_Z = (uint16_t)(-(block.target_pos.pZ - curr_position->pZ)*STEPS_PER_MM_Z);
	}


	// Setup speed
	uint32_t speed_delay;
	speed_delay = 1/((block.vel/100) * MAX_SPEED); // delay in ms


	// decide driving axis
	gpioMap_t driving_axis;
	uint16_t driving_steps;
	gpioMap_t second_axis;
	uint16_t second_steps;
	gpioMap_t third_axis;
	uint16_t third_steps;

	if(max_steps_X >= max_steps_Y && max_steps_X >= max_steps_Z){
		driving_axis = MOTOR_X_STEP;
		driving_steps = max_steps_X;
		second_axis = MOTOR_Y_STEP;
		second_steps = max_steps_Y;
		third_axis = MOTOR_Z_STEP;
		third_steps = max_steps_Z;
	}
	else if(max_steps_Y >= max_steps_Z){
		driving_axis = MOTOR_Y_STEP;
		driving_steps = max_steps_Y;
		second_axis = MOTOR_X_STEP;
		second_steps = max_steps_X;
		third_axis = MOTOR_Z_STEP;
		third_steps = max_steps_Z;


	}
	else{
		driving_axis = MOTOR_Z_STEP;
		driving_steps = max_steps_Z;
		second_axis = MOTOR_X_STEP;
		second_steps = max_steps_X;
		third_axis = MOTOR_Y_STEP;
		third_steps = max_steps_Y;

	}

	// set decition variables
	int32_t second_decition = 2 * second_steps - driving_steps;
	int32_t third_decition =  2 * third_steps - driving_steps;

	// run interpolation and move motors
	uint16_t step_count = 0;
	while(step_count < driving_steps){
		step(driving_axis);
		step_count ++;

		if(second_decition > 0){
			step(second_axis);
			second_decition -= 2*driving_steps;
		}
		if(third_decition > 0){
			step(third_axis);
			third_decition -= 2*driving_steps;
		}

		second_decition += 2*second_steps;
		third_decition += 2*third_steps;

		// control movement speed with a delay
		delay(speed_delay);
	}

	// change current position value for main program
	*curr_position = block.target_pos;
}

void fast_linear(position_t * curr_position, gblock_t gblock){
	// set maximum speed
	gblock.vel = 100;
	// implementation is the same as controlled_linear()
	controlled_linear(curr_position, gblock);
}

void home_all(position_t * curr_position){

	// Set movement directions and deltas (in steps)
	// X axis
	uint16_t max_steps_X;
	uint16_t max_steps_Y;
	uint16_t max_steps_Z;
	uint16_t step_count = 0;

	// X axis delta and direction
	if(DEFAULT_X_HOME_POS > curr_position->pX)
	{
		gpioWrite(MOTOR_X_DIR, POSITIVE_MOVE);
		max_steps_X = (uint16_t)((DEFAULT_X_HOME_POS - curr_position->pX)*STEPS_PER_MM_X);
	}
	else{
		gpioWrite(MOTOR_X_DIR, NEGATIVE_MOVE);
		max_steps_X = (uint16_t)(-(DEFAULT_X_HOME_POS - curr_position->pX)*STEPS_PER_MM_X);
	}

	// Y axis delta and direction
	if(DEFAULT_Y_HOME_POS > curr_position->pY)
	{
		gpioWrite(MOTOR_Y_DIR, POSITIVE_MOVE);
		max_steps_Y = (uint16_t)((DEFAULT_Y_HOME_POS - curr_position->pY)*STEPS_PER_MM_Y);
	}
	else{
		gpioWrite(MOTOR_Y_DIR, NEGATIVE_MOVE);
		max_steps_Y = (uint16_t)(-(DEFAULT_Y_HOME_POS - curr_position->pY)*STEPS_PER_MM_Y);
	}


	// Z axis delta and direction
	if(DEFAULT_Z_HOME_POS > curr_position->pZ)
	{
		gpioWrite(MOTOR_Z_DIR, POSITIVE_MOVE);
		max_steps_Z = (uint16_t)((DEFAULT_Z_HOME_POS - curr_position->pZ)*STEPS_PER_MM_Z);
	}
	else{
		gpioWrite(MOTOR_Z_DIR, NEGATIVE_MOVE);
		max_steps_Z = (uint16_t)(-(DEFAULT_Z_HOME_POS - curr_position->pZ)*STEPS_PER_MM_Z);
	}


	// speed always max
	uint32_t speed_delay;
	speed_delay = 1/(MAX_SPEED); // delay in ms

	// move each axis

	// first lift pen
	while(step_count < max_steps_Z){
		// make one step
		step(MOTOR_Z_STEP);
		delay(speed_delay);
		step_count++;
	}

	step_count = 0;
	while(step_count < max_steps_Y){
		// make one step
		step(MOTOR_Y_STEP);
		delay(speed_delay);
		step_count++;
	}

	step_count = 0;
	while(step_count < max_steps_X){
		// make one step
		step(MOTOR_X_STEP);
		delay(speed_delay);
		step_count++;
	}

	curr_position->pX = DEFAULT_X_HOME_POS;
	curr_position->pY = DEFAULT_Y_HOME_POS;
	curr_position->pZ = DEFAULT_Z_HOME_POS;

}
