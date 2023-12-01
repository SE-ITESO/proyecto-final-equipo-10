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
#include "conversion.h"
#include "buttonManager.h"
#include "states_machine.h"

int main(void) {

GPIO_init();
initMotorControlPins();
ADC_Init();
init_PIT0();
init_PIT0();
FlexTimer_Init();
FlexTimer2_Init();

NVIC_EnableIRQ(PORTD_IRQn);
NVIC_EnableIRQ(PORTC_IRQn);


while(1){

	uint32_t adcValueServo = ADC_Read_Servo();

	AdcToPwmServo(adcValueServo);
	initial_machine();
	machine_blink();



}



}
