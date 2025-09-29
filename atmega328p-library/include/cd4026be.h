/*
 * cd4026be.h
 *
 * Created: 2025-09-29 13:07:17
 *  Author: joela
 */ 


#ifndef CD4026BE_H_
#define CD4026BE_H_

#include <stdint.h>

typedef struct {
	
	uint8_t digit_pins[4];
	uint8_t reset_pin;
	uint8_t clock_pin;
	
} cd4026be_t;

cd4026be_t cd4026be_init(uint8_t digit_1_pin, uint8_t digit_2_pin, uint8_t digit_3_pin, uint8_t digit_4_pin, uint8_t reset_pin, uint8_t clock_pin);
void cd4026be_reset(cd4026be_t *cd4026be);
void cd4026be_select_digit(cd4026be_t *cd4026be, uint8_t digit_pos);
void cd4026be_generate_digit(cd4026be_t *cd4026be ,uint8_t digit, uint8_t digit_pos);
void cd4026be_display_number(cd4026be_t *cd4026be ,uint16_t number);



#endif /* CD4026BE_H_ */