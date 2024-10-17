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
		{ 1, 0, 0, 1, 1, 1, 0, 0 }}; // DEG (34)

void segment_write(uint8_t *data, uint8_t mode) {

	for (uint8_t i = 0; i < 8; i++) {
		HAL_GPIO_WritePin(A_HT_GPIO_Port, A_HT_Pin, segment_data[data[0]][i]);
		if((mode == 1) && (i== 0)){
			HAL_GPIO_WritePin(A_HO_GPIO_Port, A_HO_Pin, 0);
		}else{
			HAL_GPIO_WritePin(A_HO_GPIO_Port, A_HO_Pin, segment_data[data[1]][i]);
		}


		HAL_GPIO_WritePin(A_MT_GPIO_Port, A_MT_Pin, segment_data[data[2]][i]);
		HAL_GPIO_WritePin(A_MO_GPIO_Port, A_MO_Pin, segment_data[data[3]][i]);

		HAL_GPIO_WritePin(A_ST_GPIO_Port, A_ST_Pin, segment_data[data[4]][i]);
		HAL_GPIO_WritePin(A_SO_GPIO_Port, A_SO_Pin, segment_data[data[5]][i]);

		HAL_GPIO_WritePin(CLOCK_GPIO_Port, CLOCK_Pin, 0);
		HAL_GPIO_WritePin(CLOCK_GPIO_Port, CLOCK_Pin, 1);
	}
}
