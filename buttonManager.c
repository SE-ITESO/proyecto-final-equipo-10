/*
 * buttonManager.c
 *
 *  Created on: 29 nov. 2023
 *      Author: gabyd
 */

#include "buttonManager.h"

LED_state_t g_states = both_off_s;

motors_dir_t g_motor = forward_s;
//
//void leds_machine(void)
//{
//
//	switch(g_states)
//	{
//	case(both_off_s):
//		if(TRUE == !GPIO_PinRead(GPIOC, BLINK))
//		{
//			LED_Blink_on();
//			if(TRUE == !GPIO_PinRead(GPIOC, BLINK))
//				g_states = both_on_s;
//		}
//		if(TRUE == !GPIO_PinRead(GPIOC, RIGHT))
//		{
//			LED_R_on();
//			g_states = right_on_s;
//		}
//		if(TRUE == !GPIO_PinRead(GPIOC, LEFT))
//		{
//			LED_L_on();
//			g_states = left_on_s;
//		}
//	break;
//	case(both_on_s):
//		if (TRUE == !GPIO_PinRead(GPIOC, BLINK)) {
//			LED_off();
//			g_states = both_off_s;
//		}
//
//		if (TRUE == !GPIO_PinRead(GPIOC, RIGHT)) {
//			LED_off();
//			g_states = right_off_s;
//		}
//
//		if (TRUE == !GPIO_PinRead(GPIOC, LEFT)) {
//			LED_off();
//			g_states = left_off_s;
//		}
//
//	break;
//	}
//}



void choose_button_pressed(uint32_t port){
//	if(get_reverse_pressed_flag()){
//		//Cambia modo
//		uint32_t adcValueMotorB = ADC_Read_Motor();
//		AdcToPwmMotorBwd(adcValueMotorB);
//		set_reverse_pressed_flag(FALSE);
//	}
//	else{
//		uint32_t adcValueMotorF = ADC_Read_Motor();
//		AdcToPwmMotorBwd(adcValueMotorF);
//		set_reverse_pressed_flag(FALSE);
//	}

	if(get_blink_pressed_flag()){
		LED_Blink_on();
		set_blink_pressed_flag(FALSE);
	}

	if(get_right_pressed_flag()){
		LED_R_on();
		set_right_pressed_flag(FALSE);
	}

	if(get_left_pressed_flag()){
		LED_L_on();
		set_left_pressed_flag(FALSE);
	}
}

void LED_R_on(void)
{
		GPIO_PortToggle(GPIOC, 1<<LED_R);

		for (volatile int i = 0; i < 1000000; ++i) {}  // Retardo
}

void LED_L_on(void)
{

		GPIO_PortToggle(GPIOC, 1<<LED_L);

		for (volatile int i = 0; i < 1000000; ++i) {}  // Retardo

}

void LED_on(void)
{
	LED_off();
	GPIO_PortClear(GPIOC, 1 << LED_R);
	GPIO_PortClear(GPIOC, 1 << LED_L);

}

void LED_off(void)
{
	LED_off();
	GPIO_PortSet(GPIOC, 1 << LED_R);
	GPIO_PortSet(GPIOC, 1 << LED_L);
}

void LED_Blink_on(void)
{
	GPIO_PortToggle(GPIOC, 1<<LED_L);
	GPIO_PortToggle(GPIOC, 1<<LED_R);
	for (volatile int i = 0; i < 1000000; ++i) {}  // Retardo

}


