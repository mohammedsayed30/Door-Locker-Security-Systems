 /**********************************************************************
 *
 * Module: URAT_PROTOCOL
 *
 * File Name: urat.h
 *
 * Description: Header file for the AVR URAT driver
 *
 * Created on : 18/10/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 ***********************************************************************/

#ifndef URAT_H_
#define URAT_H_
#include "std_types.h"
/*************************************************************************
 *                             Definitions
 ************************************************************************/
#define URAT_DEFAULT_VALUE           0xFF
/*to make (UART_Parity) Type of unsigned char*/

typedef   uint32         UART_BaudRate;

/*
 * Enumeration_Name:UART_Parity
 *
 * Description:
 *
 * To detect the Required parity
 */

typedef enum{
	/*
	 * DISABLE--->0
	 * RESERVED-->1
	 * ENABLE_EVEN-->2
	 * ENABLE_ODD--->3
	 */
	DISABLE,RESERVED,ENABLE_EVEN,ENABLE_ODD
}UART_Parity;

/*
 * Enumeration_Name:UART_StopBit
 *
 * Description:
 *
 * To detect the Required number of Stop Bits
 */

typedef enum{
	ONE_BIT,TWO_BIT
}UART_StopBit;

/*
 * Enumeration_Name:UART_BitData
 *
 * Description:
 *
 * To detect the Required number of Stop Bits
 */

typedef enum{
	FIVE_BIT,SIX_BIT,SEVEN_BIT,EIGHT_BIT,NINE_BIT=7
}UART_BitData;

/*
 * Structure_Name:UART_ConfigType
 *
 * Description:
 * to detect the required UART_Configurations Like:
 *
 * --->	BitData & Parity & BaudRtae &StopBit
 *
 */

typedef struct{
	UART_BitData  bit_data;
	UART_Parity   parity;
	UART_StopBit  stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;
/**************************************************************************
 *                            Function_Prototypes
 *************************************************************************/
/*
 * Function name UART_init
 *
 * Description:
 *  to initialize active the URAT in AVR
 */
void UART_init(const UART_ConfigType *Config_Ptr);

/*
 * Function name UART_sendByte
 *
 * Description:
 *  to send data to another device
 */
void UART_sendByte(const uint8);

/*
 * Function name UART_recieveByte
 *
 * Description:
 *  to recieve data from another device
 */
uint8 UART_recieveByte(void);

/*
 * Function name UART_sendString
 *
 * Description:
 *  to send string to another device
 */
void UART_sendString(const uint8* str);

/*
 * Function name UART_recieveString
 *
 * Description:
 *  to recieve string from another device
 */
void UART_recieveString(uint8* str);
#endif /* URAT_H_ */
