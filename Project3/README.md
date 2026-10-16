# Cyclic Executive Task Manager — CMPE 311

**Author:** Nyi Thu Kha  
**Course:** CMPE 311, UMBC  
**Date:** 10/15/2026

## Overview
Extends PROJECT-CE by replacing Arduino's built-in `millis()` with a custom `mymilli()` function backed by a Developer-owned Timer0 CTC ISR and locally defined register constants. User-visible behavior is unchanged. Two LEDs on digital pins 2 and 3 can have their blink intervals set independently via the Arduino IDE serial monitor at 9600 baud.

## Requirements
- ELEGOO Uno R3 (or compatible Arduino Uno R3)
- 2 × LEDs
- 2 × 200 Ω resistors
- Breadboard and jumper wires
- Arduino IDE 2.3.3 or later

## How to Compile and Run
1. Place `async_led_ce.ino`, `mymilli.h`, and `mymilli.c` in the same folder.
2. Open `async_led_ce.ino` in Arduino IDE.
3. Select board: **Arduino Uno**.
4. Select the correct COM port.
5. Upload the sketch.
6. Open Serial Monitor at **9600 baud**, line ending **Newline**.
7. Follow the prompts:
   - Enter `1` or `2` for LED selection.
   - Enter the desired blink interval in milliseconds (e.g., `600`).

## Design Notes
- Round-robin cyclic executive with a function pointer table.
- Custom `mymilli()` replaces Arduino `millis()`.
- Custom Timer0 CTC ISR with `OCR0A = 249` for exactly 1 ms per tick.
- Custom register constants replace `avr.h` names.
- Atomic read via `cli()` / `SREG` restore.
- `extern "C"` guards in `mymilli.h` bridge C++ and C compilation units.
- Arduino `millis()` and `delay()` are non-functional under this design and 
  are not used.
- LEDs are on pins 2 and 3 per EC.3.

## Report
The full design report is available at [`report.pdf`](./report.pdf). The Engineering Change Note is at [`ECN1_1.pdf`](./ECN1_1.pdf).

## Changes from PROJECT-CE
See `ECN1.2.pdf` and `SDD_PROJECT-MYMILLI_v1.2.pdf` for full details.

## License
Educational use only.
