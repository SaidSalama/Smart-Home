/*
 * KeyPad.c
 *
 * Created: 2/28/2021 10:38:48 PM
 *  Author: Said Salama
 */ 
#include "GPIO_AVR.h"
#include "GPIO_AVR_PORTS.h"
#include "keypad.h"
#include <util/delay.h>
#include <avr/io.h>
 char colloc;
 char rowloc;
extern char* ptrcolloc ;
extern char* ptrrowloc ;
char *test;

  char keypad[4][4]=  {			   '1','2','3','A',
									'4','5','6','B',
									'7','8','9','C',
									'*','0','=','D'};
										
char i=0;

keypad_init()
{
	port_write(DDrC,0xf0);
	port_write(key_port,0xff);
}
char* read_col(char *ptrcolloc)
{
	*ptrcolloc=(*((volatile char*)pinC))&=0b00001111 ;
	return *ptrcolloc;
}
void check_for_press(char*ptrcolloc)					//a key is pressed if one bit of the coloumn is 0
{
	do
	{
		do
		{	_delay_ms(20);
			*ptrcolloc=read_col(&colloc);
		} while (*ptrcolloc==0b00001111);
		_delay_ms(20);
		*ptrcolloc=read_col(&colloc);
	} while (*ptrcolloc==0b00001111);
}
void let_release(char *ptrcolloc)					//let the key be realeased
{
	do
	{
		port_write(key_port,0b00001111);
		*ptrcolloc =read_col(&colloc);
		
	} while (*ptrcolloc!=0b00001111);
}
void row_check(char*ptrcolloc,char*ptrrowloc)					//check the row pressed
{
	while(1)
	{
		port_write(key_port,0b11101111);
		*ptrcolloc=read_col(&colloc);
		if(*ptrcolloc!=0b00001111)
		{
			*ptrrowloc=3;
			break;
		}
		port_write(key_port,0b11011111);
		*ptrcolloc=read_col(&colloc);
		if(*ptrcolloc!=0b00001111)
		{
			*ptrrowloc=2;
			break;
		}
		port_write(key_port,0b10111111);
		*ptrcolloc=read_col(&colloc);
		if(*ptrcolloc!=0b00001111)
		{
			*ptrrowloc=1;
			break;
		}
		port_write(key_port,0b01111111);
		*ptrcolloc=read_col(&colloc);
		if(*ptrcolloc!=0b00001111)
		{
			*ptrrowloc=0;
			break;
		}
	}
}


keypad_function(char*ptrcolloc,char*ptrrowloc)					//printing the pressed num on LCD
{
	if(*ptrcolloc==0b00001110)
	{
		lcd_out(keypad[*ptrrowloc][3]);
		
	}
	else if(*ptrcolloc==0b0001101)
	{
		lcd_out(keypad[*ptrrowloc][2]);
		
	}
	else if(*ptrcolloc==0b00001011)
	{
		lcd_out(keypad[*ptrrowloc][1]);
		
	}
	else
	{
		lcd_out(keypad[*ptrrowloc][0]);
		
	}
}




keypad_password(char*ptrcolloc,char*ptrrowloc)
{
		char i=0;
	    unsigned char passwordd[4];
		for(i=0;i<3;i++)
		{
				
				let_release(&colloc);									
				check_for_press(&colloc);
				row_check(&colloc,&rowloc);
				keypad_function(&colloc,&rowloc);
				get_password(&colloc,&rowloc,passwordd,i);
					
		}
		if((passwordd[0]=='0')&&(passwordd[1]=='0')&&(passwordd[2]=='0'))				//Password is 000
		{
			_delay_ms(2000);
			LCD_Command(0x01);
			_delay_ms(200);
			lcd_print("Welcome Said");
			_delay_ms(30000);
			LCD_Command(0x01);
		}
		else
		{
			_delay_ms(2000);
			LCD_Command(0x01);
			_delay_ms(200);
			lcd_print("Wrong password");
			_delay_ms(30000);
			LCD_Command(0x01);
			Enter_Home();
		}
		
		
}

void password_init()
{
	LCD_Command(0x01);
	_delay_ms(200);
	lcd_print("Enter Password...");
	_delay_ms(30000);
	LCD_Command(0x01);
}






get_password(char*ptrcolloc,char*ptrrowloc,char *passwordd,char i)
{
	
		if(*ptrcolloc==0b00001110)
		{
			//lcd_out(keypad[*ptrrowloc][3]);
			passwordd[i]=(keypad[*ptrrowloc][3]);
			//lcd_out(passwordd[i]);
		}
		else if(*ptrcolloc==0b0001101)
		{
			//lcd_out(keypad[*ptrrowloc][2]);
			passwordd[i]=(keypad[*ptrrowloc][2]);
			//lcd_out(passwordd[i]);
		}
		else if(*ptrcolloc==0b00001011)
		{
			//lcd_out(keypad[*ptrrowloc][1]);
			passwordd[i]=(keypad[*ptrrowloc][1]);
			//lcd_out(passwordd[i]);
		}
		else
		{
			//lcd_out(keypad[*ptrrowloc][0]);
			passwordd[i]=(keypad[*ptrrowloc][0]);
			//lcd_out(passwordd[i]);
		}
		
}