# Embedded Daily - Project Title

**Series:** Embedded Daily  
**Project Number:** 1  
**Author:** Kenneth Rodney Aboué  
**Date:** YYYY-MM-DD  

---

## Overview
This project is part of the **Embedded Daily** series, where I showcase daily embedded systems and electronics projects using Arduino, Raspberry Pi, and other microcontrollers.

**Project Description:**  
Briefly describe what the project does. Example:  
> This project monitors temperature and humidity using a DHT11 sensor and displays the values on a 16x2 LCD. Two LEDs indicate if the temperature is too low (blue) or too high (red), demonstrating a simple embedded control system with hysteresis.

---

## Hardware
- Arduino Uno/Nano
- DHT11 temperature and humidity sensor
- 16x2 LCD display
- LEDs (red and blue) with 220 Ω resistors
- Optional: Fan or small heater for temperature simulation
- Wires, breadboard, power supply

---

## Software / Libraries
- Arduino IDE
- `DHT.h` library
- `LiquidCrystal.h` library

---

## Features / Objectives
- Read temperature and humidity values
- Display values in real-time on an LCD
- Trigger LED alerts based on thresholds
- Implement hysteresis to avoid flickering
- Demonstrate embedded system control logic

---

## Usage
1. Upload the `.ino` file to your Arduino.  
2. Connect the hardware as described above.  
3. Observe the LCD display and LED indicators reacting to temperature changes.  

---

## Project Files
- `ProjectName.ino` – Main Arduino sketch
- Optional: Photos, schematics, diagrams
- `README.md` – Project documentation

---

## Notes
- Adjust `TEMP_LOW` and `TEMP_HIGH` constants according to your environment.  
- Ensure proper resistors are used for LEDs to prevent damage.  
- This template can be reused for every project in the **Embedded Daily** series.

---

## Video / Demo
Attach a short video or GIF demonstrating the project in action.  

---

## License
Optional: Specify license if you want, e.g. MIT License.
