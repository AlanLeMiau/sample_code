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

typedef enum {
    DIR_FORWARD,
    DIR_BACKWARD,
} Motor_Direction;

typedef enum
{
    MOTOR_POSITION_START,
    MOTOR_POSITION_END,
} Motor_Position;

typedef enum
{
    MOTOR_STATE_ATSTART,
    MOTOR_STATE_ATEND,
    MOTOR_STATE_INMOTION,
    MOTOR_STATE_UNKNOWN,
} Motor_State;

typedef enum {
    MOTOR_SAW,
    MOTOR_CUT_ANGLE,
    MOTOR_ARM,
    MOTOR_DOOR,
    MOTORS_TOTAL
} Motor_ID;

void Motors_init();
void Motor_on(Motor_ID m, Motor_Direction dir);
void Motor_off(Motor_ID m);
void Motor_move_to(Motor_ID m, Motor_Position new_position);
Motor_State Motor_get_state(Motor_ID m);

#endif // MOTORS_H
