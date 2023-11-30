/*
 * Direction.h
 *
 *  Created on: 22 nov. 2023
 *      Author: gabyd
 */

#ifndef CONVERSION_H_
#define CONVERSION_H_

#include "adc.h"
#include "FlexTimer.h"
#include "MotorShield.h"

#define ADC_MAX_VALUE 4095u

void AdcToPwmServo(uint32_t value);

void AdcToPwmMotorFwd(uint32_t value);

void AdcToPwmMotorBwd(uint32_t value);

#endif /* CONVERSION_H_ */
