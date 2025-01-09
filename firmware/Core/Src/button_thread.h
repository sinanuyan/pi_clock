/*
 * button_thread.h
 *
 *  Created on: Sep 27, 2024
 *      Author: sinan
 */

#ifndef SRC_BUTTON_THREAD_H_
#define SRC_BUTTON_THREAD_H_

typedef enum{
	BUTTON_UP = 1,
	BUTTON_DOWN = 2,
	BUTTON_LEFT = 3,
	BUTTON_RIGHT = 4
}BUTTON_VALUE;


void button_thread(void *pvParameters);

#endif /* SRC_BUTTON_THREAD_H_ */
