# Embedded Daily - Project Title

**Series:** Embedded Daily  
**Project Number:** 1  
**Author:** Kenneth Rodney Aboué  
**Date:** 2025-11-04   

---

## Overview
This project is part of the **Embedded Daily** series, where I showcase daily embedded systems and electronics projects using Arduino, Raspberry Pi, and other microcontrollers.

## 📅 Projects List

### 🧊 1. Temperature Control System
**Date:** 2025-11-04  
**Description:**   
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

### 🚗 2. UltraBarrier – Ultrasonic Vehicle Detection Gate
**Date:** 2025-11-05  
**Description:**  
> An automatic barrier system using an **ultrasonic sensor** to detect approaching vehicles or objects.  
When a vehicle is detected within a specific distance, an LED blinks and a servo motor lifts the barrier. Once the vehicle passes, the barrier returns to its initial position.

**Hardware:**
- Arduino Uno  
- HC-SR04 ultrasonic sensor  
- Servo motor  
- LED + resistor  
- Breadboard and jumper wires  

**Features:**
- Real-time distance measurement  
- LED alert for object detection  
- Automatic barrier control with servo motor  

### ⚡ 3. ReactionRacer – Real-Time Reaction Timer with Joystick and LCD
**Date:** 2025-11-05  
**Description:**  
> A reaction speed game that measures how fast a user can press a **joystick button** after the green light appears.  
The **LCD screen** displays a live timer counting up, and shows the player’s reaction time in milliseconds once the button is pressed.

**Hardware:**
- Arduino Uno  
- Joystick module (button only)  
- 3 LEDs (Red, Orange, Green)  
- 16x2 LCD display  
- Resistors + jumper wires + breadboard  

**Features:**
- Sequential LED signals (Red → Orange → Green)  
- Live countdown timer displayed on LCD  
- Real-time reaction measurement  
- Anti-rebound button handling  
- Randomized delay to avoid anticipation

---

## 🧰 How to Use
1. Clone this repository:  
   ```bash
   git clone https://github.com/rodneyaboue/Embedded-Daily.git