/*
 * button.c
 *
 *  Created on: Jan 9, 2025
 *      Author: sinan
 */

#include "main.h"
#include "button.h"

uint8_t read_buttons(uint8_t *button_value) {
	uint8_t temp_value = 0;
	*button_value = 0;

	temp_value = HAL_GPIO_ReadPin(BTN_UP_GPIO_Port, BTN_UP_Pin);
	*button_value |= (temp_value << 3);

	temp_value = HAL_GPIO_ReadPin(BTN_DOWN_GPIO_Port, BTN_DOWN_Pin);
	*button_value |= (temp_value << 2);

	temp_value = HAL_GPIO_ReadPin(BTN_LEFT_GPIO_Port, BTN_LEFT_Pin);
	*button_value |= (temp_value << 1);

	temp_value = HAL_GPIO_ReadPin(BTN_RIGHT_GPIO_Port, BTN_RIGHT_Pin);
	*button_value |= (temp_value << 0);
	return 0;
}

void process_button(Button *btn) {
	uint8_t raw_state = HAL_GPIO_ReadPin(btn->port, btn->pin);
	uint32_t now = HAL_GetTick();

	switch (btn->state) {
	case BUTTON_IDLE:
		if (raw_state != btn->last_raw_state) {
			btn->last_change_time = now;
			btn->state = BUTTON_DEBOUNCING;
		}
		break;

	case BUTTON_DEBOUNCING:
		if ((now - btn->last_change_time) >= DEBOUNCE_TIME_MS) {
			if (raw_state != btn->last_raw_state) {
				btn->last_raw_state = raw_state;
				if (raw_state) {  // Button pressed
					btn->press_time = now;
					btn->state = BUTTON_PRESSED;
				} else {  // Released during debounce — go back to IDLE
					btn->state = BUTTON_IDLE;
				}
			} else {
				btn->state = BUTTON_IDLE;
			}
		}
		break;

	case BUTTON_PRESSED:
		if (!raw_state) {
			if ((now - btn->press_time) < LONG_PRESS_TIME_MS) {
				printf("Short Press Detected\n");
			}
			btn->state = BUTTON_RELEASED;
		} else if ((now - btn->press_time) >= LONG_PRESS_TIME_MS) {
			printf("Long Press Detected\n");
			btn->state = BUTTON_LONG_PRESS;
		}
		break;

	case BUTTON_LONG_PRESS:
		if (!raw_state) {
			btn->state = BUTTON_RELEASED;
		}
		break;

	case BUTTON_RELEASED:
		printf("Button Released\n");
		btn->state = BUTTON_IDLE;
		break;
	}
}

