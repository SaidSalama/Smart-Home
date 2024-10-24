/*
 * CFile1.c
 *
 * Created: 3/31/2021 9:44:37 PM
 *  Author: Said Salama
 */ 
#undef F_CPU
#define F_CPU 8000000UL



#include <avr/io.h>
#include <stdio.h>
#include "GPIO_AVR.h"
#include "GPIO_AVR_PORTS.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "LCD.h"
#include "keypad.h"
extern uint16_t x;
extern char temp[];

void adc_init(uint8_t channel)
{
	pin_direction(DDrA,channel,input);
	ADMUX|=(1<<REFS0);														//Vref= Vcc 5v
	ADCSRA|=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2)|(1<<ADATE);			//enable ADC 128 division factor 
}
int read_adc(uint8_t channel)
{
	ADMUX&=0xF0;						//clear old reading
	ADMUX|=channel;
	start_conversion();
	while(!(ADCSRA&(1<<ADIF)));
	ADCSRA|=(1<<ADIF);
	_delay_ms(100);
	return   ((ADCL+256*ADCH)/2);
}
start_conversion()
{
	ADCSRA|=(1<<ADSC);
}
//int main()
//{
	//adc_init(0);
	//lcd_init();
	//while(1)
	//{
		
		//x=read_adc(0);
		//itoa(x,temp,10);
		//_delay_ms(200);
		//lcd_print(temp);
		//_delay_ms(200);
		//lcd_command(clear);
		//_delay_ms(200);
	//}
//}
// programming ADC with interrupts 
//ISR(ADC_vect)
//{
	//x=(ADCL+256*ADCH)/4;
	//itoa(x,temp,10);
	//lcd_print(" temperature= ");
	//lcd_print(temp);
	//_delay_ms(1000);
	//lcd_command(clear);
	//start_conversion();
//}