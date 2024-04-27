/*
 * TWI_interface.h
 *
 * Created: 24/10/2023 20:09:22
 *  Author: AMIT
 */ 


#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

typedef enum{
	
	NOErr , 
	StartConditionErr , 
	RepeatedStartErr ,
	SlaveAddress_With_WriteErr , 
	SlaveAddress_With_ReadErr ,
	Master_Send_DataErr ,
	Master_Recive_DataErr ,
	
	
	
}TWI_Err_sataus;


/*  if no address to master --> 0  */
void TWI_Vid_Master_Init(u8 copy_u8_address) ; 

void TWI_Vid_Slave_Init(u8 copy_u8_address) ; 

TWI_Err_sataus TWI_Send_StartCondition(void) ; 

TWI_Err_sataus TWI_Send_RepeatedStart(void) ;

TWI_Err_sataus TWI_send_SlaveAddress_With_Write(u8 copy_u8_slaveAddress) ; 
TWI_Err_sataus TWI_send_SlaveAddress_With_Read(u8 copy_u8_slaveAddress) ; 
TWI_Err_sataus TWI_Master_Send_Data(u8 copy_u8_data) ; 
TWI_Err_sataus TWI_Master_Recive_Data(u8 * copy_u8_data) ;
void TWI_Send_StopCondition(void) ; 

#endif /* TWI_INTERFACE_H_ */