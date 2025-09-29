/*
 * _74hc595.h
 *
 * Created: 2025-09-27 17:21:32
 *  Author: Joel Alftberg
 */ 


#ifndef SR_74HC595_H_
#define SR_74HC595_H_

#include <stdint.h>

typedef struct {
	
	uint8_t ser;
	uint8_t rclk;
	uint8_t srclk;
	uint8_t srclr;
	
	} shift_register_t;

shift_register_t shift_register_init(uint8_t ser_pin_number, uint8_t rclk_pin_number, uint8_t srclk_pin_number, uint8_t srclr_pin_number);
void shift_register_clear(shift_register_t *shift_reg);
void shift_register_write_bit(shift_register_t *shift_reg, uint8_t bit);
void shift_register_write_byte(shift_register_t *shift_reg, uint8_t byte);


#endif /* SR_74HC595_H_ */