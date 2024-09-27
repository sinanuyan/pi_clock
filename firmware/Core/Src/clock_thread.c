/*
 * clock_thread.c
 *
 *  Created on: Sep 27, 2024
 *      Author: sinan
 */
#include "clock_thread.h"
#include "7_segment.h"
#include "main.h"

extern RTC_HandleTypeDef hrtc;
extern TIM_HandleTypeDef htim2;
extern uint8_t segment_data[34][8];

void clock_thread(void *pvParameters) {
	/* Just to remove compiler warning. */
	(void) pvParameters;

	const TickType_t delay_10_ms = pdMS_TO_TICKS(10UL);

	uint8_t data[6] = {
			SEG_BLANK, SEG_BLANK, SEG_BLANK, SEG_BLANK, SEG_BLANK,SEG_BLANK
	};
	segment_write(data);

	RTC_TimeTypeDef sTimeStamp;
	RTC_DateTypeDef sTimeStampDate;

	uint8_t bcd;
	uint8_t old_sec = 15;
	uint8_t button_press = 0;

	while(1){
		HAL_RTC_GetDate(&hrtc, &sTimeStampDate, RTC_FORMAT_BIN);
		HAL_RTC_GetTime(&hrtc, &sTimeStamp, RTC_FORMAT_BIN);

		bcd = sTimeStamp.Seconds;
		data[5] = bcd%10;
		data[4] = bcd/10;

		bcd = sTimeStamp.Minutes;
		data[3] = bcd%10;
		data[2] = bcd/10;

		bcd = sTimeStamp.Hours;
		data[1] = bcd%10;
		data[0] = bcd/10;

		if(old_sec != data[5]){
			segment_write(data);
			old_sec = data[5];
		}

		xQueueReceive(button_queue, &button_press, ( TickType_t ) 10);
		if(button_press){
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
			vTaskDelay(delay_10_ms);
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
			button_press = 0;
		}
		vTaskDelay(delay_10_ms);

	}
}

