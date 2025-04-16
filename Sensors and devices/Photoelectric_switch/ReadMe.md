# 🔦 Photoelectric Switch Sensor

## 📖 Description
A photoelectric switch is an optical sensor that detects the presence or absence of an object using light. It is commonly used for:
- Object detection
- Line following
- Proximity-based triggers

It outputs a **digital HIGH/LOW signal** based on the reflection or interruption of light.

## 🔌 Connections (NPN Type)
| Sensor Pin | ESP32 Pin / Power |
|------------|-------------------|
| Brown      | 5V                |
| Blue       | GND               |
| Black (Signal) | GPIO 27 (example) |

> *Note: Use a voltage divider or logic level shifter if the sensor outputs 5V and your ESP32 only tolerates 3.3V on GPIOs.*

## 🛠️ Code Overview
- Reads digital input from the photoelectric sensor
- Turns an LED ON or OFF based on object detection
