/***********************************************************************************************************
 * Module : TIMER1
 *
 * File name : timer1.c
 *
 * Description : Source file for Timer1 AVR driver
 *
 * Author: BASSANT AHMED
 **********************************************************************************************************/

#include<avr/io.h>
#include <avr/interrupt.h>
#include "common_macros.h"
#include"std_types.h"
#include"timer1.h"

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/**********************************************************************************************************
 *                                              ISR                                                       *
 *********************************************************************************************************/

ISR(TIMER1_OVF_vect){

	if(g_callBackPtr != NULL_PTR)
		(*g_callBackPtr)();

}

ISR(TIMER1_COMPA_vect){

	if(g_callBackPtr != NULL_PTR)
		(*g_callBackPtr)();
}

ISR(TIMER1_COMPB_vect){

	if(g_callBackPtr != NULL_PTR)
		(*g_callBackPtr)();

}

/**********************************************************************************************************
 *                                        Functions Definitions                                           *
 *********************************************************************************************************/

/*
 * Description :
 * Function to initialize the Timer driver
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr){

	TCNT1 = Config_Ptr->initial_value;

	/*Non pwm mode*/
	SET_BIT(TCCR1A,FOC1A);
	SET_BIT(TCCR1A,FOC1B);

	if(Config_Ptr->mode == Normal){

		SET_BIT(TIMSK,TOIE1);
	}
	else if(Config_Ptr->mode == CompareA){

		SET_BIT(TCCR1B,WGM12);
		OCR1A = Config_Ptr->compare_value;
		SET_BIT(TCCR1A,COM1A1);
		SET_BIT(TIMSK,OCIE1A);
	}
	else if(Config_Ptr->mode == CompareB){

		SET_BIT(TCCR1B,WGM12);
		OCR1B = Config_Ptr->compare_value;
		SET_BIT(TCCR1A,COM1B1);
		SET_BIT(TIMSK,OCIE1B);
	}

	TCCR1B = (TCCR1B & 0xF8) | ((Config_Ptr->prescaler) & 0x07);
}

/*
 * Description :
 * Function to disable the Timer1
 */
void Timer1_deInit(void){

	/*Pre-scaler = 0 "No clock source" */
	TCCR1B &= 0xF8;
}

/*
 * Description :
 * Function to set the Call Back function address
 */
void TIMER1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr  ;
}
