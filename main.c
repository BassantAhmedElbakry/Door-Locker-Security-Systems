/************************************************************************************************************
 *
 * Module: HMI_ECU
 *
 * File name : main.c
 *
 *  Created on: ٠٢‏/١١‏/٢٠٢٢
 *
 *  Author: BASSANT AHMED
 *
 ***********************************************************************************************************/

#include<avr/io.h>
#include <util/delay.h>
#include"common_macros.h"
#include"std_types.h"
#include"lcd.h"
#include"keypad.h"
#include"timer1.h"
#include"uart.h"


/**********************************************************************************************************
 *                                               Globals                                                  *
 *********************************************************************************************************/

uint8 first_password[6];
uint8 second_password[6];
uint8 tick = 0;

/*********************************************************************************************************
 *                                             Configurations                                            *
 *********************************************************************************************************/

UART_ConfigType UART_Config  = {9600,Asynchronous,BITS_8,BIT_1,Disabled};
Timer1_ConfigType Config_Ptr1 = {0,0,Prescaler_1024,Normal};     //for 8.4sec
Timer1_ConfigType Config_Ptr2 = {13884,0,Prescaler_1024,Normal}; //for 6.6sec
Timer1_ConfigType Config_Ptr3 = {42099,0,Prescaler_1024,Normal}; //for 3sec
Timer1_ConfigType Config_Ptr4 = {55538,0,Prescaler_1024,Normal}; //for 1.2sec

/**********************************************************************************************************
 *                                        Functions Prototypes                                            *
 *********************************************************************************************************/

void HMI_setPassword(void);
void HMI_enterPassword(uint8 * password);
void HMI_re_enterPassword(uint8 * password);
void HMI_sendPassword(uint8 * password);
void HMI_Timer(void);

int main(){

	/*****************************************************************************************************
	 *                                          Local Variables                                          *
	 *****************************************************************************************************/

	uint8 myPassword[6];
	uint8 check_bit2,option;
	uint8 check_bit1;
	uint8 falseAttempts = 0;

	/*******************************************************************************************************
	 *                                          Initializations                                            *
	 ******************************************************************************************************/

	/*Enable the global interrupt*/
	SET_BIT(SREG,7);

	/*Initialize the LCD*/
	LCD_init();

	/*Initialize the KeyPad*/
	KEYPAD_init();

	/*Initialize the UART*/
	UART_init(&UART_Config);

	/*******************************************************************************************************
	 *                                            My System                                                *
	 *******************************************************************************************************/

	while(1){

		do{
			/*Get the password from user and send it to the Control_ECU*/
			HMI_setPassword();

			/*Check if the entering password and the re-entering password are the same*/
			check_bit1 = UART_recieveByte();

			LCD_clearScreen();

		}

		while(check_bit1 == FALSE);

		for(;;){

			falseAttempts = 0;

			LCD_clearScreen();

			/*Display the main options on the LCD*/
			LCD_displayStringRowColumn(0, 0, "+ : Open Door");
			LCD_displayStringRowColumn(1, 0, "- : Change Pass");

			/*Get the option from the user*/
			while( ! (option = KEYPAD_getPressedKey() ) );

			switch(option){

			/*In case user choose Open door*/
			case '+':
				do{
					/*Send the option to the Control_ECU*/
					UART_sendByte('+');
					/*Enter the password*/
					HMI_enterPassword(myPassword);
					/*Send the password to the Control_ECU*/
					HMI_sendPassword(myPassword);
					/*Check if the entered password is matched with the password of the system*/
					check_bit2 = UART_recieveByte();
					if(check_bit2 == TRUE){
						falseAttempts = 0;

						/* Display a message on the screen “Door is Unlocking” for 15 seconds */
						LCD_clearScreen();
						LCD_displayString("Door is ");
						LCD_displayStringRowColumn(1, 0, "Unlocking");

						/*Start timer1 from 0 to reach the end its time is = 8.4 seconds*/
						Timer1_init(&Config_Ptr1);
						TIMER1_setCallBack(HMI_Timer);
						while(tick < 1);
						tick = 0;
						Timer1_deInit();

						/*Calculate 6.6 seconds now the time is = 8.4 + 6.6 = 15 seconds*/
						Timer1_init(&Config_Ptr2);
						TIMER1_setCallBack(HMI_Timer);

						while(tick < 1);
						tick = 0;
						Timer1_deInit();

						/*Hold the motor for 3 seconds*/
						LCD_clearScreen();
						LCD_displayString("Door is ");
						LCD_displayStringRowColumn(1, 0, "Unlocked");

						Timer1_init(&Config_Ptr3);
						TIMER1_setCallBack(HMI_Timer);
						while(tick < 1);
						tick = 0;
						Timer1_deInit();

						/* Display a message on the screen “Door is Locking” for 15 seconds */
						LCD_clearScreen();
						LCD_displayString("Door is Locking");

						/*Start timer1 from 0 to reach the end its time is = 8.4 seconds*/
						Timer1_init(&Config_Ptr1);
						TIMER1_setCallBack(HMI_Timer);

						while(tick < 1);
						tick = 0;
						Timer1_deInit();

						/*Calculate 6.6 seconds now the time is = 8.4 + 6.6 = 15 seconds*/
						Timer1_init(&Config_Ptr2);
						TIMER1_setCallBack(HMI_Timer);

						while(tick < 1);
						tick = 0;
						Timer1_deInit();

						LCD_clearScreen();
						LCD_displayString("Door is ");
						LCD_displayStringRowColumn(1, 0, "locked");
						_delay_ms(500);

						break;
					}
					else{
						falseAttempts++;
						if(falseAttempts < 3){
							continue;

						}
						else{

							/*Start timer1 from 0 to reach the end its time is = 8.4 seconds*/
							Timer1_init(&Config_Ptr1);
							TIMER1_setCallBack(HMI_Timer);

							/*Display error message on LCD for 1 minute*/
							LCD_clearScreen();
							LCD_displayString("Elha2ny Yaaaa");
							LCD_displayStringRowColumn(1, 0, "Fa5ryyyy");

							/*Every one tick = 8.4 seconds the time now is = 7*8.4 = 58.8 seconds*/
							while(tick < 7);
							tick = 0;
							Timer1_deInit();

							/*Calculate 1.2 seconds now the time is = 58.8 + 1.2 = 1 minute*/
							Timer1_init(&Config_Ptr4);
							TIMER1_setCallBack(HMI_Timer);
							while(tick < 1);
							tick = 0;
							Timer1_deInit();

							falseAttempts = 0;
							break;
						}
					}
				}
				while(falseAttempts < 3);
				break;

			/*In case user choose Change Password*/
			case '-' :
				do{
					/*Send the option to the Control_ECU*/
					UART_sendByte('-');
					/*Enter the password*/
					HMI_enterPassword(myPassword);
					/*Send the password to the Control_ECU*/
					HMI_sendPassword(myPassword);
					/*Check if the entered password is matched with the password of the system*/
					check_bit2 = UART_recieveByte();
					if(check_bit2 == TRUE){
						falseAttempts = 0;
						do{
							HMI_setPassword();

							check_bit1 = UART_recieveByte();

							LCD_clearScreen();

						}

						while(check_bit1 == FALSE);
						break;
					}
					else{
						falseAttempts++;
						if(falseAttempts < 3){
							continue;

						}

						/*If user enter wrong password for 3 times*/
						else{
							/*Start timer1 from 0 to reach the end its time is = 8.4 seconds*/
							Timer1_init(&Config_Ptr1);
							TIMER1_setCallBack(HMI_Timer);

							/*Display error message on LCD for 1 minute*/
							LCD_clearScreen();
							LCD_displayString("Elha2ny Yaaaa");
							LCD_displayStringRowColumn(1, 0, "Fa5ryyyy");

							/*Every one tick = 8.4 seconds the time now is = 7*8.4 = 58.8 seconds*/
							while(tick < 7);
							tick = 0;
							Timer1_deInit();

							/*Calculate 1.2 seconds now the time is = 58.8 + 1.2 = 1 minute*/
							Timer1_init(&Config_Ptr4);
							TIMER1_setCallBack(HMI_Timer);
							while(tick < 1);
							tick = 0;
							Timer1_deInit();

							falseAttempts = 0;
							break;
						}
					}
				}
				while(falseAttempts < 3);
				break;

			/*In case user enter any wrong character*/
			default:
				LCD_clearScreen();
				LCD_displayString("Enter only");
				LCD_displayStringRowColumn(1, 0, "+ or -");
				_delay_ms(500);
				break;

			}
		}

	}

	return 0;
}

