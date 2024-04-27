/*
 * DC_MOTOR_interface.c
 *
 * Created: 10/3/2023 5:26:10 PM
 *  Author: youssef
 */ 

#include "MATH.h"
#include "STD_TYPE.h"
#include "DIO_interface.h"
#include "DC_MOTOR_config.h"

void DCMOTOR_Vid_Init(){
	DIO_Vid_Set_Pin_Dir(DCMOTOR_EN_PORT,DCMOTOR_EN_PIN,OUTPUT);
	DIO_Vid_Set_Pin_Dir(DCMOTOR_A1_PORT,DCMOTOR_A1_PIN,OUTPUT);
	DIO_Vid_Set_Pin_Dir(DCMOTOR_A2_PORT,DCMOTOR_A2_PIN,OUTPUT);
}

void DCMOTOR_Vid_CW(){
	DIO_Vid_Set_Pin_Val(DCMOTOR_EN_PORT,DCMOTOR_EN_PIN,HIGH);
	DIO_Vid_Set_Pin_Val(DCMOTOR_A1_PORT,DCMOTOR_A1_PIN,HIGH);
	DIO_Vid_Set_Pin_Val(DCMOTOR_A2_PORT,DCMOTOR_A2_PIN,LOW);
}

void DCMOTOR_Vid_ACW(){
	DIO_Vid_Set_Pin_Val(DCMOTOR_EN_PORT,DCMOTOR_EN_PIN,HIGH);
	DIO_Vid_Set_Pin_Val(DCMOTOR_A1_PORT,DCMOTOR_A1_PIN,LOW);
	DIO_Vid_Set_Pin_Val(DCMOTOR_A2_PORT,DCMOTOR_A2_PIN,HIGH);
}

void DCMOTOR_Vid_Stop(){
	DIO_Vid_Set_Pin_Val(DCMOTOR_EN_PORT,DCMOTOR_EN_PIN,HIGH);
	DIO_Vid_Set_Pin_Val(DCMOTOR_A1_PORT,DCMOTOR_A1_PIN,LOW);
	DIO_Vid_Set_Pin_Val(DCMOTOR_A2_PORT,DCMOTOR_A2_PIN,LOW);
}