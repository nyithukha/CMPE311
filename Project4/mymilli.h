#ifndef MYMILLI_H
#define MYMILLI_H

#include <stdint.h>

// Timer0 registers 
#define TIMER0_CTRL_A     (*(volatile uint8_t *)0x44)
#define TIMER0_CTRL_B     (*(volatile uint8_t *)0x45)
#define TIMER0_COUNT      (*(volatile uint8_t *)0x46)
#define TIMER0_COMPARE_A  (*(volatile uint8_t *)0x47)
#define TIMER0_INT_MASK   (*(volatile uint8_t *)0x6E)

// Timer0 settings
#define TIMER0_WGM01      (1 << 1)
#define TIMER0_CS01       (1 << 1)
#define TIMER0_CS00       (1 << 0)
#define TIMER0_OCIE0A     (1 << 1)

#ifdef __cplusplus
extern "C" { 
#endif
// Function declarations
void mymilli_init(void);
unsigned long mymilli(void);

#ifdef __cplusplus 
} 
#endif

#endif 
