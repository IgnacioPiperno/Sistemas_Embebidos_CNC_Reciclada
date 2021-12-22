/*
 * TP FINAL
 *
 */


/*==================[inclusions]=============================================*/
#include "sapi.h"         // <= sAPI header
#include "sapi_gpio.h"
#include "types.h"
#include "parser.h"
#include "motor_drive.h"
#include "motion_control.h"
#include "config.h"
#include "communications.h"

/* The DEBUG* functions are sAPI debug print functions.
Code that uses the DEBUG* functions will have their I/O routed to
the sAPI DEBUG UART. */
//DEBUG_PRINT_ENABLE

/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void)
{
   /* ------------- INICIALIZACIONES ------------- */

   /* Inicializar la placa */
   boardConfig();

   /* UART Config */

   // debugPrintConfigUart( DEBUG_UART, 115200 );
   // debugPrintString( "TP final CNC Ignacio Piperno\r\n" );

   communication_config(); // configure comunications UART and BAUD rate

   gblock_t gblock;
   char line[MAX_GBLOCK_LEN]; // this is for testing: = {'G', '0', '1', 'X', '1', '0', '.', '0', '0', '0', '0', '0', '0', 'Y', '2', '0', '.', '0', '0', '0', '0', '0', '0', 'Z', '3', '0', '.', '0', '0', '0', '0', '0', '0', 'F', '7', '5', '.', '0', '0', '0', '0', '0', '0', '\0'};
   status_t status = STATUS_OK;

   // configure motor pins
   gpioConfig(MOTOR_X_DIR, GPIO_OUTPUT); // @suppress("Symbol is not resolved")
   gpioConfig(MOTOR_X_STEP, GPIO_OUTPUT); // @suppress("Symbol is not resolved")
   gpioConfig(MOTOR_X_EN, GPIO_OUTPUT); // @suppress("Symbol is not resolved")

   gpioConfig(MOTOR_Y_DIR, GPIO_OUTPUT); // @suppress("Symbol is not resolved")
   gpioConfig(MOTOR_Y_STEP, GPIO_OUTPUT); // @suppress("Symbol is not resolved")
   gpioConfig(MOTOR_Y_EN, GPIO_OUTPUT); // @suppress("Symbol is not resolved")

   gpioConfig(MOTOR_Z_DIR, GPIO_OUTPUT); // @suppress("Symbol is not resolved")
   gpioConfig(MOTOR_Z_STEP, GPIO_OUTPUT); // @suppress("Symbol is not resolved")
   gpioConfig(MOTOR_Z_EN, GPIO_OUTPUT); // @suppress("Symbol is not resolved")

   //define current position for reference (must be initially (0,0,0))
   position_t curr_position;
   curr_position.pX = 0;
   curr_position.pY = 0;
   curr_position.pZ = 0;
   //home_all(&curr_position); // home to configured position
   gblock.target_pos = curr_position; // initialize gblock for implicit coordinates in gblocks

   /* ------------- REPETIR POR SIEMPRE ------------- */

   while(1) {

	   send_status(status); // send status through serial communication

	   for(int i = 0; i< MAX_GBLOCK_LEN; i++){
		   line[i] = '\0';
	   }
	   status = get_line(line); // get gblock from sender program

	   if(status == STATUS_LINE_OK){
		   status = gc_parse(line, &gblock);
	   }

	   // home by TEC1 press
	   if(!gpioRead(TEC1)){
  		   home_all(&curr_position);
  	   }

//	   debugPrintString( "Gblock:\r\n");

	   if(status == STATUS_GBLOCK_PARSED){
		   switch(gblock.type){
		   	   case AXIS_COMMAND_FAST_LINEAR_MOTION:
		   		   fast_linear(&curr_position, gblock);
		   		   status = STATUS_OK;
		   		   break;
		   	   case AXIS_COMMAND_CONTROLLED_LINEAR_MOTION:
		   		   controlled_linear(&curr_position, gblock);
		   		   status = STATUS_OK;
		   		   break;
		   	   case AXIS_COMMAND_HOMING:
		   		   home_all(&curr_position);
		   		   status = STATUS_OK;
		   		   break;
		   	   default:
		   		   break;
		   }

	   }


   }

/*

// ============== Motor testing ==============
   motorConnection_t motor1;
   motor1.dir_pin = GPIO0;
   motor1.step_pin = GPIO1;

   motorConnection_t motor2;
   motor2.dir_pin = GPIO3;
   motor2.step_pin = GPIO4;

   //motor 1
   gpioConfig(GPIO0, GPIO_OUTPUT);
   gpioConfig(GPIO1, GPIO_OUTPUT);
   gpioConfig(GPIO2, GPIO_OUTPUT); // chip enable 1 - Low = enabled
   gpioWrite(GPIO2, false);

   // motor 2
   gpioConfig(GPIO3, GPIO_OUTPUT);
   gpioConfig(GPIO4, GPIO_OUTPUT);
   gpioConfig(GPIO5, GPIO_OUTPUT); // chip enable 2 - Low = enabled
   gpioWrite(GPIO5, false);

   while(1){
	   if(!gpioRead(TEC1)){
		   gpioWrite(LEDR,true);
		   move_motor(50, true, 100, motor1);
		   gpioWrite(LED1, false);
	   }
	   if(!gpioRead(TEC2)){
		   gpioWrite(LED1,true);
		   move_motor(50, false, 100, motor1);
		   gpioWrite(LEDR, false);
	   }

	   if(!gpioRead(TEC3)){
		   gpioWrite(LED2,true);
		   move_motor(50, true, 100, motor2);
		   gpioWrite(LED3, false);
	   }
	   if(!gpioRead(TEC4)){
		   gpioWrite(LED3,true);
		   move_motor(50, false, 100, motor2);
		   gpioWrite(LED2, false);
	   }



   }
   */

/*
// ================= interpolation testing ==================

   gpioWrite(MOTOR_Y_EN, LOW);
   gpioWrite(MOTOR_Z_EN, LOW);
   gpioWrite(MOTOR_X_EN, LOW);



   gblock_t block;
   while(1){
  	   if(!gpioRead(TEC1)){
  		   block.target_pos.pX = 10;
  		   block.target_pos.pY = 10;
  		   block.target_pos.pZ = 10;
  		   block.vel = 50;
  		   controlled_linear(&curr_position, block);
  	   }
  	   if(!gpioRead(TEC2)){
  		   block.target_pos.pX = 0;
  		   block.target_pos.pY = 0;
  		   block.target_pos.pZ = 0;
  		   block.vel = 100;
  		   controlled_linear(&curr_position, block);
  	   }
   }
*/
   /* no debe llegar acá */
   return 1;

}
/*==================[end of file]============================================*/
