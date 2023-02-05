 /******************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.c
 *
 * Description:Source file for the External Buzzer driver
 *
 * Created on:28/10/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 *****************************************************/
#include "buzzer.h"

/*******************************************************
 *           Function Definitions
 *******************************************************/

/*
 * Function_Name:Buzzer_init
 *
 * Description:
 *
 * to initialize the Buzzer With its configurations Like:
 * -->setup the direction of pin
 * -->turn it off at the begging
 */
void Buzzer_init(void){
	/* setup the pin_Buzzer as output pin*/
	GPIO_setupPinDirection( BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	/*Turn off the Buzzer at the begging*/
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID ,LOGIC_LOW);
}

/*
 * Function_Name:Buzzer_on
 *
 * Description:
 *
 * to enable the Buzzer
 */
void Buzzer_on(void){
	/*Turn ON the Buzzer */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID ,LOGIC_HIGH);
}

/*
 * Function_Name:Buzzer_on
 *
 * Description:
 *
 * to disable the Buzzer
 */
void Buzzer_off(void){
	/*Turn OFF the Buzzer */
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID ,LOGIC_LOW);
}

