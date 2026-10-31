/*
 * PWM Fan Controller with Cyclic Executive — PROJECT-ADDMOTOR
 * CMPE311 Project 4
 * Extends PROJECT-MYMILLI with a PWM-driven DC fan and pushbutton control.
 * Timer2 Fast PWM on pin 11 (OC2A). Button on pin 4 with software debounce.
 * Uses custom mymilli() timer and round-robin cyclic executive.
 * LEDs on pins 2 and 3. Serial monitor at 9600 baud.
 */

#include "mymilli.h"
#include "motor.h"

#define LED1_PIN 2
#define LED2_PIN 3

unsigned long interval1 = 1000;
unsigned long interval2 = 1000;
unsigned long lastToggle1 = 0;
unsigned long lastToggle2 = 0;
bool state1 = false;
bool state2 = false;

enum SerialState { WAIT_LED, WAIT_INTERVAL };
SerialState serialState = WAIT_LED;
int selectedLED = 0;
char inputBuffer[16];
int bufferIndex = 0;

void taskSerial(void);
void taskLed1(void);
void taskLed2(void);
void taskMotor(void);

typedef void (*TaskFunc)(void);
TaskFunc taskTable[] = { taskSerial, taskLed1, taskLed2, taskMotor };
const int NUM_TASKS = sizeof(taskTable) / sizeof(taskTable[0]);

void setup() {
    Serial.begin(9600);
    mymilli_init();
    motor_init();

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
    if (now - lastToggle1 >= interval1 / 2) {
        state1 = !state1;
        digitalWrite(LED1_PIN, state1 ? HIGH : LOW);
        lastToggle1 = now;
    }
}

void taskLed2(void) {
    unsigned long now = mymilli();
    if (now - lastToggle2 >= interval2 / 2) {
        state2 = !state2;
        digitalWrite(LED2_PIN, state2 ? HIGH : LOW);
        lastToggle2 = now;
    }
}

void taskMotor(void) {
    motor_task();
}