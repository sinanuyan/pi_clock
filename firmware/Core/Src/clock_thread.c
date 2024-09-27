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

void clock_thread(void *pvParameters) {
	/* Just to remove compiler warning. */
	(void) pvParameters;

	const TickType_t delay_100_ms = pdMS_TO_TICKS(100UL);

	uint8_t data[6] = {
			0, 0, 0, 0, 0,0
	};
	segment_write(data);

	RTC_TimeTypeDef sTimeStamp;
	RTC_DateTypeDef sTimeStampDate;

	uint8_t bcd;
	uint8_t old_sec = 15;

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
		vTaskDelay(delay_100_ms);
	}
}

