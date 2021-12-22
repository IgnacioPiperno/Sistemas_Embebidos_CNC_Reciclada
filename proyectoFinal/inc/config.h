/*
 * config.h
 *
 *  Created on: 13 dic. 2021
 *      Author: ipipe
 */

#ifndef TP_FINAL_PROYECTOFINAL_INC_CONFIG_H_
#define TP_FINAL_PROYECTOFINAL_INC_CONFIG_H_

#include "sapi.h"

/* ========= UART options ========= */
#define COMMUNICATION_UART UART_USB
#define COMMUNICATION_UART_BAUD_RATE 115200
//#define DEBUG_UART UART_USB


/* ========= CNC TYPE ========= */
#define CONFIG_DVD_CNC
//#define CONFIG_CUSTOM_CNC

/* ========= main() constants ========= */
#define MAX_GBLOCK_LEN 150 // máximum length in bytes for gblock line

/* ========= Motor GPIO pins =========
 * DIR = direction
 * STEP = step
 * EN = enable (when LOW is enabled)
 */
// Y axis motor gpio pins.
#define MOTOR_Y_DIR GPIO0
#define MOTOR_Y_STEP GPIO1
#define MOTOR_Y_EN GPIO2

// Z axis motor gpio pins
#define MOTOR_Z_DIR GPIO3 // direction pin
#define MOTOR_Z_STEP GPIO4 // step pin
#define MOTOR_Z_EN GPIO5 // enable pin - low = enabled

// X axis motor gpio pins
#define MOTOR_X_DIR GPIO6 // direction pin
#define MOTOR_X_STEP GPIO7
#define MOTOR_X_EN GPIO8 // enable pin - low = enabled

// homing positions
#define DEFAULT_X_HOME_POS 0
#define DEFAULT_Y_HOME_POS 0
#define DEFAULT_Z_HOME_POS 5

#endif /* TP_FINAL_PROYECTOFINAL_INC_CONFIG_H_ */
