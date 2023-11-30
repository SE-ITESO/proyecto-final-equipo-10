/*
 * states_machine.c
 *
 *  Created on: 30 nov. 2023
 *      Author: gabyd
 */

#include "states_machine.h"
#include "gpio.h"
#include "conversion.h"
#include "adc.h"

States_t g_states = ADELANTE;


void initial_machine(void)
{
	uint32_t adcValueMotor = ADC_Read_Motor();

	switch(g_states)
	{
	case(ADELANTE):

		AdcToPwmMotor(adcValueMotor);

		if(TRUE == !GPIO_PinRead(GPIOC, REVERSE))
		{
			g_states = ATRAS;
		}

	break;
	case(ATRAS):


		AdcToPwmMotorBwd(adcValueMotor);

		if(TRUE == GPIO_PinRead(GPIOC, REVERSE))
		{
			g_states = ADELANTE;
		}


	break;

	}
}
