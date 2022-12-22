/***********************************************************************************************************
 * Module : KEYPAD
 *
 * File name : keypad.h
 *
 * Description : Header file for keypad driver
 *
 * Author: BASSANT AHMED
 **********************************************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

/**********************************************************************************************************
 *                                         Definitions                                                    *
 *********************************************************************************************************/

#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

#define PIN_ROW_0      PIN_0
#define PIN_ROW_1      PIN_1
#define PIN_ROW_2      PIN_2
#define PIN_ROW_3      PIN_3

#define PIN_COLUMN_0   PIN_4
#define PIN_COLUMN_1   PIN_5
#define PIN_COLUMN_2   PIN_6
#define PIN_COLUMN_3   PIN_7

#define PORT_ROW_0     PORT_C
#define PORT_ROW_1     PORT_C
#define PORT_ROW_2     PORT_C
#define PORT_ROW_3     PORT_C

#define PORT_COLUMN_0  PORT_C
#define PORT_COLUMN_1  PORT_C
#define PORT_COLUMN_2  PORT_C
#define PORT_COLUMN_3  PORT_C

#if (KEYPAD_NUM_COLS == 4)

#define Button_0  '7'
#define Button_1  '8'
#define Button_2  '9'
#define Button_3  '/'
#define Button_4  '4'
#define Button_5  '5'
#define Button_6  '6'
#define Button_7  '*'
#define Button_8  '1'
#define Button_9  '2'
#define Button_10 '3'
#define Button_11 '-'
#define Button_12 'O'
#define Button_13 '0'
#define Button_14 '='
#define Button_15 '+'
#define NOT_PRESS '\0'

#elif (KEYPAD_NUM_COLS == 3)

#define Button_0  '1'
#define Button_1  '2'
#define Button_2  '3'
#define Button_3  '4'
#define Button_4  '5'
#define Button_5  '6'
#define Button_6  '7'
#define Button_7  '8'
#define Button_8  '9'
#define Button_9  '*'
#define Button_10 '0'
#define Button_11 '#'
#define NOT_PRESS '\0'

#endif
/**********************************************************************************************************
 *                                        Functions Prototypes                                            *
 *********************************************************************************************************/

/*
 * Description :
 * Initialize the KEYPAD:
 * Setup the KEYPAD pins directions by use the GPIO driver.
 */
void  KEYPAD_init(void);

/*
 * Description :
 * Get the Keypad pressed button
 */
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
