/*
 * 7_segment.h
 *
 *  Created on: Sep 27, 2024
 *      Author: sinan
 */

#ifndef INC_7_SEGMENT_H_
#define INC_7_SEGMENT_H_

#include <stdint.h>

#define SEG_A 10 //{ 1, 0, 0, 0, 1, 0, 0, 0 }, // A (10)
#define SEG_b 11 //{ 1, 0, 0, 0, 0, 0, 1, 1 }, // b (11)
#define SEG_C 12 //{ 1, 1, 0, 0, 0, 1, 1, 0 }, // C (12)
#define SEG_d 13 //{ 1, 0, 1, 0, 0, 0, 0, 1 }, // d (13)
#define SEG_E 14 //{ 1, 0, 0, 0, 0, 1, 1, 0 }, // E (14)
#define SEG_F 15 //{ 1, 0, 0, 0, 1, 1, 1, 0 }, // F (15)
#define SEG_G 16 //{ 1, 1, 0, 0, 0, 0, 1, 0 }, // G (16)
#define SEG_H 17 //{ 1, 0, 0, 0, 1, 0, 0, 1 }, // H (17)
#define SEG_I 18 //{ 1, 1, 0, 0, 1, 1, 1, 1 }, // I (18)
#define SEG_J 19 //{ 1, 1, 1, 1, 0, 0, 0, 1 }, // J (19)
#define SEG_K 20 //{ 1, 0, 0, 0, 1, 0, 1, 0 }, // K (20)
#define SEG_L 21 //{ 1, 1, 0, 0, 0, 1, 1, 1 }, // L (21)
#define SEG_M 22 //{ 1, 1, 0, 1, 0, 1, 0, 0 }, // M (22)
#define SEG_n 23 //{ 1, 0, 1, 0, 1, 0, 1, 1 }, // n (23)
#define SEG_o 24 //{ 1, 0, 1, 0, 0, 0, 1, 1 }, // o (24)
#define SEG_P 25 //{ 1, 0, 0, 0, 1, 1, 0, 0 }, // P (25)
#define SEG_q 26 //{ 1, 0, 0, 1, 1, 0, 0, 0 }, // q (26)
#define SEG_r 27 //{ 1, 0, 1, 0, 1, 1, 1, 1 }, // r (27)
#define SEG_S 28 //{ 1, 0, 0, 1, 0, 0, 1, 0 }, // S (28)
#define SEG_t 29 //{ 1, 0, 0, 0, 0, 1, 1, 1 }, // t (29)
#define SEG_U 30 //{ 1, 1, 0, 0, 0, 0, 0, 1 }, // U (30)
#define SEG_Y 31 //{ 1, 0, 0, 1, 0, 0, 0, 1 }, // Y (31)
#define SEG_Z 32 //{ 1, 0, 1, 0, 0, 1, 0, 0 }};// Z (32)
#define SEG_BLANK 33 //{ 1, 1, 1, 1, 1, 1, 1, 1 }};// BLANK (33)
#define SEG_DEG 34	// { 1, 0, 0, 1, 1, 1, 0, 0 }};// DEG (34)


#define MODE_TEMP 1

void segment_write(uint8_t *data, uint8_t mode);

#endif /* INC_7_SEGMENT_H_ */
