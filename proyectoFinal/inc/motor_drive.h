/*
 * motor_drive.h
 *
 *      Author: ipipe
 */

#ifndef TP_FINAL_PROYECTOFINAL_INC_MOTOR_DRIVE_H_
#define TP_FINAL_PROYECTOFINAL_INC_MOTOR_DRIVE_H_

#include "sapi.h"
#include "types.h"
#include "config.h"

/* =================== Movement Constants =================== */
#define MAX_SPEED 1/4. // steps/ms
//V = 150 mm/s -> Delay = 1ms(MAX).
//V = 75 mm/s -> Delay = 2ms.
//V = 50mm/s -> Delay = 3ms.

#define ACCELERATION 0

#ifdef CONFIG_DVD_CNC
/* =================== Movement Limits =================== */
#define LEN_LIMIT_X 45 //maximum travel length for X axis in mm
#define LEN_LIMIT_Y 45 //maximum travel length for Y axis in mm
#define LEN_LIMIT_Z 37 //maximum travel length for Z axis in mm

/* =================== Motor Constants =================== */
#define MICRO_STEP_X 1 // microstepping factor for X axis
#define MM_PER_STEP_X 0.17 * MICRO_STEP_X // distance per step in mm for X motor
#define STEPS_PER_MM_X 1/MM_PER_STEP_X // steps per mm for X motor

#define MICRO_STEP_Y 1 // microstepping factor for Y axis
#define MM_PER_STEP_Y 0.18 * MICRO_STEP_Y // distance per step in mm for Y motor
#define STEPS_PER_MM_Y 1/MM_PER_STEP_Y // steps per mm for Y motor

#define MICRO_STEP_Z 1 // microstepping factor for Z axis
#define MM_PER_STEP_Z 0.126 * MICRO_STEP_Z 1 // distance per step in mm for Z motor (this one is Laptop CD drive)
#define STEPS_PER_MM_Z 1/MM_PER_STEP_Y // steps per mm for X motor

#endif

/* =================== function declarations =================== */

void move_motor(int32_t steps, bool_t dir, float speed, motorConnection_t motor);
void step(gpioMap_t axis);

#endif /* TP_FINAL_PROYECTOFINAL_INC_MOTOR_DRIVE_H_ */
