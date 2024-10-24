/*
 * uart.h
 *
 * Created: 2/24/2021 8:13:04 PM
 *  Author: Said Salama
 */ 


#ifndef UART_H_
#define UART_H_

void usart_send(unsigned char ch);
unsigned char usart_read();
void usart_send_string(char *str);
void usart_init();
void usart_read_string();

#define BAUDRATE 9600
#define BAUD_PRESCALER ((F_CPU/(BAUDRATE*16UL))-1)
#define F_CPU 8000000UL



#endif /* UART_H_ */