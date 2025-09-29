/*
 * max7219.h
 *
 * Created: 2025-09-29 13:06:09
 *  Author: joela
 */ 


#ifndef MAX7219_H_
#define MAX7219_H_

#include <stdint.h>

typedef struct {
	
	uint8_t din_pin;
	uint8_t clk_pin;
	uint8_t cs_pin;
	
} max7219_t;

max7219_init(uint8_t din_pin, uint8_t clk_pin, uint8_t cs_pin);
void max7219_write_byte(max7219_t *max7219, uint8_t byte);
void max7219_send_data(max7219_t *max7219, uint8_t address, uint8_t data);


#endif /* MAX7219_H_ */