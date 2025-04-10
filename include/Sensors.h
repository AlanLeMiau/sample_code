/**************************************************
*	\    ^ ^ 	Project:		Automatizacion de Sierra Cinta en Morelia
*	 )  (="=)	Program name:	Display.h
*	(  /   ) 	Author:			Raul Avendaño
*	 \(__)|| 	                Daniel Cedillo
*                               Alan Fuentes
* Driver for a Display with 6 digits, 3 up and 3 down
* It means, each row can show max number = 999
**************************************************/
#ifndef SENSORS_H
#define SENSORS_H

#include <stdint.h>

typedef enum {
    SENSOR_LS_PUERTA = 0,
    SENSOR_LS_MAS45,
    SENSOR_LS_RECTO,
    SENSOR_LS_MENOS45,
    SENSOR_LS_DERECHA,
    SENSOR_LS_IZQUIERDA,
    SENSOR_INDUCTIVO,
    SENSOR_CAPACITIVO,
    SENSORS_TOTAL,
    NO_SENSOR
} Sensor_ID;

void Sensors_init();
void Sensor_wait_for(Sensor_ID sensor_id);
int8_t Sensor_is_high(Sensor_ID s);


#endif // SENSORS_H