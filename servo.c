/*
 * servo.c
 *
 *  Created on: Nov 26, 2023
 *      Author: jorgeleautaud
 */

#include "fsl_ftm.h"
#include "FlexTimer.h"
#include "servo.h"


#define FTM_MODULE FTM0
#define FTM_CHANNEL kFTM_Chnl_2
#define FTM_CLK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)

// Servo parameters
#define SERVO_MIN_PULSE_WIDTH 1000U  // Minimum pulse width for 0 degrees
#define SERVO_MAX_PULSE_WIDTH 2000U  // Maximum pulse width for 180 degrees
#define SERVO_PERIOD 20000U          // PWM period for the servo (20ms)




void initServo(void) {
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t pwmConfig;

    // Initialize FTM module
    FTM_GetDefaultConfig(&ftmInfo);
    FTM_Init(FTM_MODULE, &ftmInfo);



    // Configure FTM channel for PWM
    pwmConfig.chnlNumber = FTM_CHANNEL;
    pwmConfig.level = kFTM_HighTrue;
    pwmConfig.dutyCyclePercent = 0U; // Initial duty cycle (0-100)
    pwmConfig.firstEdgeDelayPercent = 0U;

    FTM_SetupPwm(FTM_MODULE, &pwmConfig, 1U, kFTM_EdgeAlignedPwm, SERVO_PERIOD, FTM_CLK_FREQ);

    // Start the FTM timer
    FTM_StartTimer(FTM_MODULE, kFTM_SystemClock);
}



void updateServoPosition(uint16_t potValue) {


	FTM0->CONTROLS[2].CnV = potValue;
    // Map the ADC value to servo pulse width
    uint16_t pulseWidth = SERVO_MIN_PULSE_WIDTH +
                         ((potValue * (SERVO_MAX_PULSE_WIDTH - SERVO_MIN_PULSE_WIDTH)) / 4095U);

    // Set the PWM duty cycle to control servo position
    FTM_UpdatePwmDutycycle(FTM_MODULE, FTM_CHANNEL, kFTM_EdgeAlignedPwm, (pulseWidth * 100U) / SERVO_PERIOD);

}



