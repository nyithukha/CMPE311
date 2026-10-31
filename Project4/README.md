# PWM Fan Controller — CMPE 311

**Author:** Nyi Thu Kha  
**Course:** CMPE 311, UMBC  
**Date:** 10/31/2026

## Overview
This project extends PROJECT-MYMILLI by adding a DC motor-driven fan controlled by a pushbutton. The fan cycles through OFF, LOW, MEDIUM, HIGH, MEDIUM, and LOW with each press. PWM is generated on Timer2 (Arduino pin 11) through a low-side MOSFET driver. Two LEDs on digital pins 2 and 3 can still have their blink intervals set independently via the Arduino IDE serial monitor at 9600 baud, using the custom `mymilli()` timer and round-robin cyclic executive from Project 3.

## Requirements
- ELEGOO Uno R3 (or compatible Arduino Uno R3)
- 2 × LEDs
- 2 × 200 Ω resistors
- 1 × IRFZ34N N-channel MOSFET
- 1 × 1N4004 flyback diode
- 1 × 150 Ω resistor (gate), 1 × 10 kΩ resistor (pull-down)
- 1 × 0.1 µF capacitor (motor decoupling)
- 1 × 4-legged pushbutton
- 1 × DC motor with propeller
- 9 V 1000 mA AC/DC adapter
- Breadboard and jumper wires
- Arduino IDE 2.3.3 or later

## How to Compile and Run
1. Place `async_led_ce.ino`, `mymilli.h`, `mymilli.c`, `motor.h`, and `motor.c` in the same folder.
2. Open `async_led_ce.ino` in Arduino IDE.
3. Select board: **Arduino Uno**.
4. Select the correct COM port.
5. Upload the sketch.
6. Open Serial Monitor at **9600 baud**, line ending **Newline**.
7. Follow the prompts:
   - Enter `1` or `2` for LED selection.
   - Enter the desired blink interval in milliseconds (e.g., `600`).
8. Press the pushbutton to cycle the fan through its six states.

## Design Notes
- Round-robin cyclic executive with a function pointer table.
- Four non-blocking tasks: `taskSerial`, `taskLed1`, `taskLed2`, `taskMotor`.
- Custom `mymilli()` replaces Arduino `millis()` (Timer0 CTC ISR, 1 ms tick).
- Timer2 Fast PWM on pin 11 (OC2A), no prescaler.
- Low-side IRFZ34N MOSFET driver with 1N4004 flyback and 0.1 µF decoupling.
- Button debounced in software (30 ms) using `mymilli()`.
- Fan cycles through six states: OFF, LOW, MEDIUM, HIGH, MEDIUM, LOW.
- Arduino `millis()` and `delay()` are non-functional under this design and are not used.
- LEDs are on pins 2 and 3 per EC.3.

## Report
The full design report is available at `report.pdf`. The Engineering Change Note is at `ECN1.3.pdf`.

## License
Educational use only.
