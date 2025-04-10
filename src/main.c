/**************************************************
*    \   ^ ^    Project:        Automatizacion de Sierra Cinta en Morelia
*    )  (="=)   Program name:   maquinaFinal.ino
*   (  /   )    Author:         Raul Avendaño
*    \(__)||                    Daniel Cedillo
*                               Alan Fuentes
* Este programa automatiza el proceso de cortar trozoz de madera
* ya sea rectos o en forma de trapecio de distintas longitudes
* en un conjunto de tablas.
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