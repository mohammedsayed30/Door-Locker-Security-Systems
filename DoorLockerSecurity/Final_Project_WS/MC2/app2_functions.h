 /******************************************************
 *
 * File Name: app2_functions.h
 *
 * Description: Header file for the  Required
 * Functions Definitions for MC2
 *
 * Created on:4/11/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 *******************************************************/

#ifndef APP2_FUNCTIONS_H_
#define APP2_FUNCTIONS_H_
#include "std_types.h"

/********************************************************
 *                   Definitions
 *******************************************************/

/*
 *  to hold the size off Array the save the Five_Digit
 * for this password
 */
#define SIZE   7

/*size of the password only*/
#define PAS_SIZE 5

/*to detect that the two passwords Correct*/
#define CORRECT   1
/*to detect that the two passwords Not_Correct*/
#define NOT_CORRECT   0

/********************************************************
 *              Functions_Prototypes
 *******************************************************/

/*
 * Function_Name:Timer1_OVF_CallBack
 *
 * Description:
 *
 * call back function that execute when ISR of Timer1
 * of OverFlow MOde Execute that response for stop
 * the motor after 15 Seconds
 */

void Timer1_OVF2_CallBack(void);

/*
 * Function_Name:Timer1_Buzzer_Off
 *
 * Description:
 *
 * call back function that execute when ISR of Timer1
 * of OverFlow MOde Execute that response for disable
 * the Buzzer after 60 Seconds
 */

void Timer1_Buzzer_Off(void);

/*
 * Function_Name:Check_Passwords
 *
 * Description:
 *  to check the two Input passwords to ensure that
 *  the Same or not
 */
void Check_Passwords(void);
/*
 * Function_Name:Password_is_matched
 *
 * Description:
 *
 * to confirm that two passwords are the same
 */
uint8 password_is_matched(void);

/* Function_Name:password_matchedWithClockWise
 *
 * Description:
 *
 * execute some actions when two passwords are matched:
 * 1-Rotate the Motor for 15 Seconds
 */
void password_matchedWithClockWise(void);

/* Function_Name:Activate_Buzzer
 *
 * Description:
 *
 *Activate the Buzzer for 1 Minute Using Timer1
 */
void Activate_Buzzer(void);
#endif /* APP2_FUNCTIONS_H_ */
