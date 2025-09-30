/*
 * gpio.h
 *
 * Created: 2025-09-27 16:28:48
 *  Author: joela
 */ 


#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>


typedef struct {
	volatile uint8_t *port;
	volatile uint8_t *ddr;
	volatile uint8_t *pin;
	uint8_t bit;
	
} pin_mapping_t;

typedef enum {
	LOW, HIGH
} digital_state_t;

typedef enum {
	INPUT, OUTPUT
} mode_t;

void gpio_set_direction(uint8_t pin_number, mode_t pin_mode);
void gpio_digital_write(uint8_t pin_number, digital_state_t state);
uint8_t gpio_digital_read(uint8_t pin_number);
void gpio_pulse(uint8_t pin);

#endif /* GPIO_H_ */