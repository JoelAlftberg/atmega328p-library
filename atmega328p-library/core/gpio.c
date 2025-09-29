/*
 * gpio.c
 *
 * Created: 2025-09-27 11:00:13
 *  Author: joela
 */ 
#include <avr/io.h>
#include "../include/gpio.h"
#define NOP() __asm__ __volatile__("nop") // Define NOP instruction


// Mapping for the arduino digital pins
const pin_mapping_t arduino_mapping_digital[] = {
	{ &PORTD, &DDRD, &PIND, 0},
	{ &PORTD, &DDRD, &PIND, 1},
	{ &PORTD, &DDRD, &PIND, 2},
	{ &PORTD, &DDRD, &PIND, 3},
	{ &PORTD, &DDRD, &PIND, 4},
	{ &PORTD, &DDRD, &PIND, 5},
	{ &PORTD, &DDRD, &PIND, 6},
	{ &PORTD, &DDRD, &PIND, 7},
	{ &PORTB, &DDRB, &PINB, 0},
	{ &PORTB, &DDRB, &PINB, 1},
	{ &PORTB, &DDRB, &PINB, 2},
	{ &PORTB, &DDRB, &PINB, 3},
	{ &PORTB, &DDRB, &PINB, 4},
	{ &PORTB, &DDRB, &PINB, 5}
};


// Mapping for the arduino analog pins
const pin_mapping_t arduino_mapping_analog[] = {
	{ &PORTC, &DDRC, &PINC, 0},
	{ &PORTC, &DDRC, &PINC, 1},
	{ &PORTC, &DDRC, &PINC, 2},
	{ &PORTC, &DDRC, &PINC, 3},
	{ &PORTC, &DDRC, &PINC, 4},
	{ &PORTC, &DDRC, &PINC, 5}
};



// Sets the bit corresponding to the pin in the data direction register
/* TOOD: add input pullup */

void gpio_set_direction(uint8_t pin_number, mode_t pin_mode){
	 if (pin_mode == OUTPUT){
		 *arduino_mapping_digital[pin_number].ddr |= (1 << arduino_mapping_digital[pin_number].bit);
	 }
	 else if (pin_mode == INPUT){
		 *arduino_mapping_digital[pin_number].ddr &= ~(1 << arduino_mapping_digital[pin_number].bit);
	 }
}

// Sets the bit corresponding to the pin in the PORT register
void gpio_digital_write(uint8_t pin_number, digital_state_t state){
	
	if (state == HIGH)
	{
		*arduino_mapping_digital[pin_number].port |= (1 << arduino_mapping_digital[pin_number].bit);
	}
	else{
		*arduino_mapping_digital[pin_number].port &= ~(1 << arduino_mapping_digital[pin_number].bit);
	}
	
}

// Reads the Input from the pin and checks if it's high or low
uint8_t gpio_digital_read(uint8_t pin_number){
	return (*arduino_mapping_digital[pin_number].pin & (1 << arduino_mapping_digital[pin_number].bit)) ? 1: 0;
}

void gpio_pulse(uint8_t pin){
	gpio_digital_write(pin, HIGH);
	NOP();
	gpio_digital_write(pin, LOW);
	NOP();
}
