/*
 * 7_segment.c
 *
 *  Created on: Sep 27, 2024
 *      Author: sinan
 */
#include "7_segment.h"
#include "main.h"
#include "clock_thread.h"

uint8_t segment_data[35][8] = {
//DP, G, F, E, D, C, B, A
		{ 1, 1, 0, 0, 0, 0, 0, 0 }, // 0
		{ 1, 1, 1, 1, 1, 0, 0, 1 }, // 1
		{ 1, 0, 1, 0, 0, 1, 0, 0 }, // 2
		{ 1, 0, 1, 1, 0, 0, 0, 0 }, // 3
		{ 1, 0, 0, 1, 1, 0, 0, 1 }, // 4
		{ 1, 0, 0, 1, 0, 0, 1, 0 }, // 5
		{ 1, 0, 0, 0, 0, 0, 1, 0 }, // 6
		{ 1, 1, 1, 1, 1, 0, 0, 0 }, // 7
		{ 1, 0, 0, 0, 0, 0, 0, 0 }, // 8
		{ 1, 0, 0, 1, 0, 0, 0, 0 }, // 9
		{ 1, 0, 0, 0, 1, 0, 0, 0 }, // A (10)
		{ 1, 0, 0, 0, 0, 0, 1, 1 }, // b (11)
		{ 1, 1, 0, 0, 0, 1, 1, 0 }, // C (12)
		{ 1, 0, 1, 0, 0, 0, 0, 1 }, // d (13)
		{ 1, 0, 0, 0, 0, 1, 1, 0 }, // E (14)
		{ 1, 0, 0, 0, 1, 1, 1, 0 }, // F (15)
		{ 1, 1, 0, 0, 0, 0, 1, 0 }, // G (16)
		{ 1, 0, 0, 0, 1, 0, 0, 1 }, // H (17)
		{ 1, 1, 0, 0, 1, 1, 1, 1 }, // I (18)
		{ 1, 1, 1, 1, 0, 0, 0, 1 }, // J (19)
		{ 1, 0, 0, 0, 1, 0, 1, 0 }, // K (20)
		{ 1, 1, 0, 0, 0, 1, 1, 1 }, // L (21)
		{ 1, 1, 0, 1, 0, 1, 0, 0 }, // M (22)
		{ 1, 0, 1, 0, 1, 0, 1, 1 }, // n (23)
		{ 1, 0, 1, 0, 0, 0, 1, 1 }, // o (24)
		{ 1, 0, 0, 0, 1, 1, 0, 0 }, // P (25)
		{ 1, 0, 0, 1, 1, 0, 0, 0 }, // q (26)
		{ 1, 0, 1, 0, 1, 1, 1, 1 }, // r (27)
		{ 1, 0, 0, 1, 0, 0, 1, 0 }, // S (28)
		{ 1, 0, 0, 0, 0, 1, 1, 1 }, // t (29)
		{ 1, 1, 0, 0, 0, 0, 0, 1 }, // U (30)
		{ 1, 0, 0, 1, 0, 0, 0, 1 }, // Y (31)
		{ 1, 0, 1, 0, 0, 1, 0, 0 }, // Z (32)
		{ 1, 1, 1, 1, 1, 1, 1, 1 }, // BLANK (33)
		{ 1, 0, 0, 1, 1, 1, 0, 0 } }; // DEG (34)

void segment_write(seven_segment *seg) {
	HAL_GPIO_WritePin(seg->enable_port, seg->enable_pin, seg->enable_segment);

	for (uint8_t i = 0; i < 8; i++) {
		HAL_GPIO_WritePin(seg->a_port, seg->a_pin, segment_data[seg->data][i]);
		HAL_GPIO_WritePin(seg->clock_port, seg->clock_pin, 0);
		HAL_GPIO_WritePin(seg->clock_port, seg->clock_pin, 1);
	}
	HAL_GPIO_WritePin(seg->enable_port, seg->enable_pin, seg->enable_segment);
}

void display_write(display *disp) {
	uint32_t data = disp->data;
	disp->second_one->data = data % 10;
	data /= 10;
	disp->second_ten->data = data % 10;
	data /= 10;
	disp->minute_one->data = data % 10;
	data /= 10;
	disp->minute_ten->data = data % 10;
	data /= 10;
	disp->hour_one->data = data % 10;
	data /= 10;
	disp->hour_ten->data = data % 10;

	segment_write(disp->hour_ten);
	segment_write(disp->hour_one);
	segment_write(disp->minute_ten);
	segment_write(disp->minute_one);
	segment_write(disp->second_ten);
	segment_write(disp->second_one);
}

void segment_on_off(seven_segment *seg, uint8_t on_off){
	HAL_GPIO_WritePin(seg->enable_port, seg->enable_pin, on_off);
	seg->enable_segment = on_off;
}
