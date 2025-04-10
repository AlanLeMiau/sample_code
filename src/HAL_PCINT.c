#include <stdint.h>
#include <stddef.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "HAL_GPIO.h" 
#include "HAL_PCINT.h"

static uint8_t pc_int_mask_list[3] = {0};

void HAL_PCINT_init(uint32_t pc_int_mask)
{
    uint8_t pc_int_mask_list[3];

    pc_int_mask_list[0] = (pc_int_mask >> PCINT0_SHIFT) & 0xFF;
    pc_int_mask_list[1] = (pc_int_mask >> PCINT1_SHIFT) & 0xFF;
    pc_int_mask_list[2] = (pc_int_mask >> PCINT2_SHIFT) & 0xFF;

    if(pc_int_mask_list[0] != 0)
    {
        PCICR |= (1 << PCIE0);
        PCMSK0 |= pc_int_mask_list[0];
    }
    if(pc_int_mask_list[1] != 0)
    {
        PCICR |= (1 << PCIE1);
        PCMSK0 |= pc_int_mask_list[1];
    }
    if(pc_int_mask_list[2] != 0)
    {
        PCICR |= (1 << PCIE2);
        PCMSK0 |= pc_int_mask_list[2];
    }
}

uint8_t HAL_PCINT_get_pending_ints()
{
    return 0;
}

//PCINT0 (Limit Switches)
ISR(PCINT0_vect)
{
    uint8_t int0_bits_set = (HAL_GPIO_read_port(HAL_GPIO_PORT_B) & pc_int_mask_list[0]);
    ISR_PCINT0(int0_bits_set);
}

//PCINT1 (Sensor Capacitivo e Inductivo)
ISR(PCINT1_vect)
{
    uint8_t int1_bits_set = (HAL_GPIO_read_port(HAL_GPIO_PORT_J) & pc_int_mask_list[1]);
    ISR_PCINT1(int1_bits_set);
}

//PCINT2 (botones Interfaz)
ISR(PCINT2_vect)
{
    uint8_t int2_bits_set = (HAL_GPIO_read_port(HAL_GPIO_PORT_K) & pc_int_mask_list[2]);
    ISR_PCINT2(int2_bits_set);
}