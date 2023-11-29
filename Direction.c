/*
 * Direction.c
 *
 *  Created on: 22 nov. 2023
 *      Author: gabyd
 */
#include "Direction.h"
#include "FlexTimer.h"

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



void AdcToPwm(uint32_t value)
{
	if (value > 4095)
	{
	    value = 4095;
	}
    // Realizar la conversión
    uint32_t calcValue= ((value * 242) / 4095);
    FlexTimer_updateCH1Value(calcValue);
}
