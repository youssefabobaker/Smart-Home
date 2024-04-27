/*
 * UART_interface.h
 *
 * Created: 10/15/2023 1:35:26 PM
 *  Author: youssef
 */ 
#include "STD_TYPE.h"

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


void UART_Vid_Init(void);
void UART_Vid_TX(u8 copy_u8_data);
u8 UART_Vid_RX();

#endif /* UART_INTERFACE_H_ */