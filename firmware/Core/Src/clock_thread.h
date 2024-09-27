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

extern xTaskHandle clock_thread_handle;
extern QueueHandle_t button_queue;

void clock_thread( void *pvParameters );

#endif /* SRC_CLOCK_THREAD_H_ */
