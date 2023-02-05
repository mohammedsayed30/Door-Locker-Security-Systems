/*******************************************************************
 * *****************************************************************
 * Model:- dc_motor.c
 * Description:- source file for DC Motor
 * Created on :- 5/10/2022
 * Author: Mohammed Sayed Shaaban
 *******************************************************************
 *******************************************************************/
#include  "gpio.h"         /*to use the gpio_Driver*/
#include  "dc_motor.h"
#include  "pwm.h"          /*to use the pwm_Driver*/
#include  "timer1.h"

/*******************************************************
 *                Global Variables
 *******************************************************/

/*
 * Description:-
 * 1-the function that response for setup the port and the pins of motor
 * 2-stop the DC_motor at the beginning
 */


void DcMotor_init(void){
	/*setup the direction of the two pins of DC_Motor*/
	GPIO_setupPinDirection(DC_PORT_ID ,DC_FIRST_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_PORT_ID ,DC_SECOND_PIN_ID,PIN_OUTPUT);
	/*stop the motor at the beginning*/
	GPIO_writePin(DC_PORT_ID,DC_FIRST_PIN_ID,LOGIC_LOW );
	GPIO_writePin(DC_PORT_ID,DC_SECOND_PIN_ID,LOGIC_LOW );
}
/*
 * Description:-
 * 1-the function that response for rotate the DC Motor CW or A-CW
 * or Stop the Motor based on the state input
 * 2-Send the Required duty  cycle to the PWM based on the required
 * speed Value(0----->100)
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed){

	if(state == clock_wise){
		/* rotate with clock wise direction*/
		GPIO_writePin(DC_PORT_ID,DC_FIRST_PIN_ID,LOGIC_LOW );
		GPIO_writePin(DC_PORT_ID,DC_SECOND_PIN_ID,LOGIC_HIGH );
	}
	else if(state == anti_clock_wise){
		/* rotate with anti clock wise direction*/
		GPIO_writePin(DC_PORT_ID,DC_FIRST_PIN_ID,LOGIC_HIGH);
		GPIO_writePin(DC_PORT_ID,DC_SECOND_PIN_ID,LOGIC_LOW);
	}
	else{      /*stop the DC_Motor*/
		GPIO_writePin(DC_PORT_ID,DC_FIRST_PIN_ID,LOGIC_LOW);
		GPIO_writePin(DC_PORT_ID,DC_SECOND_PIN_ID,LOGIC_LOW);
	}
	/*call PWM function to detect Speed*/
	PWM_Timer0_Start(speed);
}

