/*
 * Model:- dc_motor.h
 * Description:- header file for DC Motor
 * Created on :- 5/10/2022
 * Author: Mohammed Sayed Shaaban
 *
*********************************************************************/


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "std_types.h"
#include "gpio.h"
/*********************************************************************
 *                       Definitions
 ********************************************************************/
#define      DC_PORT_ID              PORTB_ID
#define      DC_FIRST_PIN_ID         PIN1_ID
#define      DC_SECOND_PIN_ID        PIN2_ID
typedef enum{
	stop,clock_wise,anti_clock_wise
}DcMotor_State;
/*********************************************************************
 *                    Prototypes of Functions
 ********************************************************************/
/*
 * Description:-
 * 1-the function that response for setup the port and the pins of motor
 * 2-stop the DC_motor at the beginning
 */
void DcMotor_init(void);
/*
 * Description:-
 * 1-the function that response for rotate the DC Motor CW or A-CW
 * or Stop the Motor based on the state input
 * 2-Send the Required duty  cycle to the PWM based on the required
 * speed Value(0----->100)
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);
#endif /* DC_MOTOR_H_ */
