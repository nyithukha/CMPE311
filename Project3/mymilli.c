#include "mymilli.h"
#include <avr/interrupt.h>

// Stores the number of milliseconds
static volatile unsigned long my_timer0_millis = 0;

void mymilli_init(void) {
    cli(); // Disable interrupts during setup

    TIMER0_CTRL_A = TIMER0_WGM01;
    TIMER0_CTRL_B = TIMER0_CS01 | TIMER0_CS00;
    TIMER0_COMPARE_A = 249;
    TIMER0_COUNT = 0;
    TIMER0_INT_MASK = TIMER0_OCIE0A;

    sei(); // Enable interrupts
}

unsigned long mymilli(void) {
    unsigned long m;
    uint8_t oldSREG = SREG;
    cli(); // Prevent the counter from changing during the read
    m = my_timer0_millis;
    SREG = oldSREG;
    return m;
}

// Runs each time Timer0 reaches the compare value
ISR(TIMER0_COMPA_vect) {
    my_timer0_millis++;
}
