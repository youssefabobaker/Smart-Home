/*
 * TWI_interface.c
 *
 * Created: 24/10/2023 20:10:07
 *  Author: AMIT
 */ 
#include "STD_TYPE.h" 
#include "MATH.h" 
#include "TWI_interface.h" 
#include "TWI_private.h"

void TWI_Vid_Master_Init(u8 copy_u8_address){
	
	 /* set SCL freq : 400khz , with 16MHZ */
	 TWBR_REG=12 ; 
	 /* SET prescaler to 1 :  CLR BIT 0 & BIT1 */
	 CLR_BIT(TWSR_REG,0) ;
	 CLR_BIT(TWSR_REG,1) ; 
	 
	 /* check if the master will not be addressed */
	 if(copy_u8_address !=0){
		 
		 TWAR_REG=copy_u8_address<<1 ; 
	 }
	 else{
		 // DO nothing 
	 }
	 
	 /* ENABLE ACK BIT */
	 SET_BIT(TWCR_REG,6) ; 
	 
	 /* ENABLE TWI */
	 SET_BIT(TWCR_REG,2) ; 
	
	
}

void TWI_Vid_Slave_Init(u8 copy_u8_address){
	
	  /* set slave address */
	  TWAR_REG=copy_u8_address<<1 ; 
	
	 /* ENABLE ACK BIT */
	 SET_BIT(TWCR_REG,6) ;
	 
	 /* ENABLE TWI */
	 SET_BIT(TWCR_REG,2) ;
	
}

TWI_Err_sataus TWI_Send_StartCondition(void){
	
	TWI_Err_sataus Loc_Err=NOErr ; 
	
	/* set start condition bit */
	    SET_BIT(TWCR_REG,5) ; 
		
	/*  CLR TWI flag   */	
	  SET_BIT(TWCR_REG,7) ; 
	  /* Wait to finished current job  */
	  while(GET_BIT(TWCR_REG,7)==0); 
	  
	  if((TWSR_REG& 0xf8) != START_ACK){
		  
		  Loc_Err=StartConditionErr ; 
	  }
	  else{
		  
		   // DO nothing 
	  }
	  
	  
	 
	return Loc_Err ; 
	
}

TWI_Err_sataus TWI_Send_RepeatedStart(void) {
	
	TWI_Err_sataus Loc_Err=NOErr ;
	
	/* set start condition bit */
	SET_BIT(TWCR_REG,5) ;
	
	/*  CLR TWI flag   */
	SET_BIT(TWCR_REG,7) ;
	/* Wait to finished current job  */
	while(GET_BIT(TWCR_REG,7)==0);
	
	if((TWSR_REG& 0xf8) != REP_START){
		
		Loc_Err=RepeatedStartErr;
	}
	else{
		
		// DO nothing
	}
	
	
	
	return Loc_Err ;
	
	
}

TWI_Err_sataus TWI_send_SlaveAddress_With_Write(u8 copy_u8_slaveAddress){
	TWI_Err_sataus Loc_Err=NOErr ;
	
	  /* Send the 7 bit address on bus*/
	      TWDR_REG=copy_u8_slaveAddress<<1;  
		  /* CLR BIT 0 TO write */
		  CLR_BIT(TWDR_REG,0) ; 
		  
		  /* clr the start condition bit */
		  CLR_BIT(TWCR_REG,5) ;
		  
		/*  CLR TWI flag   */
		SET_BIT(TWCR_REG,7) ;
		/* Wait to finished current job  */
		while(GET_BIT(TWCR_REG,7)==0);
		
		if((TWSR_REG& 0xf8) != SLAVE_ADD_AND_WR_ACK){
			
			Loc_Err=SlaveAddress_With_WriteErr;
		}
		else{
			
			// DO nothing
		}
	  
	
	
	return Loc_Err ; 
}
TWI_Err_sataus TWI_send_SlaveAddress_With_Read(u8 copy_u8_slaveAddress){
	
	TWI_Err_sataus Loc_Err=NOErr ;
	
	/* Send the 7 bit address on bus*/
	TWDR_REG=copy_u8_slaveAddress<<1;
	/* SET BIT 0 TO READ */
	SET_BIT(TWDR_REG,0) ;
	
	/* clr the start condition bit */
	CLR_BIT(TWCR_REG,5) ;
	
	/*  CLR TWI flag   */
	SET_BIT(TWCR_REG,7) ;
	/* Wait to finished current job  */
	while(GET_BIT(TWCR_REG,7)==0);
	
	if((TWSR_REG& 0xf8) != SLAVE_ADD_AND_RR_ACK){
		
		Loc_Err=SlaveAddress_With_ReadErr;
	}
	else{
		
		// DO nothing
	}
	
	
	
	return Loc_Err ;
	
	
	
}
TWI_Err_sataus TWI_Master_Send_Data(u8 copy_u8_data){
	TWI_Err_sataus Loc_Err=NOErr ; 
	
	   /* write data on the bus  */  
	   
	   TWDR_REG=copy_u8_data ; 
	/*  CLR TWI flag   */
	SET_BIT(TWCR_REG,7) ;
	/* Wait to finished current job  */
	while(GET_BIT(TWCR_REG,7)==0);
	
	if((TWSR_REG& 0xf8) != MASTER_WR_BYTE_ACK){
		
		Loc_Err=Master_Send_DataErr;
	}
	else{
		
		// DO nothing
	}
	
	
	   
	return Loc_Err ; 
}
TWI_Err_sataus TWI_Master_Recive_Data(u8 * copy_u8_data){
	  
	  TWI_Err_sataus Loc_Err=NOErr ;
	  
	  /*  CLR TWI flag   */
	  SET_BIT(TWCR_REG,7) ;
	  /* Wait to finished current job  */
	  while(GET_BIT(TWCR_REG,7)==0);
	  
	  if((TWSR_REG& 0xf8) != MASTER_RD_BYTE_WITH_ACK){
		  
		  Loc_Err=Master_Recive_DataErr;
	  }
	  else{
		  
		    *copy_u8_data=TWDR_REG ; 
	  }
	  
	  
	  
	  return Loc_Err ;
	
}
void TWI_Send_StopCondition(void){
	
	 /* SEND a stop condition on the bus */
	  SET_BIT(TWCR_REG,4) ;
	  /*  CLR TWI flag   */
	  SET_BIT(TWCR_REG,7) ;
	
}