# 🚀 ESP32 DevKit Module - Quick Reference & Setup Guide

The **ESP32 DevKit** is a powerful, dual-core microcontroller module with built-in WiFi and Bluetooth, perfect for IoT, embedded systems, and automation projects.

---

## 📦 Features

- 🧠 **Processor**: Dual-core Tensilica LX6, up to 240MHz
- 🛜 **Connectivity**: 802.11 b/g/n WiFi + Bluetooth 4.2 (Classic + BLE)
- 💾 **Memory**:
  - 520 KB SRAM
  - 4MB Flash (external)
- 🔌 **I/O**:
  - 34 Programmable GPIOs (varies by board)
  - 12-bit ADCs, DACs, PWM, SPI, I2C, UART, etc.
- ⚡ **Operating Voltage**: 3.3V (but USB input is 5V safe)
- 🧩 **USB Interface**: Micro-USB for power and serial communication

---

## 🛠️ Pinout Reference

| Pin | Function     | Notes                            |
|-----|--------------|----------------------------------|
| GPIO0 | Boot Mode  | Must be LOW to enter bootloader |
| GPIO2 | Output Only | Safe for LED, etc.              |
| GPIO4/5/12–19/21–23 | General Purpose I/O | Good for sensors, LCDs, etc. |
| GPIO34–39 | Input Only | Ideal for analog inputs       |

> 📝 *Always check your specific board’s datasheet. Some pins have restrictions depending on flash or boot configurations.*

---

## 🧰 Getting Started

### 🔗 Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)
- [ESP32 Board Package](https://github.com/espressif/arduino-esp32)
  - Install via: `Tools` → `Board Manager` → Search “ESP32”

### 🔌 Setup Instructions

1. Connect ESP32 via USB.
2. Open Arduino IDE → Go to `Tools`:
   - Board: `ESP32 Dev Module`
   - Port: Select the COM port
   - Upload Speed: `115200` (default)
3. Upload a sample sketch (e.g., `WiFiScan.ino`)
4. Open Serial Monitor (set to 115200 baud)

---

## ⚙️ Common Libraries for ESP32

- `WiFi.h` – WiFi functionality
- `BluetoothSerial.h` – Classic Bluetooth
- `ESP32Servo.h` – Servo control
- `LiquidCrystal.h` – LCD (non-I2C)
- `Wire.h` – I2C communication
- `SPI.h` – SPI communication
- `EEPROM.h` – Non-volatile memory
- `HTTPClient.h` – Web requests (GET/POST)
- `WiFiClientSecure.h` – HTTPS client

---

## 📚 Sample Projects

- ✅ WiFi-enabled Weather Station
- ✅ Smart Medicine Reminder System
- ✅ Bluetooth-controlled Relay
- ✅ Motor Speed Controller using ADC
- ✅ OLED-based Keypad Authentication System

---

## 🧠 Tips

- Always level-shift inputs if using 5V sensors.
- Avoid using GPIOs 6–11; these are typically reserved for internal flash.
- Use `Serial.begin(115200);` to debug easily.
- Combine with external RTC if precise offline timekeeping is needed.

---

## 🛡️ Disclaimer

> This guide assumes usage of a generic ESP32 DevKit board. Always consult your exact model’s datasheet for hardware-specific behaviors.

---

Happy Hacking! ✨  
Made with ❤️ for embedded tinkerers and IoT creators.
