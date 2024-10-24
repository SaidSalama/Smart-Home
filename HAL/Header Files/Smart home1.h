/*
 * Smart_home1.h
 *
 * Created: 9/25/2021 11:58:38 AM
 *  Author: Said Salama
 */ 


#ifndef SMART HOME1_H_
#define SMART HOME1_H_

#define ROOM1 6
#define  FAN 7
#define Controlled '1'
#define Automatic  '2'
 void Enter_Home();
 void Door_Init()
 void Open_The_Door();
 void Close_The_Door();
 void Alarm();
 void Stop_Alarm();
 void TURN_ON_ROOM1();
 void TURN_OFF_ROOM1();
 void TURN_ON_FAN();
 void TURN_OFF_FAN();
 void Controlled_mode();
 void Automatic_mode();
 void Select_device();
 void Initialize_smart_home();
#endif /* SMART HOME1_H_ */