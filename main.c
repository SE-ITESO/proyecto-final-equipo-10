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
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "MotorShield.h"
#include "FlexTimer.h"
#include "servo.h"




int main(void) {

FlexTimer_Init();


//initServo();
initMotorControlPins();


while(1){
	moveForward(255);
	//updateServoPosition(200);


}



}
