/**************************************************
*	\    ^ ^ 	Project:		Sample Code
*	 )  (="=)	Program name:	Display.h
*	(  /   ) 	Author:			Alan Fuentes
*	 \(__)|| 	                
*                               
**************************************************/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

typedef enum 
{
    Display_Position_Up,
    Display_Position_Down,
} Display_Position;

void Display_init();
void Display_writeDigits(uint16_t value, Display_Position position);
void Display_turn_off();

#endif // DISPLAY_H
