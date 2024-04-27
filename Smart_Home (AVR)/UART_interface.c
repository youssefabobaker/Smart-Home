/*
 * UART_interface.c
 *
 * Created: 10/15/2023 1:35:42 PM
 *  Author: youssef
 */ 
#include "UART_interface.h"
#include "UART_private.h"
#include "DIO_interface.h"
#include "MATH.h"

void UART_Vid_Init(void){
	u8 loc_u8_temp = 0;
	/* SEND BIT DATA */
	SET_BIT(loc_u8_temp,7);
	SET_BIT(loc_u8_temp,1);
	SET_BIT(loc_u8_temp,2);
	UCSRC_REG = loc_u8_temp;
	
	/* SET BAUD RATE 9600 : 16MHZ */
	UBRRL_REG = 103;
	
	/* ENABLE RX */
	SET_BIT(UCSRB_REG,4);
	
	/* ENABLE TX */
	SET_BIT(UCSRB_REG,3);
}

void UART_Vid_TX(u8 copy_u8_data){
	UDR_REG = copy_u8_data;
	while(GET_BIT(UCSRA_REG,5) == 0);
}

u8 UART_Vid_RX(){
	while(GET_BIT(UCSRA_REG,7) == 0);
	return UDR_REG;
}