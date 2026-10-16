/*
 * Cyclic Executive Task Manager — PROJECT-MYMILLI
 * CMPE311 Project 3
 * Uses custom mymilli() in place of Arduino millis().
 * Custom Timer0 CTC ISR at 1 ms tick. Registers defined locally.
 * Round-robin cyclic executive with function pointer table.
 * LEDs on digital pins 2 and 3. Serial monitor at 9600 baud.
 */

#include "mymilli.h"

#define LED1_PIN 2
#define LED2_PIN 3

// LED blink intervals and last toggle times 
unsigned long interval1 = 1000;
unsigned long interval2 = 1000;
unsigned long lastToggle1 = 0;
unsigned long lastToggle2 = 0;
bool state1 = false;
bool state2 = false;

// Tracks which serial input is expected 
enum SerialState { WAIT_LED, WAIT_INTERVAL };
SerialState serialState = WAIT_LED;
int selectedLED = 0;
char inputBuffer[16];
int bufferIndex = 0;

void taskSerial(void);
void taskLed1(void);
void taskLed2(void);

typedef void (*TaskFunc)(void);
// Tasks run one at a time in this order 
TaskFunc taskTable[] = { taskSerial, taskLed1, taskLed2 };
const int NUM_TASKS = sizeof(taskTable) / sizeof(taskTable[0]);

void setup() {
    Serial.begin(9600);
    mymilli_init();

    while (Serial.available() > 0) {
        Serial.read();
    }

    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);

    Serial.println("What LED? (1 or 2)");
}

void loop() {
    static int currentTask = 0;
    // Run the next task in the table
    taskTable[currentTask]();
    currentTask = (currentTask + 1) % NUM_TASKS;
}

void taskSerial(void) {
    while (Serial.available() > 0) {
        char c = Serial.read();

        if (serialState == WAIT_LED) {
            if (c == '1' || c == '2') {
                selectedLED = c - '0';
                serialState = WAIT_INTERVAL;
                bufferIndex = 0;
                Serial.print("What interval (in msec)? ");
            }
        }
        else if (serialState == WAIT_INTERVAL) {
            if (c >= '0' && c <= '9') {
                if (bufferIndex < sizeof(inputBuffer) - 1) {
                    inputBuffer[bufferIndex++] = c;
                }
            }
            else if (c == '\n' || c == '\r') {
                if (bufferIndex > 0) {
                    inputBuffer[bufferIndex] = '\0';
                    unsigned long interval = atol(inputBuffer);
                    if (interval > 0) {
                        if (selectedLED == 1) {
                            interval1 = interval;
                            lastToggle1 = mymilli();
                        }
                        else if (selectedLED == 2) {
                            interval2 = interval;
                            lastToggle2 = mymilli();
                        }
                    }
                    // Return to asking which LED to control
                    serialState = WAIT_LED;
                    bufferIndex = 0;
                    Serial.println();
                    Serial.println("What LED? (1 or 2)");
                }
            }
        }
    }
}

void taskLed1(void) {
    unsigned long now = mymilli();
    // Toggle LED 1 when half its interval has passed
    if (now - lastToggle1 >= interval1 / 2) {
        state1 = !state1;
        digitalWrite(LED1_PIN, state1 ? HIGH : LOW);
        lastToggle1 = now;
    }
}

void taskLed2(void) {
    unsigned long now = mymilli();
    // Toggle LED 2 when half its interval has passed
    if (now - lastToggle2 >= interval2 / 2) {
        state2 = !state2;
        digitalWrite(LED2_PIN, state2 ? HIGH : LOW);
        lastToggle2 = now;
    }
}