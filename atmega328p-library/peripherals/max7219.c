/*
 * max7219.c
 *
 * Created: 2025-09-28 08:08:03
 *  Author: Joel Alftberg
 */ 

#include <stdint.h>
#include "../include/gpio.h"
#include "../include/max7219.h"

max7219_t max7219_init(uint8_t din_pin, uint8_t clk_pin, uint8_t cs_pin){
	
	gpio_set_direction(din_pin, OUTPUT);
	gpio_set_direction(clk_pin, OUTPUT);
	gpio_set_direction(cs_pin, OUTPUT);
	
	max7219_t new_max7219 = {
		.din_pin = din_pin,
		.clk_pin = clk_pin,
		.cs_pin = cs_pin
	};
	
	return new_max7219;
}

void max7219_write_byte(max7219_t *max7219, uint8_t byte){
	for(int8_t i = 7; i >= 0; i--){
		gpio_digital_write( max7219->din_pin,(byte >> i) & 0x01);
		gpio_pulse(max7219->clk_pin);
	}
}

void max7219_send_data(max7219_t *max7219, uint8_t address, uint8_t data){
	gpio_digital_write(max7219->cs_pin, LOW);
	max7219_write_byte(max7219, address);
	max7219_write_byte(max7219, data);
	gpio_digital_write(max7219->cs_pin, HIGH);
}
