 /**********************************************************************
 *
 * Module: I2C_PROTOCOL
 *
 * File Name: i2c.h
 *
 * Description: Header file for the AVR I2C driver
 *
 * Created on : 21/10/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 ***********************************************************************/

#ifndef I2C_H_
#define I2C_H_
#include "std_types.h"


/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */
/*make TWI_Address & TWI_BaudRate as unsigned char*/
typedef uint8             TWI_Address;
typedef uint8             TWI_BaudRate;

/*
 * Structure_Name:TWI_ConfigType
 *
 * Description:
 *
 * to Detect the Required Configuration for:
 *
 * -->TWI_Address
 * -->TWI_BaudRate
 */

typedef struct{
	/*hold the address of slave*/
	TWI_Address address;
	/*hold the BaudRate*/
	TWI_BaudRate bit_rate;
}TWI_ConfigType;
/**************************************************************************
 *                          Prototypes
 *************************************************************************/
/*
 * Function_Name:TWI_init
 *
 * Description:
 *
 * to initialize the I2C Model with the required configuration
 */
void TWI_init(const TWI_ConfigType *Config_Ptr);

/*
 * Function_Name:TWI_start
 *
 * Description:
 *
 * to start the I2C Model
 */
void TWI_start(void);
/*
 * Function_Name:TWI_stop
 *
 * Description:
 *
 * to stop the I2C Model
 */
void TWI_stop(void);

/*
 * Function_Name:TWI_writeByte
 *
 * Description:
 *
 * to the master write byte to the slave by the I2C Model
 */
void TWI_writeByte(uint8 data);

/*
 * Function_Name:TWI_readByteWithACK
 *
 * Description:
 *
 * to the master read byte from the slave with ACK by the I2C Model
 */
uint8 TWI_readByteWithACK(void);
/*
 * Function_Name:TWI_readByteWithNACK
 *
 * Description:
 *
 * to the master read byte from the slave with NACK by the I2C Model
 */
uint8 TWI_readByteWithNACK(void);

/*
 * Function_Name:TWI_getStatus
 *
 * Description:
 *
 * to get the status
 */
uint8 TWI_getStatus(void);
#endif /* I2C_H_ */
