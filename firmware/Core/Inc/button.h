/*
 * button.h
 *
 *  Created on: Jan 9, 2025
 *      Author: sinan
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#define BTN_UP_MASK 	0x08
#define BTN_DOWN_MASK	0x04
#define BTN_LEFT_MASK	0x02
#define BTN_RIGHT_MASK	0x01

#define DEBOUNCE_TIME_MS     30
#define LONG_PRESS_TIME_MS   1000
#define POLL_INTERVAL_MS     10

typedef enum {
    BUTTON_IDLE,
    BUTTON_DEBOUNCING,
    BUTTON_PRESSED,
    BUTTON_LONG_PRESS,
    BUTTON_RELEASED
} ButtonState;

typedef struct {
    ButtonState state;
    ButtonState state_old;
    uint32_t last_change_time;
    uint32_t press_time;
    uint8_t last_raw_state;
    GPIO_TypeDef *port;
    uint16_t pin;
} Button;

void process_button(Button* btn);




uint8_t read_buttons(uint8_t *button_value);




#endif /* INC_BUTTON_H_ */
