/**************************************************
*	\    ^ ^ 	Project:		Sample Code
*	 )  (="=)	Program name:	HAL_PCINT.h
*	(  /   ) 	Author:			Alan Fuentes
*	 \(__)|| 	                
*                               
**************************************************/

#ifndef HAL_PCINT_H
#define HAL_PCINT_H

#include <stdint.h>
#include <avr/interrupt.h> // To give access to sei ad cli

#define PCINT0_SHIFT 0
#define PCINT1_SHIFT 8
#define PCINT2_SHIFT 16

void HAL_PCINT_init(uint32_t pc_int_mask);

void ISR_PCINT0(uint8_t bits_set);
void ISR_PCINT1(uint8_t bits_set);
void ISR_PCINT2(uint8_t bits_set);

#endif //HAL_PCINT_H
