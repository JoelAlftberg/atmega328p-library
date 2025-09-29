/*
 * usart.h
 *
 * Created: 2025-09-27 17:20:19
 *  Author: joela
 */ 


#ifndef USART_H_
#define USART_H_

void usart_init(uint32_t baud_rate);
uint8_t usart_recieve_char(void);
void usart_transmit_char(uint8_t character);


#endif /* USART_H_ */