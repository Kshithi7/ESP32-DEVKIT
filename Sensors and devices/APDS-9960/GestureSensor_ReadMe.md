# ✋ APDS-9960 Gesture & Proximity Sensor

## 📖 Description
The APDS-9960 is an I2C-based sensor capable of detecting:
- Hand gestures (up, down, left, right)
- Proximity (distance detection)
- Ambient light
- RGB color sensing

Commonly used in gesture-controlled systems, smart screens, and wearables.

## 🔌 Connections
| Sensor Pin | ESP32 Pin  |
|------------|------------|
| VCC        | 3.3V       |
| GND        | GND        |
| SDA        | GPIO 21    |
| SCL        | GPIO 22    |
| INT        | Optional   |

> *Make sure to use 3.3V logic only.*
