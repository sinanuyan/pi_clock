/*
 * button_thread.c
 *
 *  Created on: Sep 27, 2024
 *      Author: sinan
 */
#include "button_thread.h"
#include "main.h"



void button_thread(void *pvParameters) {
	/* Just to remove compiler warning. */
	(void) pvParameters;

	uint8_t button_value;

	while(1){
		if(HAL_GPIO_ReadPin(BTN_UP_GPIO_Port, BTN_UP_Pin)){
			button_value = BUTTON_UP;
		}
		if(HAL_GPIO_ReadPin(BTN_DOWN_GPIO_Port, BTN_DOWN_Pin)){
			button_value = BUTTON_DOWN;
		}
		if(HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port, BTN_LEFT_Pin)){
			button_value = BUTTON_LEFT;
		}
		if(HAL_GPIO_ReadPin(BTN_RIGHT_GPIO_Port, BTN_RIGHT_Pin)){
			button_value = BUTTON_RIGHT;
		}
	}
}
