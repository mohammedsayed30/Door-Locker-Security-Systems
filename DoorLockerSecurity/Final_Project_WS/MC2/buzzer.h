 /******************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description:Header file for the External Buzzer driver
 *
 * Created on:28/10/2022
 *
 * Author: Mohammed Sayed Shaaban
 *
 *****************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_
#include "std_types.h"
#include "gpio.h"
/*******************************************************
 *                      Definitions
 *******************************************************/
/*to detect which Port that connect with*/
#define BUZZER_PORT_ID         PORTC_ID
/*to detect which pin in this POrt*/
#define BUZZER_PIN_ID          PIN5_ID

/*******************************************************
 *                Function_Prototypes
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
void Buzzer_init(void);

/*
 * Function_Name:Buzzer_on
 *
 * Description:
 *
 * to enable the Buzzer
 */
void Buzzer_on(void);

/*
 * Function_Name:Buzzer_on
 *
 * Description:
 *
 * to disable the Buzzer
 */
void Buzzer_off(void);
#endif /* BUZZER_H_ */
