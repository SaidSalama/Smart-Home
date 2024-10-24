/*
 * LCD.c
 *
 * Created: 2/27/2021 9:05:33 PM
 *  Author: Said Salama
 */ 
#include "LCD.h"
#include "GPIO_AVR.h"
#include "GPIO_AVR_PORTS.h"
#include <util/delay.h>
#include <avr/io.h>
void lcd_init()							//initializing the lcd in mode 4
{
	port_direction(LCD_DDr,output);
	_delay_ms(20);
	LCD_Command(0x33);
	_delay_ms(20);
	LCD_Command(0x32);	/* Send for 4 bit initialization of LCD  */
	_delay_ms(20);
	LCD_Command(0x28);	/* 2 line, 5*7 matrix in 4-bit mode */
	_delay_ms(20);
	LCD_Command(0x0c);	/* Display on cursor off */
	_delay_ms(20);
	LCD_Command(0x06);	/* Increment cursor (shift cursor to right) */
	_delay_ms(20);
	LCD_Command(0x01);	/* Clear display screen */
	_delay_ms(20);
	
}
void LCD_Command(char cmnd )
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0);/* Sending upper nibble */
	LCD_Port &= ~ (1<<RS);		/* RS=0, command reg. */
	LCD_Port |= (1<<E);		/* Enable pulse */
	_delay_us(1);
	LCD_Port &= ~ (1<<E);
	_delay_us(200);
	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);/* Sending lower nibble */
	LCD_Port |= (1<<E);
	_delay_us(1);
	LCD_Port &= ~ (1<<E);
	_delay_ms(2);
	
}
lcd_out(char data)
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0);/* Sending upper nibble */
	LCD_Port |= (1<<RS);  /* RS=1, data reg. */
	LCD_Port|= (1<<E);
	_delay_us(1);
	LCD_Port &= ~ (1<<E);
	_delay_us(200);
	LCD_Port = (LCD_Port & 0x0F) | (data << 4);  /* Sending lower nibble */
	LCD_Port |= (1<<E);
	_delay_us(1);
	LCD_Port &= ~ (1<<E);
	_delay_ms(2);
}
lcd_print(char*str)
{
	unsigned char i =0;
	while(str[i]!=0)
	{
		lcd_out(str[i]);
		i++;
	}
	
}