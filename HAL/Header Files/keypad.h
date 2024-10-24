/*
 * keypad.h
 *
 * Created: 2/28/2021 11:16:00 PM
 *  Author: Said Salama
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#define key_port  portC
char* read_col(char *ptrcolloc);
void keypad_init();
void let_release(char *ptrcolloc);
void check_for_press(char*ptrcolloc);
void row_check(char*ptrcolloc,char*ptrrowloc);
keypad_function(char*ptrcolloc,char*ptrrowloc);
get_password(char*ptrcolloc,char*ptrrowloc,char* passwordd,char i);
void use_keypad(char password1[]);
keypad_password(char*ptrcolloc,char*ptrrowloc);
void password_init();



#endif /* KEYPAD_H_ */