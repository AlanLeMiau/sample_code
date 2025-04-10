#include <stdint.h>
#include <stddef.h>
#include <avr/io.h>
#include "HAL_GPIO.h" 



// Arrays of pointers to PORT, DDR, and PIN registers
volatile uint8_t* const PORT_REGISTERS[HAL_GPIO_TOTAL_PORTS] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE, &PORTF, &PORTG, &PORTH, &PORTJ, &PORTK, &PORTL};
volatile uint8_t* const DDR_REGISTERS[HAL_GPIO_TOTAL_PORTS]  = {&DDRA,  &DDRB,  &DDRC,  &DDRD,  &DDRE,  &DDRF,  &DDRG,  &DDRH,  &DDRJ,  &DDRK,  &DDRL };
volatile uint8_t* const PIN_REGISTERS[HAL_GPIO_TOTAL_PORTS]  = {&PINA,  &PINB,  &PINC,  &PIND,  &PINE,  &PINF,  &PING,  &PINH,  &PINJ,  &PINK,  &PINL };

void HAL_GPIO_init_output(HAL_GPIO_PORT port, uint8_t pin)
{
    if (port < HAL_GPIO_TOTAL_PORTS)
    {
        *DDR_REGISTERS[port] |= (1 << pin); // Set the corresponding pin as output
    }
}

void HAL_GPIO_init_output_mask(HAL_GPIO_PORT port, uint8_t mask)
{
    if (port < HAL_GPIO_TOTAL_PORTS)
    {
        *DDR_REGISTERS[port] |= mask; // Set the corresponding pins as outputs
    }
}

void HAL_GPIO_write_port(HAL_GPIO_PORT port, uint8_t mask) {
    if (port < HAL_GPIO_TOTAL_PORTS) 
    {
        *PORT_REGISTERS[port] = mask; // Write the mask to the port
    }
}

void HAL_GPIO_write_bit(HAL_GPIO_PORT port, uint8_t bit, uint8_t value) {
    if (port < HAL_GPIO_TOTAL_PORTS) 
    {
        if (value) {
            *PORT_REGISTERS[port] |= (1 << bit); // Set the bit
        } else {
            *PORT_REGISTERS[port] &= ~(1 << bit); // Clear the bit
        }
    }
}

void HAL_GPIO_init_input(HAL_GPIO_PORT port, uint8_t pin, uint8_t isPullup)
{
    if (port < HAL_GPIO_TOTAL_PORTS)
    {
        *DDR_REGISTERS[port] &= ~(1 << pin); // Set the corresponding pin as input
        if (isPullup == 1) {
            *PORT_REGISTERS[port] |= (1 << pin); // Enable pull-up resistor
        }
    }
}


void HAL_GPIO_init_input_mask(HAL_GPIO_PORT port, uint8_t mask, uint8_t isPullup)
{
    if (port < HAL_GPIO_TOTAL_PORTS)
    {
        *DDR_REGISTERS[port] &= ~mask; // Set the corresponding pins as inputs
        if (isPullup == 1) {
            *PORT_REGISTERS[port] |= mask; // Enable pull-up resistor
        }
    }
}

uint8_t HAL_GPIO_read_port(HAL_GPIO_PORT port) {
    if (port < HAL_GPIO_TOTAL_PORTS)
    {
        return *PIN_REGISTERS[port]; // Read the entire port
    }
    return 0;
}

uint8_t HAL_GPIO_read_bit(HAL_GPIO_PORT port, uint8_t bit) {
    if (port < HAL_GPIO_TOTAL_PORTS)
    {
        return (*PIN_REGISTERS[port] & (1 << bit)) ? 1 : 0; // Read the specific bit
    }
    return 0;
}

