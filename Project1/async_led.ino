/*
 * Async LED Blink Controller
 * CMPE310 Async Lab
 * Bare-metal, non-blocking, millis() based
 * No delay(), no FreeRTOS, no third-party multitasking libraries
 * LEDs on digital pins 2 and 3
 * Serial monitor at 9600 baud
 */

#define LED1_PIN 2
#define LED2_PIN 3

unsigned long interval1 = 1000; // default 1000 ms (for full period)
unsigned long interval2 = 1000;
unsigned long lastToggle1 = 0;
unsigned long lastToggle2 = 0;
bool state1 = false; // off at start
bool state2 = false;

// Serial parsing state machine
enum SerialState { WAIT_LED, WAIT_INTERVAL };
SerialState serialState = WAIT_LED;
int selectedLED = 0;
char inputBuffer[16];
int bufferIndex = 0;

void setup() {
    Serial.begin(9600);
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    digitalWrite(LED1_PIN, LOW);
    digitalWrite(LED2_PIN, LOW);
    Serial.println("What LED? (1 or 2)");
}

void loop() {
    // Asynchronous serial input handling
    while (Serial.available() > 0) {
        char c = Serial.read();

        if (serialState == WAIT_LED) {
            if (c == '1' || c == '2') {
                selectedLED = c - '0';
                serialState = WAIT_INTERVAL;
                bufferIndex = 0;
                Serial.print("What interval (in msec)? ");
            } // ignore all other characters (including newline after LED selection)
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
                            lastToggle1 = millis(); // reset timing for LED1
                        } else if (selectedLED == 2) {
                            interval2 = interval;
                            lastToggle2 = millis(); // reset timing for LED2
                        }
                    } // reset for next prompt
                    serialState = WAIT_LED;
                    bufferIndex = 0;
                    Serial.println(); // newline after interval
                    Serial.println("What LED? (1 or 2)");
                } // if bufferIndex == 0, ignore newline (like after LED selection)
            } // ignore other non-digit characters
        }
    }
    
    // Non-blocking LED toggling using millis() 
    unsigned long now = millis();
    
    if (now - lastToggle1 >= interval1 / 2) {
        state1 = !state1;
        digitalWrite(LED1_PIN, state1 ? HIGH : LOW);
        lastToggle1 = now;
    }
    
    if (now - lastToggle2 >= interval2 / 2) {
        state2 = !state2;
        digitalWrite(LED2_PIN, state2 ? HIGH : LOW);
        lastToggle2 = now;
    }
}