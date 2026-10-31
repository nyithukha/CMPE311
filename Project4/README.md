# PROJECT-ADDMOTOR — PWM Fan Controller

**Author:** Nyi Thu Kha  
**Course:** CMPE 311, UMBC  
**Date:** <DATE>

## Overview
Extends PROJECT-MYMILLI by adding a DC motor-driven fan controlled by a 
pushbutton. The fan cycles through OFF → LOW → MEDIUM → HIGH → MEDIUM → LOW 
→ OFF with each press. PWM is generated on Timer2 (Arduino pin 11) through a 
low-side MOSFET driver. The custom `mymilli()` timer, cyclic executive, LED 
control, and serial interface from Project 3 are unchanged.

## Requirements
- ELEGOO Uno R3 (or compatible)
- 2 × LEDs, 2 × 200 Ω resistors
- 1 × IRFZ34N N-channel MOSFET
- 1 × 1N4004 flyback diode
- 1 × 150 Ω resistor (gate), 1 × 10 kΩ resistor (pull-down)
- 1 × 0.1 µF capacitor (motor decoupling)
- 1 × 4-legged pushbutton
- 1 × DC motor with propeller
- 9 V 1000 mA AC/DC adapter
- Arduino IDE 2.3.3 or later

## Wiring Summary
- Pin 11 → 150 Ω → MOSFET gate; gate → 10 kΩ → GND
- MOSFET source → GND; drain → motor negative
- Motor positive → +9 V from adapter via Vin
- 1N4004 across motor (cathode to +9 V, anode to motor negative)
- 0.1 µF capacitor across motor terminals
- Button: pin 4 → one leg, GND → diagonal opposite leg

## How to Compile and Run
1. Place `async_led_ce.ino`, `mymilli.h`, `mymilli.c`, `motor.h`, `motor.c` 
   in the same folder.
2. Open `async_led_ce.ino` in Arduino IDE.
3. Select board: **Arduino Uno**.
4. Select the correct COM port.
5. Upload.
6. Open Serial Monitor at **9600 baud**, Newline.
7. Press the button to cycle fan speeds. Use the serial dialog for LEDs.

## Design Notes
- Timer2 Fast PWM on pin 11 (OC2A), no prescaler.
- Low-side IRFZ34N with 1N4004 flyback and 0.1 µF decoupling.
- Button debounced in software (30 ms) using `mymilli()`.
- `taskMotor` added to the cyclic executive task table.
- Arduino `millis()` and `delay()` are non-functional under this design and 
  are not used.
- All prior project behavior preserved.

## Report
`SDD_PROJECT-ADDMOTOR_v1.3.pdf`  
`ECN1.3.pdf`
