# html-RC

A simple ESP32-based WiFi remote controller for dual DC motors.  
The ESP32 runs as a WiFi access point, serves a responsive HTML interface, and drives two motors via PWM + direction pins.

---

## Features

- **WiFi Access Point** (default SSID: `rc_UNIMAP`, password: `12345678`)
- **Web interface** with:
  - Directional buttons: Forward, Reverse, Left, Right, Stop  
  - Speed slider (0–255)  
  - Debug/status display  
  - Fullscreen toggle  
- **Dual-motor control** via two PWM channels and two direction pins  
- Easy to customize network settings, pins, UI styling, and default speed

---

## Hardware Requirements

- **ESP32** development board  
- **Two DC motor driver modules** (e.g. BTS7960, L298N, etc.)  
- **Two DC motors**  
- Jumper wires and power supply as required by your motors/driver

---

## Pinout / Wiring

| Function             | ESP32 Pin | Motor Driver Input |
|----------------------|-----------|--------------------|
| Motor 1 PWM (speed)  | GPIO 26   | PWM1               |
| Motor 1 DIR          | GPIO 25   | DIR1               |
| Motor 2 PWM (speed)  | GPIO 27   | PWM2               |
| Motor 2 DIR          | GPIO 33   | DIR2               |
| GND                  | GND       | GND                |
| ESP32 5 V / 3.3 V    | VIN / 3V3 | VCC on driver      |

> **Note:** Make sure your motor driver’s logic‐level VCC matches the ESP32’s output voltage (3.3 V).

---

## Software Dependencies

- [Arduino Core for ESP32](https://github.com/espressif/arduino-esp32)  
- Built‐in Arduino libraries:  
  - `WiFi.h`  
  - `WebServer.h`  

All other code (HTML/CSS/JS) is embedded in `html_page.h`.

---

## Getting Started

1. **Clone this repository**  
   ```bash
   git clone https://github.com/<your-username>/rc_UNIMAP.git
   cd html-RC
