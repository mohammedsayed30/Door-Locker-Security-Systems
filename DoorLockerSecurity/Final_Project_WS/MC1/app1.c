 /******************************************************
 *
 * Module: MC1_Application
 *
 * File Name: app1.c
 *
 * Description:Source file for the password_application
 * for Microcontroller1(Human Machine Interface)
 *
 * Created on:28/10/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 *****************************************************/


/*******************************************************
 *
 * Important Notes:
 * 1-This Microcontroller use 1MHZ NOT 8
 * To handle the Problems Of Keypad
 *
 * 2-There some Things is not the best solution but I
 * Used it To apply Many subjects that I had Studied
 *
 ******************************************************/



/*to use the LCD to display characters*/
#include "LCD.h"
/*to use the Keypad to get Inputs from the user*/
#include "keypad.h"
#include <util/delay.h> /*to use delay function*/
#include "urat.h"       /*to use the Uart MOdel*/
#include "timer1.h"     /*to use timer1 driver*/
#include <avr/io.h>     /*to use SREG*/
/*to use the required definitions of this Applications*/
#include "app1_functions.h"
#include "LCD.h"  /*to use the LCD Driver*/
#define   F_CPU 8000000UL
/*that key  response for holding the choice of main options*/
extern uint8 key;
int main(void){
	/* hold the allow number of Wrong passowrd*/
	uint8 count=3;
	SREG|=(1<<7);  /*to active interrupt*/
	/*to hold that two passwords are correct or not*/
	uint8 return_check;

	/*create object from Structure UART_ConfigType*/
	UART_ConfigType config;
	/*setup the configuration of Uart*/

	config.baud_rate=9600;     /* 9600 buad_rate*/
	config.bit_data=EIGHT_BIT; /*use eight data_bit*/
	config.parity=DISABLE;     /*disable the parity*/
	config.stop_bit=ONE_BIT;  /*use one stop bit*/
	/*active the UART Model*/
	UART_init(&config);
	/*active the LCD to I can display on it*/
	LCD_init();
	/*the User will stay in this stay until enter
	 * two matches passwords
	 */
	do{
	    /* to interactive with the user*/
	    UserInterface_Step1();
	    /*to send the two passwords to the Control_ECU*/
	    return_check=SendPasswordToControl_ECU();
	 }while(return_check==NOT_CORRECT);
   /*this is mean that 2 Passwords Correct*/
	key=Main_Opitions();
	while(1){
		/*hold that the password correct or not*/
		uint8 state=NOT_CORRECT;
		/*that is mean choice open door*/
		if(key=='+'){
			count=3;
			while(state==NOT_CORRECT && count){
				/*the allowed 3 times decrement by one*/
				count--;
				/*
				 * to make MC2 know that the user wanna change the password
				 * so do not any thing for dc motor
				 */
				 UART_sendByte(key);
				 state = Open_Door();
			}
/*this mean the right pass during the allowed times*/
			if(state==CORRECT){
				/*display the required Messages*/
				display_String();
			}
/* this mean that the three Times was wrong*/
			if(count==0){
				Error_Message();
			}
			key=0;/*to lose the last value*/
			state=NOT_CORRECT;/*for the next time*/
		}
		/*this mean that user want to change his password*/
		else if (key=='-'){
/*
 * to make MC2 know that the user wanna change the password
 * so do not any thing for dc motor
 */
			UART_sendByte(key);
			/*to lose his last value*/
			key=0;
			count=3;
			while(state==NOT_CORRECT && count){
/*as has the same steps at the begging in Open_Door functions */
				 state = Change_Pass();
				 count--;
			}

			if(state==CORRECT){
				do{
					/* to interactive with the user*/
					UserInterface_Step1();
					/*to send the two passwords to the Control_ECU*/
					return_check=SendPasswordToControl_ECU();
				 }while(return_check==NOT_CORRECT);
				key=Main_Opitions();
			}
			/* this mean that the three Times was wrong*/
			if(count==0){
				Error_Message();
			}

		}
	}
	return 0;
}
