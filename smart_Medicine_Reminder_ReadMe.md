# 📌 Task 1: Smart Medicine Reminder System

## 📖 Description
A Smart Medicine Reminder System built using an ESP32 dev board, an LCD, push buttons, a buzzer, and NTP time fetched over WiFi. This system allows users to set up to 5 reminders with custom messages. Reminders are saved via serial input and the system alerts users at the scheduled time using a buzzer and LCD display.

## 🎯 Aim
To build a minimal, hardware-interactive medicine reminder system using real-time time synchronization from an NTP server, controlled via a physical menu system.

## 🛠️ Features Implemented
- ⏰ NTP-based real-time clock (IST timezone)
- 📟 LCD date-time display
- 🔘 Push-button-controlled menu system:
  - **Set Reminder** (via LCD and Serial input)
  - **View Reminders** (shown in Serial Monitor)
  - **Delete Reminder** (by index via Serial)
- 🔔 Buzzer alert when the set reminder time matches
- 💾 Handles up to 5 custom reminders

## ⚙️ Components Used
- ✅ ESP32 Devkit board
- ✅ LCD 16x2 (using 6 GPIO pins)
- ✅ 4 Push buttons (Menu, Up, Down, Enter)
- ✅ Passive buzzer
- ✅ Wi-Fi connectivity (for NTP)
- ✅ Serial Monitor (for reminder message input/output)

## 🧠 Learnings
- Interfacing NTP time with ESP32
- Using `LiquidCrystal` library for non-I2C LCDs
- Implementing menu navigation using push buttons
- Handling real-time alerts and reminders in embedded systems
- Structuring data in arrays of structs (`Reminder[]`)

## ✅ Output
- Real-time date and time are shown continuously on the LCD.
- When a reminder matches the current time:
  - Message is displayed on LCD.
  - Buzzer beeps 5 times.
- Users can interact through buttons to set, view, or delete reminders.
- Reminder messages and operations are logged in the Serial Monitor.
