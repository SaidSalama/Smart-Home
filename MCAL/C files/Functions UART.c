/*
 * Functions_UART.c
 *
 * Created: 2/24/2021 8:19:39 PM
 *  Author: Said Salama
 */ 
#include <avr/io.h>
#include "UART.h"
void usart_init()
{
	UBRRH=(uint8_t)(BAUD_PRESCALER>>8);
	UBRRL=(uint8_t)(BAUD_PRESCALER);
	UCSRC=((1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL));
	UCSRB=((1<<TXEN)|(1<<RXEN));
}
void usart_send(unsigned char ch)
{
	while(!(UCSRA&(1<<UDRE)));
	UDR=ch;
}
unsigned char usart_read()
{
	while(!(UCSRA&(1<<RXC)));
	return (UDR);
}
void usart_send_string(char *str)
{
	unsigned char i=0;
	while(str[i]!=0)
	{
		usart_send(str[i]);
		i++;
	}
	usart_send('\0');							//we have to add the null character at the end of a string
}
usart_read_string()
{
	
	char x;
	do
	{
		x = usart_read();
		lcd_out(x);
	} while (x!='\0');
}