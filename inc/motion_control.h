/*
 * motion_control.h
 *
 *  Created on: 17 dic. 2021
 *      Author: ipipe
 */

#ifndef TP_FINAL_PROYECTOFINAL_INC_MOTION_CONTROL_H_
#define TP_FINAL_PROYECTOFINAL_INC_MOTION_CONTROL_H_

#include "sapi.h"
#include "types.h"
#include "motor_drive.h"

#define POSITIVE_MOVE true
#define NEGATIVE_MOVE false


void controlled_linear(position_t * curr_position, gblock_t block);
void fast_linear(position_t * curr_position, gblock_t block);
void home_all(position_t * curr_position);

#endif /* TP_FINAL_PROYECTOFINAL_INC_MOTION_CONTROL_H_ */
