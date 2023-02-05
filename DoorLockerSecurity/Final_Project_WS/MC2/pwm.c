 /********************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the AVR_Timer0 pwm driver
 *
 * Created on:- 5/10/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 *********************************************************************/
#include "pwm.h"
#include "gpio.h"
#include <avr/io.h>

/*
 * Description:-
 * setup the the PWM mode with required configuration
 */
void PWM_Timer0_Start(uint8 duty_cycle){
	TCNT0=0;           /*init value for timer0*/
	/*compare value for timer0*/
	OCR0=(float32)duty_cycle * (float32)2.56;  /*to get the value the present the duty cycle percentage*/
	/*set  the  OC0 as Output pin*/
	GPIO_setupPinDirection(PWM_PORT_ID ,PWM_PIN_ID,PIN_OUTPUT);
	/*setup the configuration that response for pwm_Timer0*/
#if(PRESCALAR==8)
	TCCR0=(1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
#elif(PRESCALAR==64)
	TCCR0=(1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01)|(1<<CS00);
#elif(PRESCALAR==256)
	TCCR0=(1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS02);
#elif(PRESCALAR==1024)
	TCCR0=(1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS02)|(1<<CS00);
#endif
}

