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
extern UART_HandleTypeDef huart2;

void clock_thread(void *pvParameters) {
	/* Just to remove compiler warning. */
	(void) pvParameters;

	const TickType_t delay_1000_ms = pdMS_TO_TICKS(1000UL);
	const TickType_t delay_200_ms = pdMS_TO_TICKS(200UL);
	const TickType_t delay_100_ms = pdMS_TO_TICKS(100UL);
	const TickType_t delay_10_ms = pdMS_TO_TICKS(10UL);

	uint8_t data[6] = {
	SEG_BLANK, SEG_BLANK, SEG_BLANK, SEG_BLANK, SEG_BLANK, SEG_BLANK };
	//segment_write(data, 0);

	RTC_TimeTypeDef sTimeStamp;
	RTC_DateTypeDef sTimeStampDate;

	uint8_t bcd;
	uint8_t old_sec = 15;

	uint8_t sht_addr = 0x88;

	uint8_t sht_tx[2] = { 0x20, 0x32 };
	uint8_t sht_rx[6];
	HAL_StatusTypeDef result;

	result = HAL_I2C_Master_Transmit(&hi2c1, sht_addr, sht_tx, 2, 10);
	vTaskDelay(delay_100_ms);
	result = HAL_I2C_Master_Receive(&hi2c1, sht_addr, sht_rx, 3, 10);

	uint8_t tx_data[100];

	uint16_t st = 0;
	uint32_t temp_seg = 0;
	st = sht_rx[0] << 8;
	st = st | sht_rx[1];

	float temperature = -45 + 175 * ((float) st / 65535);
	uint8_t hour_ten_value = 0;
	uint8_t hour_one_value = 0;
	uint8_t minute_ten_value = 0;
	uint8_t minute_one_value = 0;
	uint8_t second_ten_value = 0;
	uint8_t second_one_value = 0;

	data[0] = SEG_A;
	data[1] = SEG_A;
	data[2] = SEG_A;
	data[3] = SEG_A;
	data[4] = SEG_A;
	data[5] = SEG_A;

	seven_segment hour_ten;
	seven_segment hour_one;
	seven_segment minute_ten;
	seven_segment minute_one;
	seven_segment second_ten;
	seven_segment second_one;

	display disp;

	hour_ten.a_port = A_HT_GPIO_Port;
	hour_ten.a_pin = A_HT_Pin;
	hour_ten.clock_port = CLK_A_HT_GPIO_Port;
	hour_ten.clock_pin = CLK_A_HT_Pin;
	hour_ten.enable_port = EN_HT_GPIO_Port;
	hour_ten.enable_pin = EN_HT_Pin;
	hour_ten.enable_segment = 1;

	hour_one.a_port = A_HO_GPIO_Port;
	hour_one.a_pin = A_HO_Pin;
	hour_one.clock_port = CLK_A_HO_GPIO_Port;
	hour_one.clock_pin = CLK_A_HO_Pin;
	hour_one.enable_port = EN_HO_GPIO_Port;
	hour_one.enable_pin = EN_HO_Pin;
	hour_one.enable_segment = 1;

	minute_ten.a_port = A_MT_GPIO_Port;
	minute_ten.a_pin = A_MT_Pin;
	minute_ten.clock_port = CLK_A_MT_GPIO_Port;
	minute_ten.clock_pin = CLK_A_MT_Pin;
	minute_ten.enable_port = EN_MT_GPIO_Port;
	minute_ten.enable_pin = EN_MT_Pin;
	minute_ten.enable_segment = 1;

	minute_one.a_port = A_MO_GPIO_Port;
	minute_one.a_pin = A_MO_Pin;
	minute_one.clock_port = CLK_A_MO_GPIO_Port;
	minute_one.clock_pin = CLK_A_MO_Pin;
	minute_one.enable_port = EN_MO_GPIO_Port;
	minute_one.enable_pin = EN_MO_Pin;
	minute_one.enable_segment = 1;

	second_ten.a_port = A_ST_GPIO_Port;
	second_ten.a_pin = A_ST_Pin;
	second_ten.clock_port = CLK_A_ST_GPIO_Port;
	second_ten.clock_pin = CLK_A_ST_Pin;
	second_ten.enable_port = EN_ST_GPIO_Port;
	second_ten.enable_pin = EN_ST_Pin;
	second_ten.enable_segment = 1;

	second_one.a_port = A_SO_GPIO_Port;
	second_one.a_pin = A_SO_Pin;
	second_one.clock_port = CLK_A_SO_GPIO_Port;
	second_one.clock_pin = CLK_A_SO_Pin;
	second_one.enable_port = EN_SO_GPIO_Port;
	second_one.enable_pin = EN_SO_Pin;
	second_one.enable_segment = 1;

	hour_ten.data = 0;
	hour_one.data = 0;
	minute_ten.data = 0;
	minute_one.data = 0;
	second_ten.data = 0;
	second_one.data = 0;

	disp.hour_ten = &hour_ten;
	disp.hour_one = &hour_one;
	disp.minute_ten = &minute_ten;
	disp.minute_one = &minute_one;
	disp.second_ten = &second_ten;
	disp.second_one = &second_one;

	disp.data = 990000;
	display_write(&disp);

	while (1) {
		disp.data++;
		display_write(&disp);
		vTaskDelay(delay_10_ms);
	}
}
