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

int main(void) {

    Display_init();
    Motors_init();
    Sensors_init();
    
    Display_writeDigits(123, Display_Position_Up);
    Display_writeDigits(456, Display_Position_Down);
    while (1) {

    }

    return 0;
}