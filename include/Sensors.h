/**************************************************
*	\    ^ ^ 	Project:		Sample Code
*	 )  (="=)	Program name:	Sensors.h
*	(  /   ) 	Author:			Alan Fuentes
*	 \(__)|| 	                
*                               
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
int8_t Sensor_read_pin(Sensor_ID s);

#endif // SENSORS_H
