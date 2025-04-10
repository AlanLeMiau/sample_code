
#include <stdint.h>
#include "HAL_GPIO.h"
#include "HAL_TIMER1.h"
#include "Display.h"

#define DISPLAY_NUM_DIGITS 6 // 3 digits up and 3 down
#define DISPLAY_SEGMENTS_PORT HAL_GPIO_PORT_D

static volatile uint8_t display_numbers[DISPLAY_NUM_DIGITS] = {0};

static const HAL_GPIO_t catodos_gpio_list[DISPLAY_NUM_DIGITS] = {
    {HAL_GPIO_PORT_E, 4},    // pe4
    {HAL_GPIO_PORT_E, 5},    // pe5
    {HAL_GPIO_PORT_G, 5},    // pg5
    {HAL_GPIO_PORT_E, 3},    // pe3
    {HAL_GPIO_PORT_H, 3},    // ph3
    {HAL_GPIO_PORT_H, 4}     // ph4
};

//* 1 means segments OFF
//* 0 means segment ON
static const uint8_t digits_map[10] = 
{         // Pgfe dcba
    0xC0, // 0
    0xF9, // 1
    0xA4, // 2
    0xB0, // 3
    0x99, // 4
    0x92, // 5
    0x82, // 6
    0xF8, // 7
    0x80, // 8
    0x90  // 9
};

void Display_init()
{
    HAL_GPIO_init_output_mask(DISPLAY_SEGMENTS_PORT, 0xFF);
    HAL_GPIO_write_port(DISPLAY_SEGMENTS_PORT, 0xFF); // turn off all segments

    for (uint8_t c = 0; c < DISPLAY_NUM_DIGITS; c++)
    {
        HAL_GPIO_init_output(catodos_gpio_list[c].port, catodos_gpio_list[c].pin);
        HAL_GPIO_write_bit(catodos_gpio_list[c].port, catodos_gpio_list[c].pin, 0);
    }

    HAL_TIMER1_init();
}

void Display_writeDigits(uint16_t value, Display_Position position)
{
    uint8_t index;
    
    if (position == Display_Position_Up)
    {
        index = 3;
    }
    else if(position == Display_Position_Down)
    {
        index = 0;
    }
    else
    {
        return; // Bad call
    }

    if (value > 999)
    {
        value = 999;
    }
    // this should be atomic
    display_numbers[index] = value / 100;
    value = value - (display_numbers[index] * 100);

    display_numbers[index+1] = value / 10;
    value = value - (display_numbers[index+1] * 10);
    
    display_numbers[index+2] = value;
}

void Display_turn_off()
{
    for (uint8_t c = 0; c < DISPLAY_NUM_DIGITS; c++)
    {
        HAL_GPIO_write_bit(catodos_gpio_list[c].port, catodos_gpio_list[c].pin, 0);
    }
}

void ISR_TIMER1()
{
    static uint8_t displayIndex = 0;
    // turn off catodos_gpio_list
    Display_turn_off();

    // get digit
    uint8_t n = display_numbers[displayIndex];
    
    // write digit
    HAL_GPIO_write_port(DISPLAY_SEGMENTS_PORT, digits_map[n]);
    
    // turn on catodos
    HAL_GPIO_write_bit(catodos_gpio_list[displayIndex].port, catodos_gpio_list[displayIndex].pin, 1);
    
    displayIndex++;
    if(displayIndex >= DISPLAY_NUM_DIGITS)
    {
        displayIndex = 0;
    }
}
