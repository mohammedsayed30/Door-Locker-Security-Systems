 /******************************************************
 *
 * File Name: app1_functions.h
 *
 * Description: header file for the  Required
 * Functions Prototypes
 *
 * Created on:4/11/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 *******************************************************/

#ifndef APP1_FUNCTIONS_H_
#define APP1_FUNCTIONS_H_

#include "std_types.h"
/********************************************************
 *                    Definitions
 *******************************************************/

/* to hold the size of Array the save the Five_Digit
 * for this password + ('#' && '\0')
 */
#define SIZE   7

/*size of the password only*/
#define PAS_SIZE 5
/*to detect that the two passwords Correct*/
#define CORRECT   1
/*to detect that the two passwords Not_Correct*/
#define NOT_CORRECT   0
/*make the keyword 'ON' as enter*/
#define ENTER  '='
/*******************************************************
 *                     Functions Prototypes
 *******************************************************/
/*
 * Function_Name:Timer1_OVF1_CallBack
 *
 * Description:
 *
 * Execute the Instructions when the Interrupt Done Like:
 *
 * -->Display Messages depend on The state of Motor
 * */
void Timer1_OVF1_CallBack(void);

/*
 * Function_Name:Timer1_COMP_Error
 *
 * Description:
 *
 * Execute the Instructions when the Interrupt Done Like:
 *
 * -->Call main options again
 * */

void Timer1_COMP_Error(void);

/*
 * Function_Name:UserInterface_step1
 *
 * description:
 *
 * get Password from user
 */

void UserInterface_Step1(void);

/*
 * Function_Name:SendPasswordToControl_ECU();
 *
 * description:
 *
 * send  Passwords to Controll_ECU to ensure that are same
 */
uint8 SendPasswordToControl_ECU(void);
/*
 * Function_Name:Main_Options
 *
 * description:
 *
 * the interfacing with user after confirm that two
 * passwords are correct to make the user can choice
 * "Open the door" or "Change the password"
 */
uint8 Main_Opitions(void);

/*
 * Function_Name:Open_Door
 *
 * description:
 *
 * the interfacing with user after he choice open door
 *
 */
uint8 Open_Door(void);

/*
 * Function_Name:Change_Pass
 *
 * description:
 *
 * Response for Change the password
 *
 */

uint8 Change_Pass(void);

/*
 * Function_Name:display_String
 *
 * description:
 *
 * To display the required Messages for User
 *
 */
void display_String(void);

/*
 * Function_Name:Error_Message()
 *
 * description:
 *
 * 1-display error Message for one Minute also
 * 2-system does not accept any input from user for 1 Minute
 * 3-Display the Main Options again after this Period
 */

void Error_Message(void);
#endif /* APP1_FUNCTIONS_H_ */
