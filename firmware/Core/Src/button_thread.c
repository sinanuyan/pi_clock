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

	const TickType_t delay_100_ms = pdMS_TO_TICKS(100UL);

	uint8_t button_value;

	while(1){
		if(HAL_GPIO_ReadPin(BTN_UP_GPIO_Port, BTN_UP_Pin)){
			button_value = BUTTON_UP;
			xQueueSend(button_queue, (void *) &button_value, (TickType_t) 10);
		}
		if(HAL_GPIO_ReadPin(BTN_DOWN_GPIO_Port, BTN_DOWN_Pin)){
			button_value = BUTTON_DOWN;
			xQueueSend(button_queue, (void *) &button_value, (TickType_t) 10);
		}
		if(HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port, BTN_LEFT_Pin)){
			button_value = BUTTON_LEFT;
			xQueueSend(button_queue, (void *) &button_value, (TickType_t) 10);
		}
		if(HAL_GPIO_ReadPin(BTN_RIGHT_GPIO_Port, BTN_RIGHT_Pin)){
			button_value = BUTTON_RIGHT;
			xQueueSend(button_queue, (void *) &button_value, (TickType_t) 10);
		}
		vTaskDelay(delay_100_ms);
	}
}
