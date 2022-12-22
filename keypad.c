/***********************************************************************************************************
 * Module : KEYPAD
 *
 * File name : keypad.h
 *
 * Description : Source file for keypad driver
 *
 * Author: BASSANT AHMED
 **********************************************************************************************************/

#include "keypad.h"
#include "gpio.h"
#include<util/delay.h>

/**********************************************************************************************************
 *                                        Functions Definitions                                            *
 *********************************************************************************************************/

/*
 * Description :
 * Initialize the KEYPAD:
 * Setup the KEYPAD pins directions by use the GPIO driver.
 */
void KEYPAD_init(void){

	/*Rows --> OutPut*/

	GPIO_setupPinDirection(PORT_ROW_0    , PIN_ROW_0   , OUTPUT_PIN);
	GPIO_setupPinDirection(PORT_ROW_1    , PIN_ROW_1   , OUTPUT_PIN);
	GPIO_setupPinDirection(PORT_ROW_2    , PIN_ROW_2   , OUTPUT_PIN);
	GPIO_setupPinDirection(PORT_ROW_3    , PIN_ROW_3   , OUTPUT_PIN);

	/*Columns --> InPut*/

	GPIO_setupPinDirection(PORT_COLUMN_0 , PIN_COLUMN_0, INPUT_PIN);
	GPIO_setupPinDirection(PORT_COLUMN_1 , PIN_COLUMN_1, INPUT_PIN);
	GPIO_setupPinDirection(PORT_COLUMN_2 , PIN_COLUMN_2, INPUT_PIN);
#if(KEYPAD_NUM_COLS == 4)
	GPIO_setupPinDirection(PORT_COLUMN_3 , PIN_COLUMN_3, INPUT_PIN);
#endif

	/*Active pull up at columns pins*/

	GPIO_writePin(PORT_COLUMN_0    , PIN_COLUMN_0   , HIGH);
	GPIO_writePin(PORT_COLUMN_1    , PIN_COLUMN_1   , HIGH);
	GPIO_writePin(PORT_COLUMN_2    , PIN_COLUMN_2   , HIGH);
#if(KEYPAD_NUM_COLS == 4)
	GPIO_writePin(PORT_COLUMN_3    , PIN_COLUMN_3   , HIGH);
#endif

	return;
}

/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(void){

#if(KEYPAD_NUM_COLS == 4)
	char KeyPad_Buttons[4][4] = { {Button_0  , Button_1  , Button_2  ,  Button_3}
	                             ,{Button_4  , Button_5  , Button_6  ,  Button_7}
	                             ,{Button_8  , Button_9  , Button_10 , Button_11}
	                             ,{Button_12 , Button_13 , Button_14 , Button_15} };

	char PRESSED_BUTTON = NOT_PRESS;

	/*Check the inputs of the first ROW */

	GPIO_writePin(PORT_ROW_0, PIN_ROW_0, LOW);
	GPIO_writePin(PORT_ROW_1, PIN_ROW_1, HIGH);
	GPIO_writePin(PORT_ROW_2, PIN_ROW_2, HIGH);
	GPIO_writePin(PORT_ROW_3, PIN_ROW_3, HIGH);

	if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) )
			PRESSED_BUTTON = KeyPad_Buttons[0][0];

		while( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) )
			PRESSED_BUTTON = KeyPad_Buttons[0][1];

		while( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) )
			PRESSED_BUTTON = KeyPad_Buttons[0][2];

		while( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_3, PIN_COLUMN_3)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_3, PIN_COLUMN_3)) )
			PRESSED_BUTTON = KeyPad_Buttons[0][3];

		while( !(GPIO_readPin(PORT_COLUMN_3, PIN_COLUMN_3)) );

	}

	/*Check the inputs of the second ROW */

	GPIO_writePin(PORT_ROW_0, PIN_ROW_0, HIGH);
	GPIO_writePin(PORT_ROW_1, PIN_ROW_1, LOW);
	GPIO_writePin(PORT_ROW_2, PIN_ROW_2, HIGH);
	GPIO_writePin(PORT_ROW_3, PIN_ROW_3, HIGH);

	if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) )
			PRESSED_BUTTON = KeyPad_Buttons[1][0];

		while( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) )
			PRESSED_BUTTON = KeyPad_Buttons[1][1];

		while( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) )
			PRESSED_BUTTON = KeyPad_Buttons[1][2];

		while( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_3, PIN_COLUMN_3)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_3, PIN_COLUMN_3)) )
			PRESSED_BUTTON = KeyPad_Buttons[1][3];

		while( !(GPIO_readPin(PORT_COLUMN_3, PIN_COLUMN_3)) );

	}

	/*Check the inputs of the third ROW */

	GPIO_writePin(PORT_ROW_0, PIN_ROW_0, HIGH);
	GPIO_writePin(PORT_ROW_1, PIN_ROW_1, HIGH);
	GPIO_writePin(PORT_ROW_2, PIN_ROW_2, LOW);
	GPIO_writePin(PORT_ROW_3, PIN_ROW_3, HIGH);

	if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) )
			PRESSED_BUTTON = KeyPad_Buttons[2][0];

		while( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) )
			PRESSED_BUTTON = KeyPad_Buttons[2][1];

		while( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) )
			PRESSED_BUTTON = KeyPad_Buttons[2][2];

		while( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_3, PIN_COLUMN_3)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_3, PIN_COLUMN_3)) )
			PRESSED_BUTTON = KeyPad_Buttons[2][3];

		while( !(GPIO_readPin(PORT_COLUMN_3, PIN_COLUMN_3)) );

	}

	/*Check the inputs of the fourth ROW */

	GPIO_writePin(PORT_ROW_0, PIN_ROW_0, HIGH);
	GPIO_writePin(PORT_ROW_1, PIN_ROW_1, HIGH);
	GPIO_writePin(PORT_ROW_2, PIN_ROW_2, HIGH);
	GPIO_writePin(PORT_ROW_3, PIN_ROW_3, LOW);

	if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) )
			PRESSED_BUTTON = KeyPad_Buttons[3][0];

		while( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) )
			PRESSED_BUTTON = KeyPad_Buttons[3][1];

		while( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) )
			PRESSED_BUTTON = KeyPad_Buttons[3][2];

		while( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_3, PIN_COLUMN_3)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_3, PIN_COLUMN_3)) )
			PRESSED_BUTTON = KeyPad_Buttons[3][3];

		while( !(GPIO_readPin(PORT_COLUMN_3, PIN_COLUMN_3)) );

	}
