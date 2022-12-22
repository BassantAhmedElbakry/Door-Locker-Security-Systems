/*************************************************************************************************************
 * Module : BUZZER
 *
 * File name : buzzer.h
 *
 * Description: header file for the AVR buzzer driver
 *
 * Author: BASSANT AHMED
 ************************************************************************************************************/


#ifndef BUZZER_H_
#define BUZZER_H_

/************************************************************************************************************
 *                                           Definitions                                                    *
 ***********************************************************************************************************/

#define BUZZER_PORT PORT_D
#define BUZZER_PIN  PIN_7

/************************************************************************************************************
 *                                        Functions Prototypes                                              *
 ***********************************************************************************************************/

/*
 * Setup the direction for the buzzer pin as output pin through the
 * GPIO driver
 * Turn off the buzzer through the GPIO
 */
void Buzzer_init();

/*
 * Function to enable the Buzzer through the GPIO
 */
void Buzzer_on(void);

/*
 * Function to disable the Buzzer through the GPIO
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
