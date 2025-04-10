/**************************************************
*	\    ^ ^ 	Project:		Sample Code
*	 )  (="=)	Program name:	Sensors.h
*	(  /   ) 	Author:			Alan Fuentes
*	 \(__)|| 	                
*                               
**************************************************/

#include <avr/io.h>
#include <util/delay.h>
#include "Display.h"
#include "Motors.h"
#include "Sensors.h"
// #include "LEDs.h"
#include "Main.h"


static Machine_State machine_state = MACHINE_STATE_OFF;
static uint16_t corte = 0; // Nums of cuts
static uint16_t largo = 0; // Length of the cut

int main(void) {

    Display_init();
    Motors_init();
    Sensors_init();

    Motor_off(MOTOR_SAW);
    Motor_off(MOTOR_CUT_ANGLE);
    Motor_off(MOTOR_ARM);
    Motor_off(MOTOR_DOOR);
    
    machine_state = MACHINE_STATE_HOMING;
    
    while (1)
    {
        switch (machine_state)
        {
            case MACHINE_STATE_HOMING:
                do_homing();
                machine_state = MACHINE_STATE_WAITING;
                break;

            case MACHINE_STATE_CUTTING:
                // Cutting logic here
                break;

            case MACHINE_STATE_WAITING:
                // Waiting for user input to start cutting
                break;

            case MACHINE_STATE_ERROR:
                // error state
                break;

            case MACHINE_STATE_OFF:
                // Machine is off, do nothing
                break;

            default:
                // Invalid state, handle error
                break;
        }
    }

    return 0;
}

void motor_cut_to_rect()
{
    // menos45 start
    if((Motor_get_state(MOTOR_CUT_ANGLE) == MOTOR_STATE_ATMIDDLE) && (Sensor_read_pin(SENSOR_LS_RECTO)))
    {
        return; // we are where we should
    }

    if(Sensor_read_pin(SENSOR_LS_MENOS45))
    {
        Motor_on(MOTOR_CUT_ANGLE, DIR_FORWARD);
        Sensor_wait_for(SENSOR_LS_RECTO);
        Motor_off(MOTOR_CUT_ANGLE);
        Motor_set_state(MOTOR_CUT_ANGLE, MOTOR_STATE_ATMIDDLE);
        return;
    }

    if(Sensor_read_pin(SENSOR_LS_MAS45))
    {
        Motor_on(MOTOR_CUT_ANGLE, DIR_BACKWARD);
        Sensor_wait_for(SENSOR_LS_RECTO);
        Motor_off(MOTOR_CUT_ANGLE);
        Motor_set_state(MOTOR_CUT_ANGLE, MOTOR_STATE_ATMIDDLE);
        return;
    }
    
    // if we make it here, we don't know where we are
    // so, let's move and see where we end up
    Motor_on(MOTOR_CUT_ANGLE, DIR_FORWARD);
    while((!Sensor_is_high(SENSOR_LS_RECTO)) && (!Sensor_is_high(SENSOR_LS_MENOS45)) && (!Sensor_is_high(SENSOR_LS_MAS45)))
    {
        // wait for the sensor to be triggered
    }
    Motor_off(MOTOR_CUT_ANGLE);
    if(Sensor_read_pin(SENSOR_LS_RECTO))
    {
        Motor_set_state(MOTOR_CUT_ANGLE, MOTOR_STATE_ATMIDDLE);
        return;
    }
    else if(Sensor_read_pin(SENSOR_LS_MENOS45))
    {
        Motor_set_state(MOTOR_CUT_ANGLE, MOTOR_STATE_ATSTART);
        return;
    }
    else if(Sensor_read_pin(SENSOR_LS_MAS45))
    {
        Motor_set_state(MOTOR_CUT_ANGLE, MOTOR_STATE_ATEND);
        return;
    }
}

void do_homing()
{
    // Reset variables
    corte = 0;
    largo = 0;
    Display_writeDigits(corte, Display_Position_Up);
    Display_writeDigits(largo, Display_Position_Down);

    // Turn-Off Saw "M1"
    Motor_off(MOTOR_SAW);

    // Move arm to right  "M3"
    if (Motor_get_state(MOTOR_ARM) != MOTOR_STATE_ATSTART)
    {
        Motor_move_to(MOTOR_ARM, MOTOR_POSITION_START);
    }

    // Move door to beggining "M4"
    if (Motor_get_state(MOTOR_DOOR) != MOTOR_STATE_ATSTART)
    {
        Motor_move_to(MOTOR_DOOR, MOTOR_POSITION_START);
    }

    // Check what is the cut angleand ensure to start rect "M2"
    motor_cut_to_rect();

} // END Home
