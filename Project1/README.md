# Async LED Blink Controller - CMPE 311

**Author:** Nyi Thu Kha
**Course:** CMPE311, UMBC  
**Date:** 9/27/2026

## Overview
This project implements an asynchronous, non-blocking LED blink controller on an ELEGOO Uno R3. Two LEDs on digital pins 2 and 3 can have their blink intervals set independently via the Arduino IDE serial monitor at 9600 baud.

## Requirements
- ELEGOO Uno R3 (or compatible Arduino Uno R3)
- 2 × LEDs
- 2 × 200 Ω resistors
- Breadboard and jumper wires
- Arduino IDE 2.3.3 or later

## How to Compile and Run
1. Open `async_led.ino` in Arduino IDE.
2. Select board: **Arduino Uno**.
3. Select the correct COM port.
4. Upload the sketch.
5. Open Serial Monitor at **9600 baud**.
6. Follow the prompts:
   - Enter `1` or `2` for LED selection.
   - Enter the desired blink interval in milliseconds (e.g., `600`).

## Design Notes
- Uses `millis()` for non-blocking timing.
- No `delay()`, no FreeRTOS, no third-party multitasking libraries.
- Interval is the full period; on/off times are each half the interval.
- LEDs are on pins 2 and 3 per EC.3.

## Report
The full design report is available at [`report.pdf`](./report.pdf).

## License
Educational use.
