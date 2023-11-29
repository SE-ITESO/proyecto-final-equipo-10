/*
 * Direction.c
 *
 *  Created on: 22 nov. 2023
 *      Author: gabyd
 */
#include "conversion.h"


void AdcToPwmServo(uint32_t value)
{
	if (value > ADC_MAX_VALUE)
	{
	    value = ADC_MAX_VALUE;
	}
    // Realizar la conversión
    uint32_t calcValue= ((value * 255) / ADC_MAX_VALUE);
    FlexTimer_updateCH1Value(calcValue);
}


void AdcToPwmMotorFwd(uint32_t value)
{
	if (value > ADC_MAX_VALUE)
	{
	    value = ADC_MAX_VALUE;
	}
    // Realizar la conversión
    uint32_t calcValue= ((value * 255) / ADC_MAX_VALUE);
    moveForward(calcValue);
}


