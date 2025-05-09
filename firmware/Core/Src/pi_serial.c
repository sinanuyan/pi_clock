/*
 * pi.c
 *
 *  Created on: May 9, 2025
 *      Author: sinan
 */

#include <pi_serial.h>
#include <string.h>

extern UART_HandleTypeDef huart2;


void send_uart_command(const char* cmd) {
    HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), HAL_MAX_DELAY);
    HAL_UART_Transmit(&huart2, (uint8_t*)"\n", 1, HAL_MAX_DELAY); // newline terminator
}

void receive_uart_response(char* buffer, uint16_t size) {
    uint8_t ch;
    uint16_t idx = 0;

    while (idx < size - 1) {
        if (HAL_UART_Receive(&huart2, &ch, 1, HAL_MAX_DELAY) == HAL_OK) {
            if (ch == '\n') break;
            buffer[idx++] = ch;
        }
    }
    buffer[idx] = '\0'; // Null-terminate
}

void parse_time_string(const char* time_str, PiTime *pi_times) {
    // Expects format: "HH:MM:SS"
    sscanf(time_str, "%d:%d:%d", &pi_times->hours, &pi_times->minutes, &pi_times->seconds);
}

void parse_date_string(const char* date_str,PiTime *pi_times) {
    // Expects format: "YYYY-MM-DD"
    sscanf(date_str, "%d-%d-%d", &pi_times->years, &pi_times->months, &pi_times->seconds);
}
