#include "motor.h"
#include "mymilli.h"
#include <Arduino.h>

static const uint8_t speed_sequence[] = { 0, 90, 170, 255, 170, 90 };
static uint8_t motor_state = 0;
static uint8_t button_last = 1;
static unsigned long button_last_change = 0;

void motor_init(void) {
    MOTOR_DATA_DIR_B |= MOTOR_PB3;

    MOTOR_CTRL_A = 0;
    MOTOR_CTRL_B = 0;

    MOTOR_CTRL_A = MOTOR_COM2A1 | MOTOR_WGM21 | MOTOR_WGM20;
    MOTOR_CTRL_B = MOTOR_CS20;

    MOTOR_COMPARE_A = 0;

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    button_last = digitalRead(BUTTON_PIN);
    button_last_change = mymilli();
}

void motor_task(void) {
    uint8_t button_now = digitalRead(BUTTON_PIN);
    unsigned long now = mymilli();

    if (button_now != button_last) {
        if (now - button_last_change >= 30) {
            if (button_now == 0) {
                motor_state = (motor_state + 1) % 6;
                MOTOR_COMPARE_A = speed_sequence[motor_state];
            }
            button_last = button_now;
            button_last_change = now;
        }
    } else {
        button_last_change = now;
    }
}