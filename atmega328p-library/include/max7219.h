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
	uint8_t intensity;
	
} max7219_t;

max7219_t max7219_init(uint8_t din_pin, uint8_t clk_pin, uint8_t cs_pin, uint8_t intensity);
void max7219_write_byte(max7219_t *max7219, uint8_t byte);
void max7219_send_data(max7219_t *max7219, uint8_t address, uint8_t data);
void max7219_change_intensity(max7219_t *max7219, uint8_t target_intensity, uint16_t delay_ms);
void max7219_display_symbol(max7219_t *max7219, const uint8_t symbol[8]);



#endif /* MAX7219_H_ */