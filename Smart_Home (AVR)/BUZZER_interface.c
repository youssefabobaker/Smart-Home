/*
 * BUZZER_interface.c
 *
 * Created: 10/3/2023 3:05:17 PM
 *  Author: youssef
 */ 
#include "DIO_interface.h"
#include "BUZZER_config.h"

void BUZZER_Vid_Init(){
	DIO_Vid_Set_Pin_Dir(BUZZER_PORT,BUZZER_PIN,OUTPUT);
}
void BUZZER_Vid_On(){
	DIO_Vid_Set_Pin_Val(BUZZER_PORT,BUZZER_PIN,HIGH);
}
void BUZZER_Vid_Off(){
	DIO_Vid_Set_Pin_Val(BUZZER_PORT,BUZZER_PIN,LOW);
}