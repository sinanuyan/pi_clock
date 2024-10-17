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
extern I2C_HandleTypeDef hi2c1;
extern uint8_t segment_data[34][8];

void clock_thread(void *pvParameters) {
	/* Just to remove compiler warning. */
	(void) pvParameters;

	const TickType_t delay_1000_ms = pdMS_TO_TICKS(1000UL);
	const TickType_t delay_100_ms = pdMS_TO_TICKS(100UL);

	uint8_t data[6] = {
			SEG_BLANK, SEG_BLANK, SEG_BLANK, SEG_BLANK, SEG_BLANK,SEG_BLANK
	};
	segment_write(data, 0);

	RTC_TimeTypeDef sTimeStamp;
	RTC_DateTypeDef sTimeStampDate;

	uint8_t bcd;
	uint8_t old_sec = 15;

	uint8_t sht_addr = 0x88;

	uint8_t sht_tx[2] = {0x20, 0x32};
	uint8_t sht_rx[6];
	HAL_StatusTypeDef result;

	result = HAL_I2C_Master_Transmit(&hi2c1, sht_addr, sht_tx, 2, 10);
	vTaskDelay(delay_100_ms);
	result = HAL_I2C_Master_Receive(&hi2c1, sht_addr, sht_rx, 3, 10);

	uint16_t st = 0;
	uint32_t temp_seg = 0;
	st = sht_rx[0] << 8;
	st = st | sht_rx[1];

	float temperature = -45+175*((float)st/65535);

	while(1){
		HAL_RTC_GetDate(&hrtc, &sTimeStampDate, RTC_FORMAT_BIN);
		HAL_RTC_GetTime(&hrtc, &sTimeStamp, RTC_FORMAT_BIN);

		result = HAL_I2C_Master_Receive(&hi2c1, sht_addr, sht_rx, 3, 10);
		st = sht_rx[0] << 8;
		st = st | sht_rx[1];

		temperature = -45+175*((float)st/65535);
		temp_seg = temperature*100;

		data[5] = SEG_C;
		data[4] = SEG_DEG;
		data[3] = temp_seg%10;
		temp_seg /= 10;
		data[2] = temp_seg%10;
		temp_seg /= 10;
		data[1] = temp_seg%10;
		temp_seg /= 10;
		data[0] = temp_seg%10;

		if(old_sec != data[3]){
			segment_write(data, MODE_TEMP);
			old_sec = data[3];
		}

		vTaskDelay(delay_1000_ms);
	}
}
