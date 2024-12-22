/*
 * clock_thread.h
 *
 *  Created on: Sep 27, 2024
 *      Author: sinan
 */

#ifndef SRC_CLOCK_THREAD_H_
#define SRC_CLOCK_THREAD_H_

#include	"FreeRTOS.h"
#include	"task.h"
#include	"queue.h"
#include	"main.h"

typedef struct{
	uint8_t data;
	uint8_t enable_segment;
	GPIO_TypeDef *clock_port;
	uint16_t clock_pin;
	GPIO_TypeDef *a_port;
	uint16_t a_pin;
	GPIO_TypeDef *enable_port;
	uint16_t enable_pin;
}seven_segment;

typedef struct{
	uint32_t data;
	seven_segment *hour_ten;
	seven_segment *hour_one;
	seven_segment *minute_ten;
	seven_segment *minute_one;
	seven_segment *second_ten;
	seven_segment *second_one;
}display;

extern xTaskHandle clock_thread_handle;
extern QueueHandle_t button_queue;

void clock_thread( void *pvParameters );


#endif /* SRC_CLOCK_THREAD_H_ */
