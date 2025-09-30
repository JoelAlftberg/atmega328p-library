/*
 * delay.c
 *
 * Created: 2025-09-30 09:35:58
 *  Author: joela
 */ 

#include "../include/delay.h"

void delay_millis(uint16_t milliseconds){
	for (uint16_t i = 0; i < milliseconds; i++) {
		_delay_ms(1);
	}
}
