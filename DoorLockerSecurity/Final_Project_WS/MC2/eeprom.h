/**********************************************************************
 *
 * Module: EEPROM with I2C_PROTOCOL
 *
 * File Name: eeprom.h
 *
 * Description: Header file for the AVR EEPROM driver
 *
 * Created on : 21/10/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 ***********************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_
#include "std_types.h"

#define ERROR 0
#define SUCCESS 1
/************************************************************************
 *                         Functions Prototypes
 ************************************************************************/
/*
 * Function_Name:EEPROM_writeByte
 *
 * Description:
 *
 * to the master write byte to the slave(EEPROM) by the I2C Model
 */
uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);

/*
 * Function_Name:EEPROM_readByte
 *
 * Description:
 *
 * to the master reade byte from the slave(EEPROM) by the I2C Model
 */
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);

#endif /* EEPROM_H_ */
