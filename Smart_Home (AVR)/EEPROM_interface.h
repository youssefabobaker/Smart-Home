/*
 * EEPROM_interface.h
 *
 * Created: 10/29/2023 4:03:36 PM
 *  Author: youssef
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_Vid_Write_Data(u16 copy_u16_address, u8 copy_u8_data);

u8   EEPROM_Vid_Read_Data(u16 copy_u16_address);



#endif /* EEPROM_INTERFACE_H_ */