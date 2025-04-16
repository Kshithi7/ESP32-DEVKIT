# 🌡️ LM35 Temperature Sensor

## 📖 Description
The LM35 is a precision analog temperature sensor that provides a linear output voltage directly proportional to the temperature in °C. It's super simple and doesn’t need calibration.

- Output: 10mV per °C
- Range: -55°C to 150°C
- Accuracy: ±0.5°C (at 25°C)

## 🔌 Connections
| LM35 Pin | Function     | ESP32      |
|----------|--------------|------------|
| 1 (VCC)  | Power        | 3.3V       |
| 2 (Vout) | Analog Out   | GPIO 34    |
| 3 (GND)  | Ground       | GND        |

> ⚠️ Use a breadboard and make sure your connections are secure. LM35 is analog, so avoid noisy pins.

🧠 Learnings
Reading analog signals from sensors

Converting ADC readings to voltage and then temperature

Understanding ESP32's ADC resolution (12-bit = 0–4095)

✅ Output
Serial monitor prints live temperature in °C

Can be used in real-time temperature monitoring systems, fan automation, or smart thermostats

Let me know if you want to:

🔔 Add a buzzer/LED alert for high temperature

☁️ Push temperature data to the cloud

📈 Graph it on OLED or LCD

This tiny sensor packs a lot of punch!

