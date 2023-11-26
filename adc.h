/*
 * adc.h
 *
 *  Created on: 20 nov. 2023
 *      Author: gabyd
 */

#ifndef ADC_H_
#define ADC_H_

#include "clock_config.h"
#include "board.h"
#include "fsl_adc16.h"

void ADC_Init(void);
uint16_t ADC_Read(void);

#endif /* ADC_H_ */
