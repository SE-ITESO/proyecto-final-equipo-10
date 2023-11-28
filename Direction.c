/*
 * Direction.c
 *
 *  Created on: 22 nov. 2023
 *      Author: gabyd
 */
#include "Direction.h"

void AdcToPwm(uint32_t value)
{
    // Realizar la conversión
    uint32_t calcValue= ((value * 255) / 4095);
    FlexTimer_updateCHValue(calcValue);
}
