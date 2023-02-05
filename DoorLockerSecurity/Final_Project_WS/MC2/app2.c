 /******************************************************
 *
 * Module:MC2_Application
 *
 * File Name: app2.c
 *
 * Description:Source file for the password_application
 * for Microcontroller2(CONTROL_ECU)
 *
 * Created on:28/10/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 *****************************************************/


/*******************************************************
 *
 *
 * Important Note:This Microcontroller use 8MHZ
 *
 *
 ******************************************************/




#include "app2_functions.h"
#include "urat.h"
#include "timer1.h"
#include <util/delay.h>
#include "i2c.h"
#include "dc_motor.h"
#include "eeprom.h"
#include "buzzer.h"
#include <avr/io.h>

#define F_CPU  8000000UL



int main(void){
	uint8 change_pass_key='+';
	/* hold the allow number of Wrong passowrd*/
	uint8 count=3;
	SREG|=(1<<7);  /*to active the Interrupt*/
	/*to hold the state of password(match or not)*/
	uint8 matched_state=NOT_CORRECT;
    /*to active the dc motor*/
	DcMotor_init();

	/*create object from Structure UART_ConfigType*/
	TWI_ConfigType TWI_conf;
	/*setup the configuration of TWI*/
	TWI_conf.address=0b00000010;
	TWI_conf.bit_rate=0x02;
	TWI_init(&TWI_conf);
	/*create object from Structure UART_ConfigType*/
	UART_ConfigType UART_conf;
	/*setup the configuration of Uart*/

	UART_conf.baud_rate=9600;     /* 9600 buad_rate*/
	UART_conf.bit_data=EIGHT_BIT; /*use eight data_bit*/
	UART_conf.parity=DISABLE;     /*disable the parity*/
	UART_conf.stop_bit=ONE_BIT;  /*use one stop bit*/
	/*active the UART Model*/
	UART_init(&UART_conf);
	/*to check the two passwords */
	Check_Passwords();
  /*
   * 1-receive the password from HMI_ECU the user enter it
   * 2-to check the User_password with that one that
   * Save it in EEPROM_MEMORY
   */
	while(1){
       count=3;
		while(matched_state==NOT_CORRECT && count){
			 count--;
			 change_pass_key=UART_recieveByte();
			 matched_state=password_is_matched();
			 /*send byte to HMI_ECU*/
			 UART_sendByte(matched_state);
			/*if two Passwords Matched*/
			if(matched_state==CORRECT && change_pass_key=='+'){
				password_matchedWithClockWise();
			}
			else if(matched_state==CORRECT && change_pass_key=='-'){
				/*to check the two passwords */
				Check_Passwords();
			}
		}
		/* this mean that the three Times was wrong*/
		if(count==0){
			Activate_Buzzer();
		}
		matched_state=NOT_CORRECT;

	}
	return 0;
}

