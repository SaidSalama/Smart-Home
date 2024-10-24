/*
 * LCD.h
 *
 * Created: 2/27/2021 9:04:33 PM
 *  Author: Said Salama
 */ 


#ifndef LCD_H_
#define LCD_H_
#define clear 0x01
#define Data_port  portB
#define Command_port portB
#define RS 0
#define E  1
#define LCD_DDr DDrB
#define LCD_Port PORTB



void lcd_init();
void LCD_Command(char cmd);
void lcd_out(char);
void lcd_print(char*str);



#endif /* LCD_H_ */