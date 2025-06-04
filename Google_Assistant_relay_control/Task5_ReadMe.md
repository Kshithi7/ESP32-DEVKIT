# 📌 Task 5: Google Assistant Relay Control

## 📖 Description
A system that uses an ESP32 to control a relay via Adafruit IO, which is integrated with Google Assistant. The relay is controlled remotely using voice commands sent through Google Assistant, allowing users to turn an appliance on or off. The ESP32 connects to Wi-Fi and fetches the relay status from Adafruit IO to control the relay accordingly.

## 🎯 Aim
To enable control of a relay through Google Assistant, using Adafruit IO as an intermediary, with the ESP32 retrieving the relay status and acting on the command received.

## 🛠️ Features Implemented
- 🌐 Wi-Fi connectivity for the ESP32 to access Adafruit IO
- 🔄 Fetch relay status from Adafruit IO through HTTP requests
- 🔌 Control the relay based on Google Assistant voice commands
- 📡 Real-time relay state update via the Adafruit IO feed

## ⚙️ Components Used
- ✅ ESP32 Devkit board
- ✅ Relay connected to a GPIO pin
- ✅ Wi-Fi connectivity (for ESP32 to communicate with Adafruit IO)
- ✅ Adafruit IO for remote relay control
- ✅ Google Assistant (for voice control)

## 🧠 Learnings
- Working with Adafruit IO to control devices remotely
- Sending HTTP requests from the ESP32 to interact with external services
- Interfacing ESP32 with a relay for appliance control
- Using voice commands with Google Assistant to trigger remote actions

## ✅ Output
- The relay is turned ON or OFF based on commands received from [Google Assistant through Adafruit IO](images/relay_io_control).
- Relay status is updated and printed on the [Serial Monitor](images/relay_io_control/esp32_serial_monitor_op.png).
- ESP32 connects to Wi-Fi, fetches the relay control status, and acts accordingly.
