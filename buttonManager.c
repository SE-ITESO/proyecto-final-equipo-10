/*
 * buttonManager.c
 *
 *  Created on: 29 nov. 2023
 *      Author: gabyd
 */

#include "buttonManager.h"

void choose_button_pressed(uint32_t port){
	if(get_reverse_pressed_flag()){
		//Cambia modo

		set_reverse_pressed_flag(FALSE);
	}

	if(get_blink_pressed_flag()){
		GPIO_PortToggle(GPIOD, 1 << BLINK);
		set_blink_pressed_flag(FALSE);
	}

	if(get_right_pressed_flag()){
		GPIO_PortToggle(GPIOD, 1 << RIGHT);
		set_right_pressed_flag(FALSE);
	}

	if(get_left_pressed_flag()){
		GPIO_PortToggle(GPIOD, 1 << LEFT);
		set_left_pressed_flag(FALSE);
	}
}
