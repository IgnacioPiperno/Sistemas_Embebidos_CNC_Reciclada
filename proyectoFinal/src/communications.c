/*
 * communications.c
 *
 *  Created on: 18 dic. 2021
 *      Author: ipipe
 */




#include "communications.h"


void communication_config(void){

	uartConfig(COMMUNICATION_UART, COMMUNICATION_UART_BAUD_RATE);

}

void send_status(status_t status){
	uartWriteByte(COMMUNICATION_UART, status);
}

status_t get_line(char * line){

	char read_char = '\0';
	uint32_t char_counter = 0;
	uint32_t timeout_counter = 0;
	bool_t did_read = false;
	uartWriteByte(COMMUNICATION_UART, 'O'); // send a permition to send a gblock
	while(read_char != '\n' && char_counter < MAX_GBLOCK_LEN && read_char != '#'){
		if(did_read = uartReadByte(COMMUNICATION_UART,&read_char)){
			switch(read_char){
				case '\r': case ' ': // trim whitespaces and carriage return
					break;

				// should add a comment filter here (not implemented yet)
				case '\n':
					line[char_counter] = '\0';
					char_counter++;
					break;

				default:
					line[char_counter] = read_char;
					char_counter++;
					break;
			}
		}

	}

	if(char_counter >= MAX_GBLOCK_LEN){
		FAIL(STATUS_GBLOCK_EXCEDED_LENGTH);
	}
	if(read_char == '#'){
		uartReadByte(COMMUNICATION_UART,&read_char); // flush remaining '\n'
		return STATUS_PROGRAM_ENDED;
	}
	return STATUS_LINE_OK;
}
