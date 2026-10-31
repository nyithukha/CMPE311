#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>

#define MOTOR_CTRL_A      (*(volatile uint8_t *)0xB0)
#define MOTOR_CTRL_B      (*(volatile uint8_t *)0xB1)
#define MOTOR_COMPARE_A   (*(volatile uint8_t *)0xB3)
#define MOTOR_DATA_DIR_B  (*(volatile uint8_t *)0x24)

#define MOTOR_COM2A1      (1 << 7)
#define MOTOR_WGM21       (1 << 1)
#define MOTOR_WGM20       (1 << 0)
#define MOTOR_CS20        (1 << 0)
#define MOTOR_PB3         (1 << 3)

#define MOTOR_PWM_PIN     11
#define BUTTON_PIN        4

#ifdef __cplusplus
extern "C" {
#endif

void motor_init(void);
void motor_task(void);

#ifdef __cplusplus
}
#endif

#endif