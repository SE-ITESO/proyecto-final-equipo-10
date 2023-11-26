/*
 * gpio.h
 *
 *  Created on: 11 oct. 2023
 *      Author: gabyd
 */

#ifndef GPIO_H_
#define GPIO_H_


#include "stdint.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include <stdbool.h>
#include "MK64F12.h"


#define RIGHT    0u
#define LEFT     2u
#define BLINK   3u
#define LED_R   17u
#define LED_L   16u

typedef enum
{
	FALSE,
	TRUE
} bool_t;

/*! These constants are used to select an specific port in the different API functions*/
typedef enum{GPIO_A, /*!< Definition to select GPIO A */
			 GPIO_B, /*!< Definition to select GPIO B */
			 GPIO_C, /*!< Definition to select GPIO C */
			 GPIO_D, /*!< Definition to select GPIO D */
			 GPIO_E, /*!< Definition to select GPIO E */
			 GPIO_F  /*!< Definition to select GPIO F */
			} gpio_name_t;

typedef struct
{
	uint8_t flag_port_a : 1;
	uint8_t flag_port_b : 1;
	uint8_t flag_port_c : 1;
	uint8_t flag_port_d : 1;
	uint8_t flag_port_e : 1;
} gpio_interrupt_flags_t;


void GPIO_callback_init(gpio_name_t gpio, void (*handler)(void));

void GPIO_clear_irq_status(gpio_name_t gpio);

uint8_t GPIO_get_irq_status(gpio_name_t gpio);

void GPIO_init(void);

void init_RGB();

uint8_t return_portA_irq_status(void);

void clear_AFLAG(void);


#endif /* GPIO_H_ */
