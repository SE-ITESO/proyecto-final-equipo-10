/*
 * Direction.h
 *
 *  Created on: 22 nov. 2023
 *      Author: gabyd
 */

#ifndef DIRECTION_H_
#define DIRECTION_H_

#include "adc.h"
#include "FlexTimer.h"
#include "fsl_ftm.h"


void initServo(void);

void AdcToPwm(uint32_t value);

#endif /* DIRECTION_H_ */
