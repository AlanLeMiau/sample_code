/**************************************************
*	\    ^ ^ 	Project:		Automatizacion de Sierra Cinta en Morelia
*	 )  (="=)	Program name:	Display.h
*	(  /   ) 	Author:			Raul Avendaño
*	 \(__)|| 	                Daniel Cedillo
*                               Alan Fuentes
* Driver for a Display with 6 digits, 3 up and 3 down
* It means, each row can show max number = 999
**************************************************/
#ifndef MOTORS_H
#define MOTORS_H

#include <stdint.h>
#include "HAL_GPIO.h"
#include "Sensors.h"


typedef enum
{
    MOTOR_POSITION_START,
    MOTOR_POSITION_END,
} Motor_Position;

typedef enum {
    MOTOR_SAW,
    MOTOR_CUT_ANGLE,
    MOTOR_ARM,
    MOTOR_DOOR,
    MOTORS_TOTAL
} Motor_ID;

void Motors_init();


#endif // MOTORS_H