/*
 * gpio.c
 *
 *  Created on: 11 oct. 2023
 *      Author: gabyd
 */


#include "gpio.h"

volatile static gpio_interrupt_flags_t g_intr_status_flag = {0};

static void (*gpio_A_callback)(void) = 0;
static void (*gpio_B_callback)(void) = 0;
static void (*gpio_C_callback)(void) = 0;
static void (*gpio_D_callback)(void) = 0;
static void (*gpio_E_callback)(void) = 0;

uint8_t irq_AFLAG = FALSE;

void GPIO_callback_init(gpio_name_t gpio, void (*handler)(void))
{
	switch(gpio)
	{
		case GPIO_A:
			gpio_A_callback = handler;
			break;
		case GPIO_B:
			gpio_B_callback = handler;
			break;
		case GPIO_C:
			gpio_C_callback = handler;
			break;
		case GPIO_D:
			gpio_D_callback = handler;
			break;
		default:
			gpio_E_callback = handler;
			break;
	}
}




void GPIO_init(void)
{
	gpio_pin_config_t gpio_input_config = {
			        kGPIO_DigitalInput,
			        0,
			    };

	gpio_pin_config_t gpio_output_config = {
			        kGPIO_DigitalOutput,
			        1,
			    };

	const port_pin_config_t button_config = {
			kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
			kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
			kPORT_PassiveFilterEnable,                              /* Passive filter is disabled */
			kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
			kPORT_HighDriveStrength,                                 /* High drive strength is configured */
			kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
			kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
		  };

	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortD);
	CLOCK_EnableClock(kCLOCK_PortC);

	//Botones de Direccionales
	GPIO_PinInit(GPIOD, RIGHT, &gpio_input_config);
	PORT_SetPinConfig(PORTD, RIGHT, &button_config);
	PORT_SetPinInterruptConfig(PORTD, RIGHT, kPORT_InterruptFallingEdge);

	GPIO_PinInit(GPIOD, LEFT, &gpio_input_config);
	PORT_SetPinConfig(PORTD, LEFT, &button_config);
	PORT_SetPinInterruptConfig(PORTD, LEFT, kPORT_InterruptFallingEdge);
	//Boton para Intermitentes
	GPIO_PinInit(GPIOD, BLINK, &gpio_input_config);
	PORT_SetPinConfig(PORTD, BLINK, &button_config);
	PORT_SetPinInterruptConfig(PORTD, BLINK, kPORT_InterruptFallingEdge);

	//LED izquirdo
	PORT_SetPinMux(PORTC, LED_R, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOC, LED_R, &gpio_output_config);
	//LED derecho
	PORT_SetPinMux(PORTC, LED_L, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOC, LED_L, &gpio_output_config);

}

/* Change frequency */
void PORTA_IRQHandler(void)
{
	if(gpio_A_callback)
	{
		gpio_A_callback();
	}

	irq_AFLAG = 1;
	GPIO_PortClearInterruptFlags(GPIOA, 0xFFFF);
}

/* Change signal */
void PORTC_IRQHandler(void)
{
	if(gpio_C_callback)
	{
		gpio_C_callback();
	}

	GPIO_PortClearInterruptFlags(GPIOC, 0xFFFF);
}

void PORTB_IRQHandler(void)
{
	if(gpio_B_callback)
	{
		gpio_B_callback();
	}

	GPIO_PortClearInterruptFlags(GPIOB, 0xFFFF);
}

void PORTD_IRQHandler(void)
{
	if(gpio_D_callback)
	{
		gpio_D_callback();
	}

	GPIO_PortClearInterruptFlags(GPIOD, 0xFFFF);
}

void PORTE_IRQHandler(void)
{
	if(gpio_E_callback)
	{
		gpio_E_callback();
	}

	GPIO_PortClearInterruptFlags(GPIOE, 0xFFFF);
}

uint8_t return_portA_irq_status(void)
{
	return irq_AFLAG;
}

void clear_AFLAG(void)
{
	irq_AFLAG = FALSE;
}
