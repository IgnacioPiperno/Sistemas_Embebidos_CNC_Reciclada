/*
 * motor_drive.c
 *
 *  Created on: 13 dic. 2021
 *      Author: ipipe
 */

#include "motor_drive.h"


/* =================== Global Variables =================== */
position_t last_position; // last position in absolute coordinates
float speed = 100; // speed % (values from 0 to 100) - Default is full speed

/*
// update delay for speed control with acceleration in mm/s**2, acutal speed in mm/s
void update_speed_delay(tick_t* speed_delay,float actual_speed, float acc){

	float speed_delta = acc*(*speed_delay/1000); // speed delta in mm/s - speed delay in m
	float new_speed = speed_delta+actual_speed;

	tick_t new_delay = 1/((new_speed) *STEPS_PER_MM_X) * 1000; // delay in ms
	pdMS_TO_TICKS(1);
	if(delay_delta)
		delay(1);

}
*/

// PARA REGULAR LA VELOCIDAD, PONER UN DELAY CADA VEZ QUE SE AVANZA UN PASO (PASO = (pasoX,pasoY,pasoZ))
/* Move X motor*/
void move_motor(int32_t steps, bool_t dir, float speed, motorConnection_t motor){

	float speed_delay;

	// Set direction and delay for speed control
	gpioWrite(motor.dir_pin, dir);
	if(speed > 0){
		speed_delay = 1/((speed/100) * MAX_SPEED * STEPS_PER_MM_X) * 1000; // delay in ms
	}
	else
	{
		speed_delay = 1/((1/100) * MAX_SPEED * STEPS_PER_MM_X) * 1000; // if speed is lower or equal to 0%, then use 1%
	}


	int16_t step_count = 0;
	while(step_count < steps){

		// make one step
		gpioWrite(motor.step_pin, true);
		// reset pin for future steps
		gpioWrite(motor.step_pin, false);
		delay(speed_delay);


		step_count++;
	}

}



void step(gpioMap_t axis)
{
	// if it was high, return to low to generate a rising edge
	gpioWrite(axis, LOW);

	//generate rising edge
	gpioWrite(axis, HIGH);

	// return to low state
	gpioWrite(axis, LOW);
}
