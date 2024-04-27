/*
 * UART_RX.c
 *
 * Created: 10/15/2023 2:10:51 PM
 * Author : youssef
 */ 
//#include <avr/eeprom.h>
#include "DIO_interface.h"
#include "UART_interface.h"
#include "TIMER1_interface.h"
#include "BUZZER_interface.h"
#include "ADC_test_interface.h"
#include "UART_interface.h"
#include "GIE_interface.h"
#include "EXT_interface.h"
#include "LCD_interface.h"
#include "LCD_config.h"
#include "DC_MOTOR_interface.h"
#include "TIMER0_interface.h"
#include "EEPROM_interface.h"
#include "TWI_interface.h"
#include "Keypad_config.h"
#include "Keypad_interfcae.h"
#define F_CPU 16000000UL
#include <util/delay.h>
 
int main(void)
{

	u8 val;
	u8 i;
	u8 admin_flag=0;
	u8 index=0;
	u8 flag=0;
	u8 flag1=0;
	u8 flag2=0;
	u8 door_control;
	u8 door_flag=0;
	u8 buzzer_flag=0;
	u8 buzzer_flag2=0;
	u8 c=0xff , v=0xff;
	u8 modee=0xff;

	DIO_Vid_Set_Pin_Dir(PORTD,PIN0,INPUT); // RX    
	UART_Vid_Init();
	
	/* SERVO */
	DIO_Vid_Set_Pin_Dir(PORTD,PIN5,OUTPUT); //OCR1A
	TIMER1_Vid_FastPWM_ICR1_Init();
	
	
	/* BUZZER */
	BUZZER_Vid_Init();
	DIO_Vid_Set_Pin_Dir(PORTB,PIN0,OUTPUT);
	
	/* ADC */
	u16 tempreture;
	ADC_Vid_Init();
	
	/*KEYPAD*/
	KEYPAD_Vid_Init() ;
	
	/* LCD*/
	DIO_Vid_Set_Port_Dir(LCD_DPORT,0xf0) ;
	DIO_Vid_Set_Pin_Dir(LCD_CPORT,LCD_RS_PIN,OUTPUT) ;
	DIO_Vid_Set_Pin_Dir(LCD_CPORT,LCD_RW_PIN,OUTPUT) ;
	DIO_Vid_Set_Pin_Dir(LCD_CPORT,LCD_EN_PIN,OUTPUT) ;
	LCD_Vid_Init() ;
	
	LCD_Vid_GotoXY(COL6,ROW1);
	LCD_Vid_Send_String("HELLO!");
	_delay_ms(2000);
	LCD_Vid_Send_Command(LCD_CLR);


	while(1){	
		LCD_Vid_GotoXY(COL1,ROW1);
		LCD_Vid_Send_String("0:admin ,1:user");
		modee=UART_Vid_RX();
		if(modee=='0' || modee=='1'){
			if(modee=='0'){
				LCD_Vid_GotoXY(COL1,ROW1);
				LCD_Vid_Send_String("0:register      1:admin 2:delete ");
				modee=UART_Vid_RX();
				LCD_Vid_Send_Command(LCD_CLR);
				if(modee=='1'){
					LCD_Vid_GotoXY(COL1,ROW1);
					LCD_Vid_Send_String("enter username:");
					c=UART_Vid_RX();
					LCD_Vid_Send_Data(c);
					_delay_ms(500);
					LCD_Vid_Send_Command(LCD_CLR);
					
					LCD_Vid_GotoXY(COL1,ROW1);
					LCD_Vid_Send_String("enter password:");
					v=UART_Vid_RX();
					
					LCD_Vid_Send_Data(v);
					_delay_ms(500);
					LCD_Vid_Send_Command(LCD_CLR);
					if(c=='A' && v=='0'){
						admin_flag=1;
						LCD_Vid_Send_String("Valid admin");
						_delay_ms(500);
						break;
					}else{
					LCD_Vid_Send_String("Invalid admin!");
					_delay_ms(500);
					buzzer_flag++;
					if(buzzer_flag>3){
						while(1){
							DIO_Vid_Set_Pin_Val(PORTB,PIN0,HIGH);
							BUZZER_Vid_On();
							_delay_ms(200);
							DIO_Vid_Set_Pin_Val(PORTB,PIN0,LOW);
							BUZZER_Vid_Off();
							_delay_ms(200);
						}
					}
					
					
				}}else if(modee=='0'){
					flag=0;
					LCD_Vid_GotoXY(COL1,ROW1);
					LCD_Vid_Send_String("enter username:");
					c=UART_Vid_RX();
					LCD_Vid_Send_Data(c);
					_delay_ms(500);
					LCD_Vid_Send_Command(LCD_CLR);
					
					LCD_Vid_GotoXY(COL1,ROW1);
					LCD_Vid_Send_String("enter password:");
					v=UART_Vid_RX();
						
					LCD_Vid_Send_Data(v);
					_delay_ms(500);
					LCD_Vid_Send_Command(LCD_CLR);
				
					for(i=0;i<index ;i+=2){
						if((EEPROM_Vid_Read_Data(i)==c) && (EEPROM_Vid_Read_Data(i+1)==v)){
							flag=1;
							break;
						}
					}
					if(flag==1 && index>=2){
							LCD_Vid_Send_String("Already saved!");
							_delay_ms(500);
						}else if(flag==0){
							EEPROM_Vid_Write_Data(index,c);
							EEPROM_Vid_Write_Data(index+1,v);
						    index+=2;
							LCD_Vid_Send_String("Account Saved");
							_delay_ms(500);
							
						}
					}else if(modee=='2'){
						flag2=0;
						LCD_Vid_Send_Command(LCD_CLR);
						LCD_Vid_GotoXY(COL1,ROW1);
						LCD_Vid_Send_String("enter user you  want to delete:");
						_delay_ms(500);
						val=UART_Vid_RX();
						LCD_Vid_Send_Data(val);
						_delay_ms(500);
						LCD_Vid_Send_Command(LCD_CLR);
						for(i=0;i<index;i++){
							if(EEPROM_Vid_Read_Data(i)==val){
								flag2=1;
								break;
							}
						}
						if(flag2==0){
							LCD_Vid_Send_String("user not found");
							_delay_ms(500);
						}else{
							while(i<index){
							EEPROM_Vid_Write_Data(i,EEPROM_Vid_Read_Data(i+2));
							EEPROM_Vid_Write_Data(i+1,EEPROM_Vid_Read_Data(i+3));
							i+=2;
							index-=2;
							}
							LCD_Vid_Send_String("user is deleted");
							_delay_ms(500);
						}
					}
					}else if(modee=='1'){
						flag1=0;
						
							c=0xff;
							v=0xff;
							while(1){
								LCD_Vid_GotoXY(COL1,ROW1);
								LCD_Vid_Send_String("enter username:");
								c=KEYPAD_u8_Get_Key();
								if(c!=0xff){
									break;
								}
							}
							LCD_Vid_Send_Data(c);
							_delay_ms(500);
							LCD_Vid_Send_Command(LCD_CLR);
							while(1){
								LCD_Vid_GotoXY(COL1,ROW1);
								LCD_Vid_Send_String("enter password:");
								v=KEYPAD_u8_Get_Key();
								if(v!=0xff){
									break;
								}
							}
							
							LCD_Vid_Send_Data(v);
							_delay_ms(500);
							LCD_Vid_Send_Command(LCD_CLR);
						
						/*
						LCD_Vid_GotoXY(COL1,ROW1);
						LCD_Vid_Send_String("enter username:");
						c=UART_Vid_RX();
						LCD_Vid_Send_Data(c);
						_delay_ms(500);
						LCD_Vid_Send_Command(LCD_CLR);
						
						LCD_Vid_GotoXY(COL1,ROW1);
						LCD_Vid_Send_String("enter password:");
						v=UART_Vid_RX();
						
						LCD_Vid_Send_Data(v);
						_delay_ms(500);
						LCD_Vid_Send_Command(LCD_CLR);
						*/
						
						
						for(i=2;i<index ;i+=2){
							if((EEPROM_Vid_Read_Data(i)==c) && (EEPROM_Vid_Read_Data(i+1)==v)){		
								flag1=1;
								break;
							}
						}
						if(flag1==1){
							LCD_Vid_Send_String("valid user!");
							_delay_ms(500);
							break;
						}else{
						LCD_Vid_Send_String("Invalid user!");
						_delay_ms(500);
						buzzer_flag2++;
						if(buzzer_flag2>3){
							while(1){
								DIO_Vid_Set_Pin_Val(PORTB,PIN0,HIGH);
								BUZZER_Vid_On();
								_delay_ms(200);
								DIO_Vid_Set_Pin_Val(PORTB,PIN0,LOW);
								BUZZER_Vid_Off();
								_delay_ms(200);
							}
						}
						
						
					}
					}
						
		}
		
			}
	

	/******************************************************************************************************************/
	

_delay_ms(500);
LCD_Vid_Send_Command(LCD_CLR);
LCD_Vid_Send_String("Welcome Back!");
_delay_ms(2000);
LCD_Vid_Send_Command(LCD_CLR);
while(1){
	
	/*Door opening/closing*/
	
	if(admin_flag==1){
		LCD_Vid_GotoXY(COL1,ROW1);
		LCD_Vid_Send_String("0:control door");
		LCD_Vid_GotoXY(COL1,ROW2);
		LCD_Vid_Send_String("1:continue");
		door_flag=UART_Vid_RX();
		if(door_flag=='0'){
			LCD_Vid_Send_Command(LCD_CLR);
			LCD_Vid_GotoXY(COL1,ROW1);
			LCD_Vid_Send_String("0:open 1:close");
			door_control=UART_Vid_RX();
			if(door_control=='1' || door_control=='0')
			{
				if(door_control=='1'){
					do
					{
						for(u32 i=0; i<=4500; i++){
							TIMER1_Vid_SetCompareVal(i);
							_delay_us(100);
						}
						door_control=0;
					} while (door_control!=0);
					break;
					}else{
					do
					{
						for(u32 i=4500; i>0; i--){
							TIMER1_Vid_SetCompareVal(i);
							_delay_us(100);
						}
					} while (door_control!='0');
					break;
				}
			}
		}else{
			LCD_Vid_Send_Command(LCD_CLR);
			break;
		}	
	}else{
		break;
	}
}
while(1){
	_delay_ms(300);
	LCD_Vid_GotoXY(COL8,ROW1);
	LCD_Vid_Send_Data(' ');
	LCD_Vid_GotoXY(COL9,ROW1);
	LCD_Vid_Send_Data(' ');
			
		
	/* TEMPERATURE */
	
	tempreture = ADC_u16_ReadChannel(ADC0);
	_delay_ms(10);
	tempreture = ((tempreture*500)/1023) - 20 ;
	LCD_Vid_GotoXY(COL1,ROW1);
	LCD_Vid_Send_String("TEMP:");
	LCD_Vid_Send_Number(tempreture);
	if(tempreture > 27){
		DCMOTOR_Vid_CW();
		LCD_Vid_GotoXY(COL16,ROW1);
		LCD_Vid_Send_Data(' ');
		LCD_Vid_GotoXY(COL10,ROW1);
		LCD_Vid_Send_String("FAN:on");
		DIO_Vid_Set_Pin_Val(PORTC,PIN7,HIGH);
	}
	else{
		DCMOTOR_Vid_Stop();
		LCD_Vid_GotoXY(COL10,ROW1);
		LCD_Vid_Send_String("FAN:off");
		DIO_Vid_Set_Pin_Val(PORTC,PIN7,LOW);
	}
	

	
}
}
 
	
			
	
		

	
	

	
	