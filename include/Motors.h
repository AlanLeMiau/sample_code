/**************************************************
*	\    ^ ^ 	Project:		Sample Code
*	 )  (="=)	Program name:	Motors.h
*	(  /   ) 	Author:			Alan Fuentes
*	 \(__)|| 	                
*                               
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
void Motor_on(Motor_ID m);
void Motor_off(Motor_ID m);
void Motor_move_to(Motor_ID m, Motor_Position new_position);

#endif // MOTORS_H
