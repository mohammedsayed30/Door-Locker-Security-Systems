 /**********************************************************************
 *
 * Module: EEPROM with I2C_PROTOCOL
 *
 * File Name: eeprom.c
 *
 * Description: Source file for the AVR EEPROM driver
 *
 * Created on : 21/10/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 ***********************************************************************/
#include "eeprom.h"
#include "i2c.h"

/*
 * Function_Name:EEPROM_writeByte
 *
 * Description:
 *
 * to the master write byte to the slave(EEPROM) by the I2C Model
 */
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data){
	/*transimate send start bit*/
	TWI_start();
	 if (TWI_getStatus() != TWI_START)/*to ensure that start bit sended*/
	        return ERROR;
	 /*send the divece address where we should take the (A10 A9 A8)
	  * from the memory locations
	  */
	   TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
	    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
	        return ERROR;
	    /*send the required address locations*/
		TWI_writeByte((uint8)(u16addr));
		if (TWI_getStatus() != TWI_MT_DATA_ACK)
		     return ERROR;
		   /* write byte to eeprom */
		    TWI_writeByte(u8data);
		    if (TWI_getStatus() != TWI_MT_DATA_ACK)
		        return ERROR;

		    /* Send the Stop Bit */
		    TWI_stop();
		    return SUCCESS;
}

/*
 * Function_Name:EEPROM_readByte
 *
 * Description:
 *
 * to the master reade byte from the slave(EEPROM) by the I2C Model
 */
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data){
	/*transimate send start bit*/
	TWI_start();
	 if (TWI_getStatus() != TWI_START)/*to ensure that start bit sended*/
	        return ERROR;
	 /*send the divece address where we should take the (A10 A9 A8)
	  * from the memory locations
	  */
	   TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
	    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
	        return ERROR;
	    /*send the required address locations*/
		TWI_writeByte((uint8)(u16addr));
		if (TWI_getStatus() != TWI_MT_DATA_ACK)
		     return ERROR;
		/*transimate reapeated start bit*/
		TWI_start();
		 if (TWI_getStatus() != TWI_REP_START)/*to ensure that start bit sended*/
		        return ERROR;
		 /*send the divece address where we should take the (A10 A9 A8)
		  * from the memory locations
		  */
		   TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7)|1));
		    if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
		        return ERROR;

		    /* Read Byte from Memory without send ACK */
		    *u8data = TWI_readByteWithNACK();
		    if (TWI_getStatus() != TWI_MR_DATA_NACK)
		        return ERROR;

		    /* Send the Stop Bit */
		    TWI_stop();

		    return SUCCESS;
}

