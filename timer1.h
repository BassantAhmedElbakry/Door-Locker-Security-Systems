/***********************************************************************************************************
 * Module : TIMER1
 *
 * File name : timer1.h
 *
 * Description : Header file for Timer1 AVR driver
 *
 * Author: BASSANT AHMED
 **********************************************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"

/**********************************************************************************************************
 *                                         Definitions                                                    *
 *********************************************************************************************************/

typedef enum{
	No_Prescaler,
	Prescaler_1,
	Prescaler_8,
	Prescaler_64,
	Prescaler_256,
	Prescaler_1024,
	External_clock_Falling_edge,
	External_clock_Rising_edge
}Timer1_Prescaler;

typedef enum{
	Normal,
	CompareA,
	CompareB
}Timer1_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

/**********************************************************************************************************
 *                                        Functions Prototypes                                            *
 *********************************************************************************************************/

/*
 * Description :
 * Function to initialize the Timer driver
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/*
 * Description :
 * Function to disable the Timer1
 */
void Timer1_deInit(void);

/*
 * Description :
 * Function to set the Call Back function address
 */
void TIMER1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
