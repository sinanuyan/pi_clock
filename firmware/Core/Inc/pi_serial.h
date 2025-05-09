/*
 * pi.h
 *
 *  Created on: May 9, 2025
 *      Author: sinan
 */

#ifndef INC_PI_H_
#define INC_PI_H_

#include "main.h"
#include <stdio.h>

typedef struct {
    int hours;
	int minutes;
	int seconds;
	int years;
	int months;
	int days;
} PiTime;

void send_uart_command(const char* cmd);
void receive_uart_response(char* buffer, uint16_t size);
void parse_time_string(const char* time_str, PiTime *pi_times);
void parse_date_string(const char* date_str,PiTime *pi_times);

#endif /* INC_PI_H_ */
