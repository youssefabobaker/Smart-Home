/*
 * ADC_test_interface.h
 *
 * Created: 9/19/2023 4:42:07 PM
 *  Author: youssef
 */ 

#ifndef ADC_TEST_INTERFACE_H_
#define ADC_TEST_INTERFACE_H_

/*****************************************************************************
* Function Name: ADC_Vid_Init
* Purpose      : INITIALIZE ADC
* Parameters   : VOID
* Return value : VOID
*****************************************************************************/
void ADC_Vid_Init() ;
/*****************************************************************************
* Function Name: ADC_u16_ReadChannel
* Purpose      : READ THE CONVERTED DATA
* Parameters   : u8 copy_u8_channel
* Return value : u16
*****************************************************************************/
u16 ADC_u16_ReadChannel(u8 copy_u8_channel) ;
/***************************************************************************************/

/* SELECT THE CHANNEL (ADC PIN) */
#define  ADC0  0
#define  ADC1  1
#define  ADC2  2
#define  ADC3  3
#define  ADC4  4
#define  ADC5  5
#define  ADC6  6
#define  ADC7  7

/* ADC PRESCALAR SELECTIONS ( DIVISION FACTOR) */
#define  DIVSION_2      1
#define  DIVSION_4      2
#define  DIVSION_8      3
#define  DIVSION_16     4
#define  DIVSION_32     5
#define  DIVSION_64     6
#define  DIVSION_128    7 

/* SELCT FROM ADC PRESCALAR SELECTIONS */
#define  ADC_PRESCALER   DIVSION_128


#endif /* ADC_TEST_INTERFACE_H_ */ 