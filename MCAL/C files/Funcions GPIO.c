/*
 * Funcions_GPIO.c
 *
 * Created: 2/15/2021 9:48:13 PM
 *  Author: Said Salama
 */ 

#include"GPIO_AVR_PORTS.h"
#include <avr/io.h>
void stepper_motor();
void stepper_motor()
{
	pin_reset(portD,3);
	pin_set(portD,0);
	_delay_ms(80);
	pin_set(portD,1);
	_delay_ms(80);
	pin_reset(portD,0);
	_delay_ms(80);
	pin_set(portD,2);
	_delay_ms(80);
	pin_reset(portD,1);
	_delay_ms(80);
	pin_set(portD,3);
	_delay_ms(80);
	pin_reset(portD,2);
	_delay_ms(80);
}
void pin_direction( char DDrX, char pin, char state)
{
	if (state==output)
	{
		pin_set((DDrX),  pin);
	}
	else
		pin_reset((DDrX),  pin);
}
void port_direction( char DDrX, char state)
{
	if (state==output)
	(*(volatile char *)(DDrX))=0xff;
	else
	(*(volatile  char *)(DDrX))=0x00;
}
char port_read(char pinX)
{
	char x;
	x=(*(volatile char*)(pinX));
	return x;
}
void port_write( char portX,char value)
{
	(*(volatile char*)(portX))=value;

}
char pin_read(char pinX,char pin)
{
	char x;
	x=(*(volatile char*)(pinX))&(1<<pin);
	return x;
}

void pin_set(char reg,char pin)
{
	
	*((volatile char*)(reg))|=(1<<pin);
}
void pin_reset(char reg,char pin)
{
	
	*((volatile char*)(reg))&= ~(1<<pin);
}
void Delay_half_sec()
{
	TCNT0=0x00;
	TCCR0=0x05;
	char countt=0;
	while(countt<15)
	{
		while((TIFR&(1<<TOV0))==0);
		TCNT0=0x00;
		TIFR=0x01;
		countt++;
	}
	countt=0;
	return;
}