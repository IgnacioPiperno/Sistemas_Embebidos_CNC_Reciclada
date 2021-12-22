/*
 * communications.h
 *
 *  Created on: 18 dic. 2021
 *      Author: ipipe
 */

#ifndef TP_FINAL_PROYECTOFINAL_INC_COMMUNICATIONS_H_
#define TP_FINAL_PROYECTOFINAL_INC_COMMUNICATIONS_H_


#include "sapi.h"
#include "config.h"
#include "types.h"

void communication_config(void);
status_t get_line(char * line);
void send_status(status_t status);


#endif /* TP_FINAL_PROYECTOFINAL_INC_COMMUNICATIONS_H_ */
