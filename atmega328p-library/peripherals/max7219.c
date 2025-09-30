/*
 * max7219.c
 *
 * Created: 2025-09-28 08:08:03
 *  Author: Joel Alftberg
 */ 

#include <stdint.h>
#include "../include/gpio.h"
#include "../include/max7219.h"
#include "../include/delay.h"

// Some helpful addresses to different commands
#define MAX7219_DECODE_MODE_ADDR 0x09
#define MAX7219_INTENSITY_ADDR 0x0A
#define MAX7219_SCAN_LIMIT_ADDR  0x0B
#define MAX7219_SHUTDOWN_ADDR    0x0C


// Initialize max7219 struct and send some settings commands
max7219_t max7219_init(const uint8_t din_pin, const uint8_t clk_pin, const uint8_t cs_pin, const uint8_t intensity){
	
	gpio_set_direction(din_pin, OUTPUT);
	gpio_set_direction(clk_pin, OUTPUT);
	gpio_set_direction(cs_pin, OUTPUT);
	
	max7219_t new_max7219 = {
		.din_pin = din_pin,
		.clk_pin = clk_pin,
		.cs_pin = cs_pin,
		.intensity = intensity		
	};

	max7219_send_data(&new_max7219, MAX7219_SHUTDOWN_ADDR, 0x01); // Set normal operation mode	
	max7219_send_data(&new_max7219, MAX7219_SCAN_LIMIT_ADDR, 0x07); // Show all digits
	max7219_send_data(&new_max7219, MAX7219_DECODE_MODE_ADDR, 0x00); // No decode mode active
	max7219_send_data(&new_max7219, MAX7219_INTENSITY_ADDR, intensity); // Set intensity
	
	return new_max7219;
}

// Send one byte and trigger clock pin
void max7219_write_byte(max7219_t *max7219, const uint8_t byte){
	for(int8_t i = 7; i >= 0; i--){
		gpio_digital_write( max7219->din_pin,(byte >> i) & 0x01);
		gpio_pulse(max7219->clk_pin);
	}
}

// Set chip-select low, send address and data bytes, then set chip-select high
void max7219_send_data(max7219_t *max7219, const uint8_t address, const uint8_t data){
	gpio_digital_write(max7219->cs_pin, LOW);
	max7219_write_byte(max7219, address);
	max7219_write_byte(max7219, data);
	gpio_digital_write(max7219->cs_pin, HIGH);
}

// Raise or lower the intensity output
void max7219_change_intensity(max7219_t *max7219, const uint8_t target_intensity, const uint16_t delay_ms){
	
	// Catch if we are targeting outside intensity bounds
	if(target_intensity > 0x0F){
		return;
	}
	
	// Check if we are raising or lowering intensity
	if(max7219->intensity < target_intensity){
		while(max7219->intensity < target_intensity){
			max7219->intensity++;
			max7219_send_data(max7219, MAX7219_INTENSITY_ADDR, max7219->intensity);
			delay_millis(delay_ms);
		}
	}
	else{
		while(max7219->intensity > target_intensity){
			max7219->intensity--;
			max7219_send_data(max7219, MAX7219_INTENSITY_ADDR, max7219->intensity);
			delay_millis(delay_ms);
		}
	}
	
}

void max7219_display_symbol(max7219_t *max7219, const uint8_t symbol[8]){
	
		for (uint8_t column = 1; column <= 8; column++) {
			max7219_send_data(max7219, column, symbol[column - 1]); // light all 8 LEDs in this 
		}
		
}