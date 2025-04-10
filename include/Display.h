/**************************************************
*	\    ^ ^ 	Project:		Automatizacion de Sierra Cinta en Morelia
*	 )  (="=)	Program name:	Display.h
*	(  /   ) 	Author:			Raul Avendaño
*	 \(__)|| 	                Daniel Cedillo
*                               Alan Fuentes
* Driver for a Display with 6 digits, 3 up and 3 down
* It means, each row can show max number = 999
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