# Encoder Motor Control with XOR Logic using Single GPIO

This project demonstrates a method to control both **direction** and read **speed/position** of an **encoder-based DC motor** using only **one GPIO pin** on the ESP32. Direction control is achieved via an **XOR logic gate (74HC86)**, which generates the complementary signal needed for the motor driver (TB6612FNG).

## 🔧 Hardware Setup

- **Microcontroller**: ESP32
- **Motor Driver**: TB6612FNG
- **DC Motor**: JGA25-370 with Encoder (6-wire)
- **Logic Gate**: 74HC86 (XOR)
- **Power Supply**:
  - VM (motor power): 6–12V
  - Logic: 3.3V (ESP32)

### 🧩 Wiring Overview

| Function       | Connection            |
|----------------|------------------------|
| AIN1           | GPIO18 (ESP32)         |
| AIN2           | Output of XOR gate     |
| XOR Input A    | GPIO18 (ESP32)         |
| XOR Input B    | 3.3V                   |
| STBY           | GPIO26 (ESP32)         |
| PWMA           | Connected to 3.3V      |
| AO1, AO2       | Motor terminals        |
| Encoder A (C2) | GPIO19 (ESP32)         |
| Encoder B (C1) | GPIO21 (ESP32)         |
| Encoder VCC    | 3.3V or 5V             |
| Encoder GND    | GND (shared)           |

> ✅ IN2 is generated as the XOR of IN1 and 3.3V → effectively `NOT(IN1)`

## ⚙️ Features

- Motor direction control with **only 1 GPIO** using XOR logic.
- Real-time encoder feedback using interrupts.
- Count display and simple speed estimation.
- Easily expandable to PID speed/position control.

## 📜 Code Overview

- Uses `attachInterrupt()` to count encoder pulses on Channel A.
- Direction is toggled by setting `GPIO18` HIGH or LOW.
- Encoder count and basic speed (delta count) are printed via Serial Monitor.


## 🚀 Getting Started

1. Flash the provided Arduino sketch to your ESP32.
2. Open Serial Monitor at `115200 baud`.
3. The motor will:
   - Spin forward (3s)
   - Pause (1s)
   - Spin reverse (3s)
   - Stop

4. Encoder count updates will display continuously.

## 📁 File Structure

encoder-motor-xor/
├── src/
│ └── encoder_motor.ino # Main Arduino sketch
├── README.md
└── LICENSE (optional)

## 🧪 Future Improvements

- Add PID position/speed control.
- Replace XOR logic with software-controlled dual GPIO for flexibility.
- Integrate OLED or GUI for live monitoring.

## 📘 License

MIT License. Feel free to use, modify, and share.

## 🤝 Credits

Developed by [Thang Nguyen]  
Project for robotic motor control optimization with minimal IO usage.


