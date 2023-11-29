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
DAC0_init();
ADC_Init();
FlexTimer_Init();
FlexTimer2_Init();

GPIO_callback_init(GPIO_D, choose_button_pressed);

while(1){
	uint32_t adcValueServo = ADC_Read_Servo();
	uint32_t adcValueMotor = ADC_Read_Motor();

	AdcToPwmServo(adcValueServo);
	AdcToPwmMotorFwd(adcValueMotor);

}



}
