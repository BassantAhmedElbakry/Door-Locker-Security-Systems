/*************************************************************************************************************
 * Module : BUZZER
 *
 * File name : buzzer.c
 *
 * Description: Source file for the AVR buzzer driver
 *
 * Author: BASSANT AHMED
 ************************************************************************************************************/

#include"buzzer.h"
#include"gpio.h"

/*
 * Setup the direction for the buzzer pin as output pin through the
 * GPIO driver
 * Turn off the buzzer through the GPIO
 */
void Buzzer_init(){

	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, OUTPUT_PIN);
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOW);

}

/*
 * Function to enable the Buzzer through the GPIO
 */
void Buzzer_on(void){

	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, HIGH);
}

/*
 * Function to disable the Buzzer through the GPIO
 */
void Buzzer_off(void){

	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOW);
}
