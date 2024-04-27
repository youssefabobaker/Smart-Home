/*
 * EEPROM_interface.c
 *
 * Created: 10/29/2023 4:03:55 PM
 *  Author: youssef
 */ 
#include "MATH.h"
#include "STD_TYPE.h"
#include "TWI_interface.h"
#define F_CPU 16000000UL
#include <util/delay.h>

void EEPROM_Vid_Write_Data(u16 copy_u16_address, u8 copy_u8_data){
	
	u8 loc_u8_address = 0b1010000 | copy_u16_address>>8;
	TWI_Send_StartCondition();
	TWI_send_SlaveAddress_With_Write(loc_u8_address);
	TWI_Master_Send_Data((u8)copy_u16_address);
	TWI_Master_Send_Data(copy_u8_data);
	TWI_Send_StopCondition();
	_delay_ms(5);

}
/*
u8   EEPROM_Vid_Read_Data(u16 copy_u16_address){
	
	u8 loc_u8_val=0;
	
	u8 loc_u8_address = 0b1010000 | copy_u16_address>>8;
	TWI_Send_StartCondition();
	TWI_send_SlaveAddress_With_Write(loc_u8_address);
	TWI_Master_Send_Data((u8)copy_u16_address);
	TWI_Send_RepeatedStart();
	TWI_send_SlaveAddress_With_Read(loc_u8_address);
	TWI_Master_Recive_Data(&loc_u8_val);
	
	TWI_Send_StopCondition();
	return loc_u8_val;
	
}
*/

u8 EEPROM_Vid_Read_Data(u16 copy_u16_address) {
	u8 loc_u8_val = 0;
	TWI_Err_sataus readStatus;

	u8 loc_u8_address = 0b1010000 | copy_u16_address >> 8;
	TWI_Send_StartCondition();
	TWI_send_SlaveAddress_With_Write(loc_u8_address);
	TWI_Master_Send_Data((u8)copy_u16_address);
	TWI_Send_RepeatedStart();
	TWI_send_SlaveAddress_With_Read(loc_u8_address);
    TWI_Master_Send_Data((u8)copy_u16_address);
	readStatus = TWI_Master_Recive_Data(&loc_u8_val);

	TWI_Send_StopCondition();

	if (readStatus != NOErr) {
		// Handle the error, e.g., return a specific value or print an error message
		return 0x00; // or any other value to indicate an error
	}

	return loc_u8_val;
}
