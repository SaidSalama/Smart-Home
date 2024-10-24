/*
 * Smar_Home.c
 *
 * Created: 9/25/2021 11:59:52 AM
 *  Author: Said Salama
 */ 
#include <avr/io.h>
#include "GPIO_AVR.h"
#include "GPIO_AVR_PORTS.h"
#include "LCD.h"
#include "keypad.h"
#include "Smart home1.h"
#include "LCD.h"
#include <util/delay.h>
char colloc;
char rowloc;
void Enter_Home()
{
	_delay_ms(2000);
	password_init();
	keypad_password(&colloc,&rowloc);
	_delay_ms(2000);
}
void Door_Init()
{
	DDRD |= (1<<PD5);	/* Make OC1A pin as output */
	TCNT1 = 0;		/* Set timer1 count zero */
	ICR1 = 2499;		/* Set TOP count for timer1 in ICR1 register */

	/* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
}
void Open_The_Door()
{
	OCR1A = 300;	/* Set servo shaft at 90° position */
}
void Close_The_Door()
{
	OCR1A = 70;	/* Set servo shaft at -90° position */
}
void Alarm()
{
	pin_direction(DDrD,6,output);
	pin_direction(DDrD,7,output);
	pin_direction(DDrA,5,output);				//fire lamp output
	pin_set(portD,6);
	pin_reset(portD,7);
	pin_reset(portA,5);
	_delay_ms(400);
	pin_set(portD,7);
	pin_set(portD,6);
	pin_set(portA,5);
	_delay_ms(400);
}
void Stop_Alarm()
{
	pin_reset(portD,6);
	pin_reset(portD,7);
	pin_reset(portA,5);
}

void TURN_ON_ROOM1()
{
	pin_reset(portA,ROOM1);
}
void TURN_OFF_ROOM1()
{
	pin_set(portA,ROOM1);
}
void TURN_ON_FAN()
{
	pin_reset(portA,FAN);
}
void TURN_OFF_FAN()
{
	pin_set(portA,FAN);
}

void Controlled_mode()
{
	usart_send_string("You are in control mode\n");
	Select_device();
}
void Automatic_mode()
{
	  usart_send_string("You are in Automatic mode\n");
	  usart_send_string("press any key to exit mode\n");
	  int x;
	  char temperature[3];
	  int y;
	  char light[3];
	  while(!(UCSRA&(1<<RXC)))				// loop until any data sent from mobile(UART)
	{
			adc_init(0);						// initialize adc for temp sensor with interrupt			
			x=read_adc(0);
			ADC=0;
			itoa(x,temperature,10);
			LCD_Command(0x80);
			lcd_print("Temperature = ");
			lcd_print(temperature);
			 if((x>35)&&(x<70))
			 {
				 TURN_ON_FAN();
			 }
			 else
			 {
				 TURN_OFF_FAN();
			 }
			_delay_ms(1000);
			adc_init(1);					//initilaize adc for ldr sensor without interrupt 
			y=read_adc(1);
			ADC=0;
			itoa(y,light,10);
			LCD_Command(0xc0);
			lcd_print("Light  =     ");
			lcd_print(light);
			if(y>400)
			{
				TURN_OFF_ROOM1();
			}
			else
			{
				TURN_ON_ROOM1();
			}
			_delay_ms(1000);
			
			
	}
	LCD_Command(clear);
	  
}
void Select_device()
{
		char control;
		char device;
		usart_send_string("1-ROOM  2-FAN  3-Exit mode");
		control=usart_read();
		while(control!='3')
		{
			if(control=='1')
			{
				usart_send_string(" Room:   1-ON  2-OFF");
				device=usart_read();
				if(device=='1')
				{
					TURN_ON_ROOM1();
					
				}
				else if(device=='2')
				{
					TURN_OFF_ROOM1();
					
				}
			
			}
			else if(control=='2')
			{
				usart_send_string("Fan:   1-ON  2-OFF");
				device=usart_read();
				if(device=='1')
				{
					TURN_ON_FAN();
				}
				else if(device=='2')
				{
					TURN_OFF_FAN();
				}
				
			
			}
			usart_send_string("1-ROOM  2-FAN  3-Exit mode");
			control=usart_read();
			
		}
}
void Initialize_smart_home()
{
		usart_init();
		pin_direction(DDrA,FAN,output);
		pin_direction(DDrA,ROOM1,output);
		TURN_OFF_FAN();
		TURN_OFF_ROOM1();
		usart_send_string("Welcome to smart home\n");
		usart_send_string("Select the mode\n");
		usart_send_string("1-Controlled 2-Automatic\n");
}