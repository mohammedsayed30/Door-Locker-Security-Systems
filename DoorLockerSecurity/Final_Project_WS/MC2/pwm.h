 /********************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.h
 *
 * Description: header file for the AVR_Timer0 pwm driver
 *
 * Created on:- 5/10/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 *********************************************************************/
#ifndef PWM_H_
#define PWM_H_
#include "std_types.h"
/*********************************************************************
 *                           Definitions                             *
*********************************************************************/
#define PRESCALAR          8
#define PWM_PORT_ID       PORTB_ID
#define PWM_PIN_ID        PIN3_ID
/*********************************************************************
 *                           Prototypes                             *
*********************************************************************/
/*
 * Description:-
 * setup the the PWM mode with required configuration
 */
void PWM_Timer0_Start(uint8 duty_cycle);
#endif /* PWM_H_ */
