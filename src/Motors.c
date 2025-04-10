
#include <stdint.h>
#include "HAL_GPIO.h"
#include "Sensors.h"
#include "Motors.h"


typedef struct Motor_t
{
    HAL_GPIO_t power;
    HAL_GPIO_t direction;
    Sensor_ID start_position;
    Sensor_ID end_position;
} Motor_t;

static const Motor_t motors_list[MOTORS_TOTAL] = {
    {{.port = HAL_GPIO_PORT_A, .pin = 0}, {.port = HAL_GPIO_PORT_A, .pin = 7}, NO_SENSOR, NO_SENSOR},
    {{.port = HAL_GPIO_PORT_A, .pin = 1}, {.port = HAL_GPIO_PORT_A, .pin = 2}, SENSOR_LS_MENOS45, SENSOR_LS_MAS45},
    {{.port = HAL_GPIO_PORT_A, .pin = 3}, {.port = HAL_GPIO_PORT_A, .pin = 4}, SENSOR_LS_DERECHA, SENSOR_LS_IZQUIERDA},
    {{.port = HAL_GPIO_PORT_A, .pin = 5}, {.port = HAL_GPIO_PORT_A, .pin = 6}, SENSOR_LS_PUERTA, SENSOR_INDUCTIVO},
};

static Motor_State motors_state_list[MOTORS_TOTAL] = {
    MOTOR_STATE_UNKNOWN,
    MOTOR_STATE_UNKNOWN,
    MOTOR_STATE_UNKNOWN,
    MOTOR_STATE_UNKNOWN,
};

void Motors_init()
{
    for (uint8_t m = 0; m < MOTORS_TOTAL; m++)
    {
        HAL_GPIO_init_output(motors_list[m].power.port, motors_list[m].power.pin);
        HAL_GPIO_init_output(motors_list[m].direction.port, motors_list[m].direction.pin);
        HAL_GPIO_write_bit(motors_list[m].power.port, motors_list[m].power.pin, 0);
        motors_state_list[m] = MOTOR_STATE_UNKNOWN;
    }
}

void Motor_move_to(Motor_ID m, Motor_Position new_position)
{
    if(m >= MOTORS_TOTAL)
    {
        return;
    }

    Motor_t const *motor = &motors_list[m];
    Motor_State motor_state = motors_state_list[m];
    
    if (motors_state_list[m] == MOTOR_STATE_INMOTION)
    {
        return;
    }
    
    if (((new_position == MOTOR_POSITION_START) && (motor_state == MOTOR_STATE_ATSTART)) ||
        ((new_position == MOTOR_POSITION_END) && (motor_state == MOTOR_STATE_ATEND))
    )
    {
        return; // we are where we should
    }
    
    if(new_position == MOTOR_POSITION_START)
    {
        HAL_GPIO_write_bit(motor->direction.port, motor->direction.pin, DIR_BACKWARD);
        HAL_GPIO_write_bit(motor->power.port, motor->power.pin, 1);
        motor_state = MOTOR_STATE_INMOTION;
        Sensor_wait_for(motor->start_position);
        motor_state = MOTOR_STATE_ATSTART;
        HAL_GPIO_write_bit(motor->power.port, motor->power.pin, 0);
    }
    else if(new_position == MOTOR_POSITION_END)
    {
        HAL_GPIO_write_bit(motor->direction.port, motor->direction.pin, DIR_FORWARD);
        HAL_GPIO_write_bit(motor->power.port, motor->power.pin, 1);
        motor_state = MOTOR_STATE_INMOTION;
        Sensor_wait_for(motor->end_position);
        motor_state = MOTOR_STATE_ATEND;
        HAL_GPIO_write_bit(motor->power.port, motor->power.pin, 0);
    }
    else
    {
        return;
    }
}

Motor_State Motor_get_state(Motor_ID m)
{
    if (m >= MOTORS_TOTAL)
    {
        return MOTOR_STATE_UNKNOWN;
    }
    return motors_state_list[m];
}

void Motor_off(Motor_ID m)
{
    if(m >= MOTORS_TOTAL)
    {
        return;
    }

    Motor_t const *motor = &motors_list[m];
    HAL_GPIO_write_bit(motor->power.port, motor->power.pin, 0);
    motors_state_list[m] = MOTOR_STATE_UNKNOWN;
}

void Motor_on(Motor_ID m, Motor_Direction dir)
{
    if(m >= MOTORS_TOTAL)
    {
        return;
    }

    Motor_t const *motor = &motors_list[m];
    HAL_GPIO_write_bit(motor->direction.port, motor->direction.pin, dir);
    HAL_GPIO_write_bit(motor->power.port, motor->power.pin, 1);
    motors_state_list[m] = MOTOR_STATE_INMOTION;
}
