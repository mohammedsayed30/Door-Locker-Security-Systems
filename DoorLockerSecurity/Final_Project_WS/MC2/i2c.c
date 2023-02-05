 /**********************************************************************
 *
 * Module: I2C_PROTOCOL
 *
 * File Name: i2c.c
 *
 * Description: Source file for the AVR I2C driver
 *
 * Created on : 21/10/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 ***********************************************************************/
#include "i2c.h"
#include "gpio.h"
#include "common_macros.h"
#include <avr/io.h>        /* to use registers of AVR*/


/*
 * Function_Name:TWI_init
 *
 * Description:
 *
 * to initialize the I2C Model with the required configuration
 */
void TWI_init(const TWI_ConfigType *Config_Ptr){
	/*
	TWBR=0x02;  /*to use 400000 kbps with 8MHZ
	TWSR=0x00;        /*n0 prescalar
	/*my adress=0x01---->used when Microcontroller is slave
	TWAR=0b00000010;
	TWCR=(1<<TWEN);   /*to enables TWI operation
	*/

/* With Dynamic Configurations as required */

	/*to use the required rate*/
	TWBR=Config_Ptr->bit_rate;
	TWSR=0x00;        /*No Prescalar*/
	/*to use the required Rate*/
	TWAR=Config_Ptr->address;
	TWCR=(1<<TWEN);   /*to enables TWI operation*/
}

/*
 * Function_Name:TWI_start
 *
 * Description:
 *
 * to start the I2C Model
 */
void TWI_start(void){
	/*
	 * TWSTA=1-->to active start bit
	 * TWEN=1--->to enables TWI operation
	 * TWINT=1--->to clear the interrupt flag at the beggining
	 */
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	/*wait tile the start condition is transmitted successfully*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
}
/*
 * Function_Name:TWI_stop
 *
 * Description:
 *
 * to stop the I2C Model
 */
void TWI_stop(void){
	/*
	 * TWSTO=1-->to active Stop bit
	 * TWEN=1--->to enables TWI operation
	 * TWINT=1--->to clear the interrupt flag at the beggining
	 */
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

/*
 * Function_Name:TWI_writeByte
 *
 * Description:
 *
 * to the master write byte to the slave by the I2C Model
 */
void TWI_writeByte(uint8 data){

	/*put the data to the required register*/
	TWDR=data;
	/*
	 * TWEN=1--->to enables TWI operation
	 * TWINT=1--->to clear the interrupt flag at the beggining
	 */
	TWCR=(1<<TWINT)|(1<<TWEN);

	/*polling to ensure that data is stored successfuly*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*
 * Function_Name:TWI_readByteWithACK
 *
 * Description:
 *
 * to the master read byte from the slave with ACK by the I2C Model
 */
uint8 TWI_readByteWithACK(void){
	/*
	 * TWEN=1--->to enables TWI operation
	 * TWINT=1--->to clear the interrupt flag at the beggining
	 * TWEA=1--->to enable the ACK bit after recieving or reading
	 */
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	/*polling to ensure that is the required data*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/*return the required data*/
	return TWDR;
}
/*
 * Function_Name:TWI_readByteWithNACK
 *
 * Description:
 *
 * to the master read byte from the slave with NACK by the I2C Model
 */
uint8 TWI_readByteWithNACK(void){
	/*
	 * TWEN=1--->to enables TWI operation
	 * TWINT=1--->to clear the interrupt flag at the beggining
	 * TWEA=0--->to enable the NACK bit after recieving or reading
	 */
	TWCR=(1<<TWINT)|(1<<TWEN);
	/*polling to ensure that is the required data*/
	while(BIT_IS_CLEAR(TWCR,TWINT));
	/*return the required data*/
	return TWDR;
}

/*
 * Function_Name:TWI_getStatus
 *
 * Description:
 *
 * to get the status
 */
uint8 TWI_getStatus(void){
	uint8 status_result;
	status_result=(TWSR & 0xF8);
	return status_result;
}


