 /******************************************************
 *
 * File Name: app1_functions.c
 *
 * Description: Source file for the  Required
 * Functions Definitions for MC2
 *
 * Created on:4/11/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 *******************************************************/
#include "app2_functions.h"
#include "urat.h"
#include "timer1.h"
#include <util/delay.h>
#include "i2c.h"
#include "dc_motor.h"
#include <avr/io.h>
#include "eeprom.h"
#include "buzzer.h"

/******************************************************
 * global variables
 ******************************************************/
/*hold the values of the first Password*/
uint8 arr2_password[SIZE];
/*hold the Values of the second Password*/
uint8 arr2_repeated_password[SIZE];
/*hold the Values of the Input Password*/
uint8 arr_InputPassword[SIZE];

/*hold the count of Interrupts*/
uint8 tick=0;

/*
 * Function_Name:Timer1_OVF_CallBack
 *
 * Description:
 *
 * call back function that execute when ISR of Timer1
 * of OverFlow MOde Execute that response for stop
 * the motor after 15 Seconds
 */

void Timer1_OVF2_CallBack(void){
	tick++;
	/* tick==2 that is mean that timer count 15 seconds*/
	if(tick==2){
		/*stop the DC_Motor for three seconds*/
		DcMotor_Rotate(stop,0);
		/*wait for 3 seconds*/
		_delay_ms(3000);
		/*rotate the DC in anti_clock_wise direction*/
		DcMotor_Rotate(anti_clock_wise,100);
	}
	if(tick==4){
		/*stop the DC_Motor*/
		DcMotor_Rotate(stop,0);
		Timer1_deInit();
		tick=0;
	}
}
/*
 * Function_Name:Timer1_Buzzer_Off
 *
 * Description:
 *
 * call back function that execute when ISR of Timer1
 * of OverFlow MOde Execute that response for disable
 * the Buzzer after 60 Seconds
 */

void Timer1_Buzzer_Off(void){
	tick++;
	if(tick==8){ /*it means 60 seconds*/
		tick=0;
		Timer1_deInit();
		Buzzer_off();
	}
}
/*to check the two passwords */
void Check_Passwords(void){
	uint8 check=CORRECT;
	uint16 count;
	/*recieve the first Password*/
    UART_recieveString(arr2_password);
	/*recieve the second Password*/
    UART_recieveString(arr2_repeated_password);
	/*check the two Passwords*/
	for(count=0;count<PAS_SIZE;count++){
		if(arr2_password[count]!=arr2_repeated_password[count]){
			check=NOT_CORRECT;
		}
	}
	UART_sendByte(check);
	//_delay_us(10);
	if(check==CORRECT){
		for(count=0;count<PAS_SIZE;count++){
			/*save the Password in the EEPROM*/
			EEPROM_writeByte(0x0311+count,arr2_password[count]);
			_delay_ms(10);
		}
	}
}
/*
 * to confirm that two passwords are matched
 */
uint8 password_is_matched(void){
	/*hold the data from eeprom*/
	uint8 data,state=CORRECT;
	uint16 count;
	UART_recieveString(arr_InputPassword);
	for(count=0;count<PAS_SIZE;count++){
		EEPROM_readByte(0x0311+count,&data);
		_delay_ms(10);
		if(arr_InputPassword[count]!=data){
			state=NOT_CORRECT;
			break;
		}
	}
	return state;
}
/* Function_Name:password_matched
 *
 * Description:
 *
 * execute some actions when two passwords are matched
 */
void password_matchedWithClockWise(void){
	/*to rotate in clock_wise and with maximum speed*/
	DcMotor_Rotate(clock_wise,100);
	/*send a required message to HMI_ECU*/
	UART_sendString("Door is Unlock#");
	/* create object from structure Timer1_ConfigType
	 * to hold the required configuration of Timer1
	 */
	Timer1_ConfigType timer1_conf;
	/*
	 * the required configurations
	 *
	 */
	/*
	 * use OVF Mode
	 * Note:
	 * I can use Compare mode and make the compare value
	 * equal=60000
	 * but I Wanna do this to test both modes
	 * */
	timer1_conf.mode=NORMAL_MODE;
	/*to make INterrupt Every 7.5 Seconds
	 *that is mean I need 2-Interrupt for 15 seconds
	 */
	timer1_conf.initial_value=5536;  /*start count from 5536*/
	timer1_conf.prescalar=CLK_1024;
	Timer1_init(&timer1_conf);
    //_delay_ms(1);
	Timer1_setCallBack(Timer1_OVF2_CallBack);
}

/* Function_Name:Activate_Buzzer
 *
 * Description:
 *
 *Activate the Buzzer for 1 Minute Using Timer1
 */
void Activate_Buzzer(void){
	Timer1_ConfigType timer1_conf;
	/*the required configurations*/
	timer1_conf.mode=COMPARE_MODE; /*use Compare Mode*/
	timer1_conf.initial_value=0;  /*start count from 0*/
	timer1_conf.prescalar=CLK_1024;
	/*that is mean 60 seconds with 1MHZ with 1 Interrupt*/
	timer1_conf.compare_value=60000;
	Timer1_init(&timer1_conf);
	Buzzer_on();
	Timer1_setCallBack(Timer1_Buzzer_Off);
}

