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
#include "Direction.h"

uint8_t flag =0;

void set_flag(void){
	flag = 1;
}
int main(void) {

GPIO_init();
//initFTM();
//initMotorControlPins();

NVIC_global_enable_interrupts;
NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ,PRIORITY_2);
DAC0_init();
ADC_Init();
FlexTimer_Init();

while(1){
	uint32_t adcValue = ADC_Read();

	//DAC_SetBufferValue(DAC0, 0U, adcValue);


//	moveForward(100);
	AdcToPwm(adcValue);

	FlexTimer_updateCHValue(50u);

}



}
