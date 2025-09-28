/*
 * max7219.c
 *
 * Created: 2025-09-28 08:08:03
 *  Author: Joel Alftberg
 */ 

#define F_CPU 16000000UL // 16 MHz clock frequency

#include <stdint.h>
#include "../include/gpio.h"
#include <util/delay.h>

typedef struct {
	
	uint8_t din_pin;
	uint8_t clk_pin;
	uint8_t cs_pin;
	
	} max7219_t;

static inline void pulse(uint8_t pin) {
	gpio_digital_write(pin, HIGH);
	_delay_us(1);
	gpio_digital_write(pin, LOW);
	_delay_us(1);
}

max7219_t max7219_init(uint8_t din_pin, uint8_t clk_pin, uint8_t cs_pin){
	
	gpio_set_direction(din_pin, OUTPUT);
	gpio_set_direction(clk_pin, OUTPUT);
	gpio_set_direction(cs_pin, OUTPUT);
	
	max7219_t new_max7219 = {
		.din_pin = din_pin;
		.clk_pin = clk_pin;
		.cs_pin = cs_pin;
	};
	
	return new_max7219;
}

void max7219_write_byte(max7219_t *max7219, uint8_t byte){
	for(int8_t i = 7; i >= 0; i--){
		gpio_digital_write( max7219->din_pin,(byte >> i) & 0x01);
		pulse(max7219->clk_pin);
	}
}
