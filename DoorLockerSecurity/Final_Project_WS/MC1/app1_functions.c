 /******************************************************
 *
 * File Name: app1_functions.h
 *
 * Description: Source file for the  Required
 * Functions Definitions
 *
 * Created on:4/11/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 *******************************************************/
#include "app1_functions.h"
#include <util/delay.h>
#include "timer1.h"
#include "LCD.h"
#include "keypad.h"
#include "urat.h"

/******************************************************
 * global variables
 ******************************************************/
/*hold the values of the first Password+ ('#' && '\0')*/
uint8 arr_password[SIZE];
/*hold the Values of the second Password+ ('#' && '\0')*/
uint8 arr_repeated_password[SIZE];

/*hold the values of password+ ('#' && '\0')*/
uint8 arr_InputPassword[SIZE];

/*hold the Message from Controll ECU*/
uint8 arr_string[16];

/*to hold what the user want(open door or change pass*/
uint8 key=0;

/*to count the number of Interrupts*/
uint8 tick=0;




/*
 * Function_Name:Timer1_OVF1_CallBack
 *
 * Description:
 *
 * Execute the Instructions when the Interrupt Done Like:
 *
 * -->Display Messages depend on The state of Motor
 * */
void Timer1_OVF1_CallBack(void){
	tick++;
	if(tick==1){
	  /*the time of holding the motor(3_Seconds)*/
	  _delay_ms(3000);
	  LCD_clearScreen();
	  LCD_moveCursor(0,0);
	  LCD_displayString("Door is Locking");

    }
	if(tick==2){
		/*
		 * 1-call main options again
		 * 2-deInit the Timer
		 * 3-tick=0;
		*/
        /*to waiting the DcMotor Finish his Cycle
         *some lag in calculations
         */
		_delay_ms(1000);
		key=Main_Opitions();
		tick=0;
		Timer1_deInit();
	}
}

/*
 * Function_Name:Timer1_OVF1_CallBack
 *
 * Description:
 *
 * Execute the Instructions when the Interrupt Done Like:
 *
 * -->Call main options again
 * */

void Timer1_COMP_Error(void){
	tick++;
	if(tick==1){  /*equal 60 seconds*/
		tick=0;
		Timer1_deInit();
		key=Main_Opitions();
	}
}

/*
 * Function_Name:UserInterface_step1
 *
 * description:
 *
 * get Password from user
 */

void UserInterface_Step1(void){

	/*that hold the input from user*/
	uint8 UserInput=0,count;
	/*to hold the index of array*/
	uint8 index=0;
	/*clean the LCD*/
	LCD_clearScreen();
	/*
	 * entering password step
	 */
	LCD_displayString("plz enter pass: ");
	/*to move the cursor to the second row*/
	LCD_moveCursor(1,0);
	/*loop six times(Five Digit + Enter Pressed)*/
	for(count=0;count<=SIZE;count++){
		UserInput=KEYPAD_getButtonPressed();
		/*its mean he pressed on Enter keyword*/
		if(UserInput==ENTER)
			break;   /*move to next step*/
		if(index<5){
		   /*save the password in this array*/
		   arr_password[index++]=UserInput;
		   /*display (*) for each input_digit*/
		   LCD_displayCharacter('*');
		   /*the time of press*/
		   _delay_ms(500);
		}

	}
	arr_password[index++]='#';
	arr_password[index++]='\0';

	/*
	 * the repeated password step
	 */

	/*to make sure that is not Hold the ascii of Enter
	 * as that is due to cancel the confirm password
	 */
	UserInput=0;
	index=0; /*to begin at index =0*/
	LCD_clearScreen();
	/*to move the cursor to the first row again*/
	LCD_moveCursor(0,0);
	LCD_displayString("plz re-enter the ");
	LCD_moveCursor(1,0);
	LCD_displayString("same pass: ");

	for(count=0;count<=SIZE;count++){
		UserInput=KEYPAD_getButtonPressed();
		/*its mean he pressed on Enter keyword*/
		if(UserInput==ENTER)
			break;   /*move to next step*/
		if(index<5){
			/*save the confirmed password in this array*/
		   arr_repeated_password[index++]=UserInput;
		   /*display (*) for each input_digit*/
		   LCD_displayCharacter('*');
		   /*the time of press*/
		   _delay_ms(500);
		}

	}
	arr_repeated_password[index++]='#';
	arr_repeated_password[index++]='\0';
}