#elif(KEYPAD_NUM_COLS == 3)

	char KeyPad_Buttons[4][3] = { {Button_0  , Button_1  , Button_2  }
	                             ,{Button_3  , Button_4  , Button_5  }
	                             ,{Button_6  , Button_7  , Button_8  }
	                             ,{Button_9  , Button_10 , Button_11 } };

	char PRESSED_BUTTON = NOT_PRESS;

	/*Check the inputs of the first ROW */

	GPIO_writePin(PORT_ROW_0, PIN_ROW_0, LOW);
	GPIO_writePin(PORT_ROW_1, PIN_ROW_1, HIGH);
	GPIO_writePin(PORT_ROW_2, PIN_ROW_2, HIGH);
	GPIO_writePin(PORT_ROW_3, PIN_ROW_3, HIGH);

	if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) )
			PRESSED_BUTTON = KeyPad_Buttons[0][0];

		while( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) )
			PRESSED_BUTTON = KeyPad_Buttons[0][1];

		while( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) )
			PRESSED_BUTTON = KeyPad_Buttons[0][2];

		while( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) );

	}

	/*Check the inputs of the second ROW */

	GPIO_writePin(PORT_ROW_0, PIN_ROW_0, HIGH);
	GPIO_writePin(PORT_ROW_1, PIN_ROW_1, LOW);
	GPIO_writePin(PORT_ROW_2, PIN_ROW_2, HIGH);
	GPIO_writePin(PORT_ROW_3, PIN_ROW_3, HIGH);

	if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) )
			PRESSED_BUTTON = KeyPad_Buttons[1][0];

		while( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) )
			PRESSED_BUTTON = KeyPad_Buttons[1][1];

		while( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) )
			PRESSED_BUTTON = KeyPad_Buttons[1][2];

		while( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) );

	}

	/*Check the inputs of the third ROW */

	GPIO_writePin(PORT_ROW_0, PIN_ROW_0, HIGH);
	GPIO_writePin(PORT_ROW_1, PIN_ROW_1, HIGH);
	GPIO_writePin(PORT_ROW_2, PIN_ROW_2, LOW);
	GPIO_writePin(PORT_ROW_3, PIN_ROW_3, HIGH);

	if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) )
			PRESSED_BUTTON = KeyPad_Buttons[2][0];

		while( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) )
			PRESSED_BUTTON = KeyPad_Buttons[2][1];

		while( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) )
			PRESSED_BUTTON = KeyPad_Buttons[2][2];

		while( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) );

	}

	/*Check the inputs of the fourth ROW */

	GPIO_writePin(PORT_ROW_0, PIN_ROW_0, HIGH);
	GPIO_writePin(PORT_ROW_1, PIN_ROW_1, HIGH);
	GPIO_writePin(PORT_ROW_2, PIN_ROW_2, HIGH);
	GPIO_writePin(PORT_ROW_3, PIN_ROW_3, LOW);

	if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) )
			PRESSED_BUTTON = KeyPad_Buttons[3][0];

		while( !(GPIO_readPin(PORT_COLUMN_0, PIN_COLUMN_0)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) )
			PRESSED_BUTTON = KeyPad_Buttons[3][1];

		while( !(GPIO_readPin(PORT_COLUMN_1, PIN_COLUMN_1)) );

	}

	else if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) ){

		_delay_ms(30);

		if( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) )
			PRESSED_BUTTON = KeyPad_Buttons[3][2];

		while( !(GPIO_readPin(PORT_COLUMN_2, PIN_COLUMN_2)) );

	}


#endif
	return PRESSED_BUTTON;

}
