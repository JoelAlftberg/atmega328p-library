/*
 * delay.h
 *
 * Created: 2025-09-30 09:37:13
 *  Author: joela
 */ 


#ifndef DELAY_H_
#define DELAY_H_


#define F_CPU 16000000UL // 16 MHz clock frequency

#include <util/delay.h>

void delay_millis(uint16_t milliseconds);


#endif /* DELAY_H_ */