/**********************************************************************************************************
 *                                        Functions Definitions                                           *
 *********************************************************************************************************/
/*
 * Description :
 * Function to Set the password of the system
 */
void HMI_setPassword(void){

	HMI_enterPassword(first_password);
	HMI_re_enterPassword(second_password);

	HMI_sendPassword(first_password);
	HMI_sendPassword(second_password);

}

/*
 * Description :
 * Function to enter the password
 */
void HMI_enterPassword(uint8 * password){

	uint8 i = 0;

	LCD_clearScreen();

	LCD_displayString("plz enter pass:");
	LCD_moveCursor(1, 0);

	for(i = 0 ; i < 5 ; i++){
		while( !( password[i] = KEYPAD_getPressedKey() ) );
		LCD_displayCharacter('*');
	}
	password[i] = '\0';
	while(KEYPAD_getPressedKey() != 'O');
}

/*
 * Description :
 * Function to re-enter the password
 */
void HMI_re_enterPassword(uint8 * password){

	uint8 i = 0;

	LCD_clearScreen();

	LCD_displayStringRowColumn(0, 0,"plz re-enter the");
	LCD_displayStringRowColumn(1, 0, "same pass: ");

	for(i = 0 ; i < 5 ; i++){
		while( !( password[i] = KEYPAD_getPressedKey() ) );
		LCD_displayCharacter('*');
	}
	password[i] = '\0';
	while(KEYPAD_getPressedKey() != 'O');

}

/*
 * Description :
 * Function to send the password to the Control_ECU
 */
void HMI_sendPassword(uint8 * password){

	uint8 i = 0;

	while(password[i] != '\0'){
		UART_sendByte(password[i]);
		i++;
	}
}

/*
 * Description :
 * Call back function
 */
void HMI_Timer(void){
	tick++;
}
