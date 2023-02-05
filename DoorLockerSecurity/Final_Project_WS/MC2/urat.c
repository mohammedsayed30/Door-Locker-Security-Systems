 /**********************************************************************
 *
 * Module: URAT_PROTOCOL
 *
 * File Name: urat.c
 *
 * Description: Source file for the AVR URAT driver
 *
 * Created on : 18/10/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 ***********************************************************************/
#include "urat.h"
#include "gpio.h"
#include "common_macros.h"
#include <avr/io.h>
/*
 * Function name UART_init
 *
 * Description:
 *  to initialize active the URAT in AVR
 */
void UART_init(const UART_ConfigType *Config_Ptr){
	uint16 rate_value;          /*to hold the required value to UBRR*/

	UCSRA=(1<<U2X);      /* to using the asynchronous*/


	/*
	 * RXEN=1-->to enable URAT Reciver
	 * TXEN=1->>to enable URAT Sender
	 * (Config_Ptr->bit_data)&(0x04)-->to set the UCSZ2_Bit
	 */
	UCSRB=(1<<RXEN)|(1<<TXEN)|((Config_Ptr->bit_data)&(0x04));
	UCSRC=(1<<URSEL)|((Config_Ptr->stop_bit)<<USBS)|((Config_Ptr->parity)<<UPM0)|((Config_Ptr->bit_data)<<UCSZ0);
	rate_value=(uint16)(((F_CPU/(Config_Ptr->baud_rate*8UL)))-1);
	/*boat rate*/
	UBRRL=rate_value;
	UBRRH=rate_value>>8;
}

/*
 * Function name UART_sendByte
 *
 * Description:
 *  to send data to another device
 */
void UART_sendByte(const uint8 data){
	/*polling to ensure there is unread_data */
	while(BIT_IS_CLEAR(UCSRA,UDRE));
	UDR=data;       /*send the required data*/
}

/*
 * Function name UART_recieveByte
 *
 * Description:
 *  to recieve data from another device
 */
uint8 UART_recieveByte(void){
	/*polling to ensure there is the required data */
	while(BIT_IS_CLEAR(UCSRA,RXC));
	return UDR;          /*return this data*/
}

/*
 * Function name UART_sendString
 *
 * Description:
 *  to send string to another device
 */
void UART_sendString(const uint8* str){
	uint8 index_str=0;          /*counter*/
	while(str[index_str]!='\0'){
		UART_sendByte(str[index_str]);
		index_str++;
	}
}

/*
 * Function name UART_recieveString
 *
 * Description:
 *  to recieve string from another device
 */
void UART_recieveString(uint8* str){
	uint8 index_str=-1;          /*counter*/
	do{
		index_str++;
		str[index_str]=UART_recieveByte();
	}while(str[index_str]!='#');
	str[index_str] ='\0';
}

