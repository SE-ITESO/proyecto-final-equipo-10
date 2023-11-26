/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/**
 * @file    Proyecto_NXP_embebidos.c
 * @brief   Application entry point.
 */


#include "gpio.h"
#include "nvic.h"
#include "pit.h"
#include "dac.h"
#include "adc.h"
#include "MotorShield.h"
#include "FlexTimer.h"


int main(void) {

initFTM();
initMotorControlPins();

init_PIT0();
DAC0_init();
ADC_Init();
FlexTimer_Init();

NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ,PRIORITY_5);

while(1){
	uint16_t adcValue = ADC_Read();
	DAC_SetBufferValue(DAC0, 0U, adcValue);
//	moveForward(100);
}



}
