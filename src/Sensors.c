
#include <stdint.h>
#include "HAL_GPIO.h"
#include "HAL_PCINT.h"
#include "Sensors.h"

typedef struct Sensor_t
{
    HAL_GPIO_t gpio;
    uint8_t is_pull_up;
    uint8_t bit_flag;
} Sensor_t;

static volatile uint32_t sensorStateFlags = 0;
static volatile uint32_t prevSensorStateFlags = 0;

static const Sensor_t sensors_list[SENSORS_TOTAL] = {
    {{.port = HAL_GPIO_PORT_B, .pin = 0}, 1, 0}, // sensorLSpuerta (PB0, PCINT0)
    {{.port = HAL_GPIO_PORT_B, .pin = 1}, 1, 1}, // sensorLSmas45 (PB1, PCINT1)
    {{.port = HAL_GPIO_PORT_B, .pin = 2}, 1, 2}, // sensorLSrecto (PB2, PCINT2)
    {{.port = HAL_GPIO_PORT_B, .pin = 3}, 1, 3}, // sensorLSmenos45 (PB3, PCINT3)
    {{.port = HAL_GPIO_PORT_B, .pin = 5}, 1, 5}, // sensorLSderecha (PB5, PCINT5)
    {{.port = HAL_GPIO_PORT_B, .pin = 6}, 1, 6}, // sensorLSizquierda (PB6, PCINT6)
    {{.port = HAL_GPIO_PORT_J, .pin = 0}, 1, 9}, // sensorInductivo (PJ0, PCINT9)
    {{.port = HAL_GPIO_PORT_K, .pin = 7}, 1, 23} // sensorCapacitivo (PK7, PCINT23)
};

static void Sensors_debounce_delay()
{
    volatile uint32_t timeout = 0xFFFF;
    while (timeout > 0)
    {
        timeout--;
    }
}

void Sensors_init()
{
    uint32_t pc_int_mask = 0;
    for (uint8_t s = 0; s < SENSORS_TOTAL; s++)
    {
        HAL_GPIO_init_input(sensors_list[s].gpio.port, sensors_list[s].gpio.pin, sensors_list[s].is_pull_up);
        pc_int_mask |= (1 << sensors_list[s].bit_flag);
    }
    HAL_PCINT_init(pc_int_mask);
}

int8_t Sensor_is_high(Sensor_ID s)
{
    if(s >= SENSORS_TOTAL)
    {
        return 0; // An invalid sensor cannot be high never
    }

    uint8_t sensor_interrupt_state = 0;
    uint8_t sensor_pin_state = 0;
    uint8_t stable_pin_state = 0;

    cli(); // Critical section
    sensor_interrupt_state = (sensorStateFlags & (1 << sensors_list[s].bit_flag));
    sensorStateFlags &= ~(1 << sensors_list[s].bit_flag);
    sei(); // End of critical section

    sensor_pin_state = HAL_GPIO_read_bit(sensors_list[s].gpio.port, sensors_list[s].gpio.pin);
    Sensors_debounce_delay();
    stable_pin_state = HAL_GPIO_read_bit(sensors_list[s].gpio.port, sensors_list[s].gpio.pin);

    if (sensor_interrupt_state && (sensor_pin_state == stable_pin_state))
    {
        return 1; // Sensor is high and stable
    }

    return 0; // Sensor is low or unstable
}

void Sensor_wait_for(Sensor_ID s)
{
    if(s >= SENSORS_TOTAL)
    {
        return;
    }
    while(!Sensor_is_high(s))
    {
        // wait for the sensor to be triggered
    }
}


// ISR(PCINT0_vect)
void ISR_PCINT0(uint8_t bits_set)
{
    prevSensorStateFlags = sensorStateFlags;
    sensorStateFlags = ((bits_set << PCINT0_SHIFT) ^ prevSensorStateFlags);
}

void ISR_PCINT1(uint8_t bits_set)
{
    prevSensorStateFlags = sensorStateFlags;
    sensorStateFlags = ((bits_set << PCINT1_SHIFT) ^ prevSensorStateFlags);
}

void ISR_PCINT2(uint8_t bits_set)
{
    prevSensorStateFlags = sensorStateFlags;
    sensorStateFlags = ((bits_set << PCINT2_SHIFT) ^ prevSensorStateFlags);
}
