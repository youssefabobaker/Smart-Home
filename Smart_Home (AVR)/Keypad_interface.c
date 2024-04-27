/*
 * Keypad_interface.c
 *
 * Created: 05/09/2023 16:34:44
 *  Author: AMIT
 */ 
#include "MATH.h" 
#include "STD_TYPE.h" 
#include "DIO_interface.h" 
#include "Keypad_config.h" 

u8 KEYPAD_Data[4][4]={
	{'7','8','9','A'},
	{'4','5','6','B'},
	{'1','2','3','C'},
	{'*','0','=','D'}
	
};
void KEYPAD_Vid_Init(){
	u8 Loc_u8_col_arr[4]={KEYPAD_COL0_PIN,KEYPAD_COL1_PIN,KEYPAD_COL2_PIN,KEYPAD_COL3_PIN};
	
	u8 Loc_u8_row_arr[4]={KEYPAD_ROW4_PIN,KEYPAD_ROW5_PIN,KEYPAD_ROW6_PIN,KEYPAD_ROW7_PIN};
	
	u8 Loc_u8_in=0;
	
	/*  initialization COL */
	for(Loc_u8_in=0;Loc_u8_in<4;Loc_u8_in++)
	{
		
		DIO_Vid_Set_Pin_Dir(KEYPAD_COL_PORT,Loc_u8_col_arr[Loc_u8_in],OUTPUT);
		DIO_Vid_Set_Pin_Val(KEYPAD_COL_PORT,Loc_u8_col_arr[Loc_u8_in],HIGH);
	}
	
	/*  initialization ROW */
	for(Loc_u8_in=0;Loc_u8_in<4;Loc_u8_in++)
	{
		
		DIO_Vid_Set_Pin_Dir(KEYPAD_ROW_PORT,Loc_u8_row_arr[Loc_u8_in],INPUT);
		
		/* ACTIVE PULL UP RESISTOR */
		DIO_Vid_Set_Pin_Val(KEYPAD_ROW_PORT,Loc_u8_row_arr[Loc_u8_in],HIGH);
	}
	
}

u8 KEYPAD_u8_Get_Key()
{
	
	u8 Loc_u8_col_arr[4]={KEYPAD_COL0_PIN,KEYPAD_COL1_PIN,KEYPAD_COL2_PIN,KEYPAD_COL3_PIN};
	u8 Loc_u8_row_arr[4]={KEYPAD_ROW4_PIN,KEYPAD_ROW5_PIN,KEYPAD_ROW6_PIN,KEYPAD_ROW7_PIN};
	u8 Loc_u8_val=0xff;
	u8 Loc_u8_row=0;
	u8 Loc_u8_col=0;
	
	for(Loc_u8_col=0;Loc_u8_col<4;Loc_u8_col++)
	{
		/* ACTIVE COL(N) ---> LOW */
		DIO_Vid_Set_Pin_Val(KEYPAD_COL_PORT,Loc_u8_col_arr[Loc_u8_col],LOW);

		/* CHECK IF ANY BUTTON IS PRESSED */
		
		for(Loc_u8_row=0;Loc_u8_row<4;Loc_u8_row++)
		{
			if(DIO_u8_Get_Pin_Val(KEYPAD_ROW_PORT,Loc_u8_row_arr[Loc_u8_row])==0)
			{
				/* GET VALUE */
				Loc_u8_val=KEYPAD_Data[Loc_u8_row][Loc_u8_col];
				/* BUSY WAIT */
				while (DIO_u8_Get_Pin_Val(KEYPAD_ROW_PORT,Loc_u8_row_arr[Loc_u8_row])==0);
				
				
				return Loc_u8_val;
			}
			
		}
		DIO_Vid_Set_Pin_Val(KEYPAD_COL_PORT,Loc_u8_col_arr[Loc_u8_col],HIGH);
		
	}
	return Loc_u8_val;
	
}