/*
 * Function_Name:SendPasswordToControl_ECU();
 *
 * description:
 *
 * send  Passwords to Controll_ECU
 */
uint8 SendPasswordToControl_ECU(void){
	uint8 count;
	/*send the first password to Control_ECU*/
	UART_sendString(arr_password);
	/*send the second password to Control_ECU*/
	UART_sendString(arr_repeated_password);
	/*to know that two password are correct or not*/
	//_delay_us(10);
	return UART_recieveByte();

}
/*
 * Function_Name:UserInterface_Step2
 *
 * description:
 *
 * the interfacing with user after confirm that two
 * passwords are correct
 */
uint8 Main_Opitions(void){
	/*to hold the input user in main option step*/
	uint8 key;
	/*clear the screen*/
	LCD_clearScreen();
	LCD_moveCursor(0,1);
	LCD_displayString("+ : Open Door");
	LCD_moveCursor(1,1);
	LCD_displayString("- : Change Pass");
	/*
	 * this do_while if the user pressed any button
	 * beside (+) or (-)
	 */
	do{
	    key=KEYPAD_getButtonPressed();
	}while((key !='+') && (key !='-'));
	return key;
}

/*
 * Function_Name:UserInterface_Step3
 *
 * description:
 *
 * the interfacing with user after he choice open door
 *
 */
uint8 Open_Door(void){
	uint8 UserInput,index=0;
	/*used as count with for loops*/
	uint8 count;
	/*clear the screen*/
	LCD_clearScreen();
	/*move cursor to the 1th row and the 2th column*/
	LCD_moveCursor(0,1);
	/*ask the user to enter the password*/
	LCD_displayString("plz enter pass:");
	LCD_moveCursor(1,1);
	for(count=0;count<=PAS_SIZE;count++){
		UserInput=KEYPAD_getButtonPressed();
		/*its mean he pressed on Enter keyword*/
		if(UserInput==ENTER)
			break;   /*move to next step*/
		if(index<5){
			/*save the confirmed password in this array*/
			arr_InputPassword[index++]=UserInput;
		   /*display (*) for each input_digit*/
		   LCD_displayCharacter('*');
		   /*the time of press*/
		   _delay_ms(500);
		}

	}
	LCD_clearScreen();
	arr_InputPassword[index++]='#';
	arr_InputPassword[index++]='\0';
	/*send the Password to Control_ECU*/
	UART_sendString(arr_InputPassword);
    return UART_recieveByte();
}

/*
 * Function_Name:Change_Pass
 *
 * description:
 *
 * Response for Change the password
 *
 */

uint8 Change_Pass(void){

	uint8 change_state;
	/*as I need the same code of Open_Door Functions*/
	change_state=Open_Door();
	return change_state;
}

void display_String(void){
	/*
	 * 1-receive the message from Control_ECU
	 * 2-display the Message  on the screen
	 * ("Door is Unlocking")
	 */
	UART_recieveString(arr_string);
	LCD_moveCursor(0,0);
	LCD_displayString(arr_string);

	Timer1_ConfigType timer1_conf;
	/*the required configurations*/
	timer1_conf.mode=COMPARE_MODE; /*use Compare Mode*/
	timer1_conf.initial_value=0;  /*start count from 0*/
	timer1_conf.prescalar=CLK_1024;
	timer1_conf.compare_value=15000;
	Timer1_init(&timer1_conf);
    //_delay_ms(1);
	Timer1_setCallBack(Timer1_OVF1_CallBack);

}
/*
 * Function_Name:Error_Message()
 *
 * description:
 *
 * 1-display error Message for one Minute also
 * 2-system does not accept any input from user for 1 Minute
 * 3-Display the Main Options again after this Period
 */

void Error_Message(void){
	Timer1_ConfigType timer1_conf;
	/*the required configurations*/
	timer1_conf.mode=COMPARE_MODE; /*use Compare Mode*/
	timer1_conf.initial_value=0;  /*start count from 0*/
	timer1_conf.prescalar=CLK_1024;
	/*that is mean 60 seconds with 1MHZ with 1 Interrupt*/
	timer1_conf.compare_value=60000;
	Timer1_init(&timer1_conf);
	Timer1_setCallBack(Timer1_COMP_Error);
	LCD_clearScreen();
	LCD_moveCursor(0,5);
	LCD_displayString("ERROR");
}

