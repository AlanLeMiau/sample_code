/**************************************************
*	\    ^ ^ 	Project:		Sample Code
*	 )  (="=)	Program name:	Main.h
*	(  /   ) 	Author:			Alan Fuentes
*	 \(__)|| 	                
*                               
**************************************************/

#ifndef HAL_TIMER_1_H
#define HAL_TIMER_1_H

typedef enum
{
    MACHINE_STATE_HOMING,
    MACHINE_STATE_CUTTING,
    MACHINE_STATE_WAITING,
    MACHINE_STATE_ERROR,
    MACHINE_STATE_OFF,
} Machine_State;

void motor_cut_to_rect();
void do_homing();

#endif //HAL_TIMER_1_H
