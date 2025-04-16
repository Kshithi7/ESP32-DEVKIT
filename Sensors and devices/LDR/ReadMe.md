# 🌞 Light Dependent Resistor (LDR)

## 📖 Description
An LDR is a variable resistor whose resistance decreases with increasing light intensity. It is widely used in:
- Ambient light sensing
- Auto-brightness controls
- Day/night detectors
- Solar tracking systems

## 🔌 Connections
| LDR Pin   | ESP32 |
|-----------|-------|
| One end   | 3.3V  |
| Other end | GPIO 34 (Analog Input) + 10kΩ pull-down resistor to GND |

> *Use a voltage divider circuit to read varying voltages from the LDR into an analog pin.*

## 🔧 Voltage Divider Circuit
3.3V --- [ LDR ] ---+--- [ 10kΩ Resistor ] --- GND | GPIO 34 (Analog input)
