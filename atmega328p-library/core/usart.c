/*
 * usart.c
 *
 * Created: 2025-09-23 09:23:10
 *  Author: Joel Alftberg
 */ 

#include <avr/io.h>
#include <stdint.h>

#define F_CPU 16000000UL // 16 MHz clock frequency


/************************************************************************
* Function name: serial_init (uint32_t baud_rate)
* parameter 1: baud_rate is used to calculate the value for the UBRR register
* Enable RX/TX, sets character size and sets the UBRR value
************************************************************************/
void usart_init(uint32_t baud_rate){

	// Enable double speed mode
	/*	UCSR0A = (1 << U2X0);*/
	
	// Calculate UBRR value ex. 8 for 115200 baud rate
	uint16_t ubrr = ((F_CPU + (baud_rate * 8UL)) / (16UL * baud_rate)) - 1; 
	UBRR0H = (uint8_t) (ubrr >> 8); // set high bits
	UBRR0L = (uint8_t) ubrr; // set low bits
	
	// Set character size bits to 011, 8-bit per character
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); 
	
	// Enable RX (bit-4 of USART Control/Status register B)
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	
}

uint8_t usart_recieve_char(void){
	
	// Wait until RX Complete flag is set
	while(!(UCSR0A & (1 << RXC0)));
	
	// Return the data from the USART Data Register
	return UDR0; 
	
}

void usart_transmit_char(uint8_t character){
	
	// Wait for the USART Data Register Empty flag to be 0
	while(!(UCSR0A & (1 << UDRE0)));
	
	// Write the character to the USART Data Register
	UDR0 = character;
	
}



