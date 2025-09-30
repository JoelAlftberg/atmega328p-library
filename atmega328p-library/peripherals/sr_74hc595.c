/*
 * _74hc595.c
 *
 * Created: 2025-09-27 13:11:37
 *  Author: Joel Alftberg
 */ 

#include "../include/gpio.h"
#include "../include/sr_74hc595.h"


// Initialize a new register and set chosen pins to output mode
shift_register_t shift_register_init(uint8_t ser_pin_number, uint8_t rclk_pin_number, uint8_t srclk_pin_number, uint8_t srclr_pin_number){
	gpio_set_direction(ser_pin_number, OUTPUT);
	gpio_set_direction(rclk_pin_number, OUTPUT);
	gpio_set_direction(srclk_pin_number, OUTPUT);
	gpio_set_direction(srclr_pin_number, OUTPUT);

	shift_register_t new_register = {
		.ser = ser_pin_number,
		.rclk = rclk_pin_number,
		.srclk = srclk_pin_number,
		.srclr = srclr_pin_number
	};
	
	shift_register_clear(&new_register);
	
	return new_register;
	
}


// Function to clear the register
void shift_register_clear(shift_register_t *shift_reg){
	
	gpio_digital_write(shift_reg->srclr, LOW);
	gpio_digital_write(shift_reg->srclr, HIGH);
	
}

// Write a single bit and send to shift register
void shift_register_write_bit(shift_register_t *shift_reg, uint8_t bit){
	
	gpio_digital_write(shift_reg->ser, bit  ? HIGH: LOW);
	gpio_pulse(shift_reg->srclk);
	
}

void shift_register_write_byte(shift_register_t *shift_reg, uint8_t byte){
	
	for(int8_t i = 0; i < 8; i++){
		// shift each bit of the byte and mask
		shift_register_write_bit(shift_reg, (byte >> i) & 0x01);
	}
	gpio_pulse(shift_reg->rclk);
	
}

	
