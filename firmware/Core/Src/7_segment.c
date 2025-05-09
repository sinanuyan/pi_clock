/*
 * 7_segment.c
 *
 *  Created on: Sep 27, 2024
 *      Author: sinan
 */
#include "7_segment.h"
#include "main.h"

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

void segment_write(seven_segment *seg, uint8_t dot) {
	HAL_GPIO_WritePin(seg->enable_port, seg->enable_pin, 0);

	for (uint8_t i = 0; i < 8; i++) {
		if((i == 0) && (dot == 1)){
			HAL_GPIO_WritePin(seg->a_port, seg->a_pin, 0);
		}else{
			HAL_GPIO_WritePin(seg->a_port, seg->a_pin, segment_data[seg->data][i]);
		}

		HAL_GPIO_WritePin(seg->clock_port, seg->clock_pin, 0);
		HAL_GPIO_WritePin(seg->clock_port, seg->clock_pin, 1);
	}
	HAL_GPIO_WritePin(seg->enable_port, seg->enable_pin, seg->enable_segment);
}

//void display_write_number(display *disp) {
//	uint32_t data = disp->data;
//	disp->second_one->data = data % 10;
//	data /= 10;
//	disp->second_ten->data = data % 10;
//	data /= 10;
//	disp->minute_one->data = data % 10;
//	data /= 10;
//	disp->minute_ten->data = data % 10;
//	data /= 10;
//	disp->hour_one->data = data % 10;
//	data /= 10;
//	disp->hour_ten->data = data % 10;
//
//	if (disp->hour_ten->data != disp->hour_ten->data_old) {
//		segment_write(disp->hour_ten);
//		disp->hour_ten->data_old = disp->hour_ten->data;
//	}
//
//	if (disp->hour_one->data != disp->hour_one->data_old) {
//		segment_write(disp->hour_one);
//		disp->hour_one->data_old = disp->hour_one->data;
//	}
//
//	if (disp->minute_ten->data != disp->minute_ten->data_old) {
//		segment_write(disp->minute_ten);
//		disp->minute_ten->data_old = disp->minute_ten->data;
//	}
//
//	if (disp->minute_one->data != disp->minute_one->data_old) {
//		segment_write(disp->minute_one);
//		disp->minute_one->data_old = disp->minute_one->data;
//	}
//
//	if (disp->second_ten->data != disp->second_ten->data_old) {
//		segment_write(disp->second_ten);
//		disp->second_ten->data_old = disp->second_ten->data;
//	}
//
//	if (disp->second_one->data != disp->second_one->data_old) {
//		segment_write(disp->second_one);
//		disp->second_one->data_old = disp->second_one->data;
//	}
//}

void display_write_segment(display_segment *disp_segment, uint8_t dot) {
	uint8_t data = disp_segment->data;
	if (data != disp_segment->data_old) {
		disp_segment->data_old = disp_segment->data;

		disp_segment->one->data = data % 10;
		data /= 10;
		disp_segment->ten->data = data;

		segment_write(disp_segment->one, dot);
		segment_write(disp_segment->ten, 0);
	}
}

void segment_on_off(seven_segment *seg, uint8_t on_off) {
	HAL_GPIO_WritePin(seg->enable_port, seg->enable_pin, on_off);
	seg->enable_segment = on_off;
}
