/*
 * cd4026be.c
 *
 * Created: 2025-09-29 10:28:34
 *  Author: Joel Alftberg 0x4A.0x41
 */ 

#define F_CPU 16000000UL // 16 MHz clock frequency

#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>

#include "../include/gpio.h"
#include "../include/cd4026be.h"

cd4026be_t cd4026be_init(uint8_t digit_1_pin, uint8_t digit_2_pin, uint8_t digit_3_pin, uint8_t digit_4_pin, uint8_t reset_pin, uint8_t clock_pin){
	
	cd4026be_t new_cd4026be = {
		.digit_pins = {digit_1_pin, digit_2_pin, digit_3_pin, digit_4_pin},
		.reset_pin = reset_pin,
		.clock_pin = clock_pin
	};
	
	cd4026be_reset(&new_cd4026be);
	
	return new_cd4026be;
}

void cd4026_reset(cd4026be_t *cd4026be){
	gpio_pulse(cd4026be->reset_pin);
}

void cd4026be_select_digit(cd4026be_t *cd4026be, uint8_t digit_pos){
	
	
	/* Turn all digits off by setting HIGH */
	for(int i = 0; i < 4; i++){
		gpio_digital_write(cd4026be->digit_pins[i], HIGH);
	}

	if (digit_pos == 0 || digit_pos > 4) return;

	uint8_t digit_index = digit_pos - 1;
	/* Turn selected digit on by setting LOW*/
	gpio_digital_write(cd4026be->digit_pins[digit_index], LOW);
	
}

void cd4026be_generate_digit(cd4026be_t *cd4026be ,uint8_t digit, uint8_t digit_pos){
	
	if (digit > 9){
		return;
	}
	
	// Generate the digit with pulses
	for(uint8_t i = 0; i < digit; i++){
		gpio_pulse(cd4026be->clock_pin);	
	}
	
	cd4026be_select_digit(cd4026be, digit_pos);
	
}

void cd4026be_display_number(cd4026be_t *cd4026be ,uint16_t number){
	
	// Display the number 0 in digit 4 position
	if (number == 0){
		cd4026be_reset(cd4026be);
		cd4026be_generate_digit(cd4026be, 0, 4); 
	}
	
	uint8_t digits[4];
	
	bool leading_zero = true;
	
	digits[0] = (number / 1000) % 10;
	digits[1] = (number / 100) % 10;
	digits[2] = (number / 10) % 10;
	digits[3] = number % 10;
	
	for(uint8_t i = 0; i < 4; i++){
		if (digits[i] != 0){
			leading_zero = false;
		}
		
		// If digit is zero, turn all digits off
		if(leading_zero){
			cd4026be_select_digit(cd4026be,0); 
		}
		else{
			cd4026be_reset(cd4026be);
			cd4026be_generate_digit(cd4026be, digits[i], i + 1);
		}
		_delay_ms(2);
		cd4026be_select_digit(cd4026be, 0);
	}
	
}

