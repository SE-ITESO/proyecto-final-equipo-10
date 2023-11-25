/*
 * MotorShield.c
 *
 *  Created on: Nov 20, 2023
 *      Author: jorgeleautaud
 */


#include "fsl_gpio.h"
#include "fsl_ftm.h"
#include "fsl_port.h"

// Define motor control pins
#define MOTOR_A_IN1_PIN 2U  // Replace with the actual pin number connected to L298N IN1
#define MOTOR_A_IN2_PIN 3U  // Replace with the actual pin number connected to L298N IN2
#define MOTOR_B_IN1_PIN 10U  // Replace with the actual pin number connected to L298N IN3
#define MOTOR_B_IN2_PIN 11U  // Replace with the actual pin number connected to L298N IN4

// Define FTM module and channel
#define FTM_MODULE FTM0
#define FTM_CHANNEL kFTM_Chnl_0


/* Get source clock for FTM driver */
#define FTM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

void initMotorControlPins(void) {
    gpio_pin_config_t motorConfig = {
        kGPIO_DigitalOutput, 0,
    };
	const port_pin_config_t gpio_config = {
			kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
			kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
			kPORT_PassiveFilterEnable,                              /* Passive filter is disabled */
			kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
			kPORT_HighDriveStrength,                                 /* High drive strength is configured */
			kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
			kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
		  };

    CLOCK_EnableClock(kCLOCK_PortB);
    CLOCK_EnableClock(kCLOCK_PortC);

    // Assign PTC3 to FTM0_CH0
   PORT_SetPinMux(PORTC, 3U, kPORT_MuxAlt4);


    // Initialize motor control pins as digital outputs
    GPIO_PinInit(GPIOB, MOTOR_A_IN1_PIN, &motorConfig);
    PORT_SetPinConfig(PORTB, MOTOR_A_IN1_PIN, &gpio_config);

    GPIO_PinInit(GPIOB, MOTOR_A_IN2_PIN, &motorConfig);
    PORT_SetPinConfig(PORTB, MOTOR_A_IN2_PIN, &gpio_config);

    GPIO_PinInit(GPIOB, MOTOR_B_IN1_PIN, &motorConfig);
    PORT_SetPinConfig(PORTB, MOTOR_B_IN1_PIN, &gpio_config);

    GPIO_PinInit(GPIOB, MOTOR_B_IN2_PIN, &motorConfig);
    PORT_SetPinConfig(PORTB, MOTOR_B_IN2_PIN, &gpio_config);

}

void initFTM(void) {
    ftm_config_t ftmInfo;
    ftm_chnl_pwm_signal_param_t ftmParam;

    // Initialize FTM module
    FTM_GetDefaultConfig(&ftmInfo);
    FTM_Init(FTM_MODULE, &ftmInfo);


    // Configure FTM channel for PWM
    ftmParam.chnlNumber = FTM_CHANNEL;
    ftmParam.level = kFTM_HighTrue;
    ftmParam.dutyCyclePercent = 0U; // Initial duty cycle (0-100)
    ftmParam.firstEdgeDelayPercent = 0U;

    FTM_SetupPwm(FTM_MODULE, &ftmParam, 1U, kFTM_EdgeAlignedPwm, 10000U, FTM_SOURCE_CLOCK);





	// Start the FTM timer
	  FTM_StartTimer(FTM_MODULE, kFTM_SystemClock);

}

void setMotorSpeed(uint8_t percent) {
    // Set the duty cycle to control motor speed
    FTM_UpdatePwmDutycycle(FTM_MODULE, FTM_CHANNEL, kFTM_EdgeAlignedPwm, percent);
}

void moveForward(uint8_t percent) {


	FTM_UpdatePwmDutycycle(FTM_MODULE, FTM_CHANNEL, kFTM_EdgeAlignedPwm, percent);
    // Motor A
     GPIO_PinWrite(GPIOB, MOTOR_A_IN1_PIN, 1);
     GPIO_PinWrite(GPIOB, MOTOR_A_IN2_PIN, 0);

    // Motor B
    GPIO_PinWrite(GPIOB, MOTOR_B_IN1_PIN, 1);
    GPIO_PinWrite(GPIOB, MOTOR_B_IN2_PIN, 0);
}

void moveBackward(uint8_t percent) {

	FTM_UpdatePwmDutycycle(FTM_MODULE, FTM_CHANNEL, kFTM_EdgeAlignedPwm, percent);

    // Motor A
    GPIO_PinWrite(GPIOB, MOTOR_A_IN1_PIN, 0);
    GPIO_PinWrite(GPIOB, MOTOR_A_IN2_PIN, 1);

    // Motor B
    GPIO_PinWrite(GPIOB, MOTOR_B_IN1_PIN, 0);
    GPIO_PinWrite(GPIOB, MOTOR_B_IN2_PIN, 1);
}



void stopMotors(void) {

    // Motor A
    GPIO_PinWrite(GPIOB, MOTOR_A_IN1_PIN, 0);
    GPIO_PinWrite(GPIOB, MOTOR_A_IN2_PIN, 0);

    // Motor B
    GPIO_PinWrite(GPIOB, MOTOR_B_IN1_PIN, 0);
    GPIO_PinWrite(GPIOB, MOTOR_B_IN2_PIN, 0);

}
