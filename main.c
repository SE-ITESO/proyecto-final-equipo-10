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

int main(void) {

GPIO_init();
initMotorControlPins();
ADC_Init();
init_PIT0();
FlexTimer_Init();
FlexTimer2_Init();

NVIC_EnableIRQ(PORTD_IRQn);
NVIC_EnableIRQ(PORTC_IRQn);

GPIO_callback_init(GPIO_C, choose_button_pressed);

while(1){

//	leds_machine();

	uint32_t adcValueServo = ADC_Read_Servo();
	uint32_t adcValueMotor = ADC_Read_Motor();

	AdcToPwmServo(adcValueServo);
	AdcToPwmMotorFwd(adcValueMotor);


}



}
