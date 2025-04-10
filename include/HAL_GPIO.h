#ifndef HAL_GPIO_H
#define HAL_GPIO_H

typedef enum 
{
    HAL_GPIO_PORT_A, 
    HAL_GPIO_PORT_B,
    HAL_GPIO_PORT_C,
    HAL_GPIO_PORT_D,
    HAL_GPIO_PORT_E,
    HAL_GPIO_PORT_F,
    HAL_GPIO_PORT_G,
    HAL_GPIO_PORT_H,
    HAL_GPIO_PORT_J,
    HAL_GPIO_PORT_K,
    HAL_GPIO_PORT_L,
    HAL_GPIO_TOTAL_PORTS
} HAL_GPIO_PORT;


typedef struct HAL_GPIO_t {
    HAL_GPIO_PORT port;
    uint8_t pin;
} HAL_GPIO_t;

void HAL_GPIO_init_output(HAL_GPIO_PORT port, uint8_t pin);
void HAL_GPIO_init_output_mask(HAL_GPIO_PORT port, uint8_t mask);
void HAL_GPIO_write_port(HAL_GPIO_PORT port, uint8_t mask);
void HAL_GPIO_write_bit(HAL_GPIO_PORT port, uint8_t bit, uint8_t value);

void HAL_GPIO_init_input(HAL_GPIO_PORT port, uint8_t pin, uint8_t isPullup);
void HAL_GPIO_init_input_mask(HAL_GPIO_PORT port, uint8_t mask, uint8_t isPullup);
uint8_t HAL_GPIO_read_port(HAL_GPIO_PORT port);
uint8_t HAL_GPIO_read_bit(HAL_GPIO_PORT port, uint8_t bit);


#endif // HAL_GPIO_H