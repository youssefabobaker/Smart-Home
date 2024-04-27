/*
 * ADC_test_private.h
 *
 * Created: 9/19/2023 4:41:50 PM
 *  Author: youssef
 */ 


#ifndef ADC_TEST_PRIVATE_H_
#define ADC_TEST_PRIVATE_H_


#define  ADMUX_REG  *((volatile u8*)0x27)
#define  ADCSRA_REG *((volatile u8*)0x26)
#define  ADC_REG    *((volatile u16*)0x24) // ADCL + ADCH ---> WORK ON 10 BIT RESOLUTION


#endif /* ADC_TEST_PRIVATE_H_ */