 ///board with COM7

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <LiquidCrystal.h>

// Wi-Fi Credentials
const char* ssid = "<Your WiFi SSID>";
const char* password = "<WiFi password>";

// NTP Setup
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 19800, 60000); // IST offset (5hr 30min)

// LCD Pins
const int rs = 16, en = 17, d4 = 19, d5 = 21, d6 = 22, d7 = 23; // port connected to lcd
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Button Pins
const int buttonMenu = 32;  // pin numbers connected to push buttons
const int buttonUp = 33;
const int buttonDown = 36;
const int buttonEnter = 34;

const int buzzerPin = 25; // Pin number connected to buzzer

// Struct to store reminders
struct Reminder {
  int hour;
  int minute;
  String message;
};

Reminder reminders[5]; // Store up to 5 reminders
int reminderCount = 0;

void setup() {
    Serial.begin(115200);
    lcd.begin(16, 2);

    pinMode(buttonMenu, INPUT_PULLUP);
    pinMode(buttonUp, INPUT_PULLUP);
    pinMode(buttonDown, INPUT_PULLUP);
    pinMode(buttonEnter, INPUT_PULLUP);
    pinMode(buzzerPin, OUTPUT);

    connectWiFi();
    timeClient.begin();

    lcd.clear();
    lcd.print("Fetching Time...");
    delay(2000);
}

void loop() {
    int currentHour, currentMinute, currentSecond, currentDay, currentMonth, currentYear;
    getNTPTime(currentHour, currentMinute, currentSecond, currentDay, currentMonth, currentYear);

    // Display Date and Time on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Date: ");
    if (currentDay < 10) lcd.print("0"); 
    lcd.print(currentDay);
    lcd.print("/");
    if (currentMonth < 10) lcd.print("0"); 
    lcd.print(currentMonth);
    lcd.print("/");
    lcd.print(currentYear % 100);  // Display last two digits of the year

    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    if (currentHour < 10) lcd.print("0");
    lcd.print(currentHour);
    lcd.print(":");
    if (currentMinute < 10) lcd.print("0");
    lcd.print(currentMinute);
    lcd.print(":");
    if (currentSecond < 10) lcd.print("0");
    lcd.print(currentSecond);

    delay(1000); // Refresh time every second

    for (int i = 0; i < reminderCount; i++) {
        if (currentHour == reminders[i].hour && currentMinute == reminders[i].minute) {
            triggerReminder(reminders[i].message);
        }
    }

    if (digitalRead(buttonMenu) == HIGH) {
        showMenu();
    }
}

void connectWiFi() {
    Serial.print("Connecting to WiFi...");
    WiFi.begin(ssid, password);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) { // Try for 10 seconds
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connected!");
    } else {
        Serial.println("\nWiFi Connection Failed!");
    }
}

void getNTPTime(int &hour, int &minute, int &second, int &day, int &month, int &year) {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected. Cannot get NTP time.");
        return;
    }

    timeClient.update();
    hour = timeClient.getHours();
    minute = timeClient.getMinutes();
    second = timeClient.getSeconds();

    time_t epochTime = timeClient.getEpochTime();
    struct tm *ptm = gmtime((time_t *)&epochTime);

    day = ptm->tm_mday;
    month = ptm->tm_mon + 1;
    year = ptm->tm_year + 1900;
}

void showMenu() {
    int menuIndex = 0;
    const char* menuItems[] = {"Set Reminder", "View Reminders", "Delete Reminder"};
    int menuSize = 3;
    
    lcd.clear();

    // Wait until the button is released to avoid instant selection
    while (digitalRead(buttonMenu) == HIGH);  
    delay(200);  // Small debounce delay

    while (true) {
        lcd.setCursor(0, 0);
        lcd.print("-> ");
        lcd.print(menuItems[menuIndex]);

        if (menuIndex < menuSize - 1) {
            lcd.setCursor(3, 1);
            lcd.print(menuItems[menuIndex + 1]);
        } else {
            lcd.setCursor(3, 1);
            lcd.print("               "); // Clear second line
        }

        // Navigate menu
        if (digitalRead(buttonUp) == HIGH) {
            while (digitalRead(buttonUp) == HIGH); // Wait for release
            menuIndex = (menuIndex + 1) % menuSize;
            delay(300);
        }
        if (digitalRead(buttonDown) == HIGH) {
            while (digitalRead(buttonDown) == HIGH); // Wait for release
            menuIndex = (menuIndex - 1 + menuSize) % menuSize;
            delay(300);
        }

        // Select menu option
        if (digitalRead(buttonEnter) == HIGH) {
            while (digitalRead(buttonEnter) == HIGH); // Wait for release
            delay(200);  // Small debounce
            lcd.clear();
            if (menuIndex == 0) setReminder();
            else if (menuIndex == 1) viewReminders();
            else if (menuIndex == 2) deleteReminder();
            break;
        }
    }
}

void setReminder() {
    int hour = 0, minute = 0;

    if (reminderCount >= 5) {
        lcd.clear();
        lcd.print("Max Reminders!");
        delay(2000);
        return;
    }

    bool settingHour = true; // Start by setting hours
    lcd.clear();

    while (true) {
        lcd.setCursor(0, 0);
        lcd.print("Set Reminder:");

        lcd.setCursor(0, 1);
        if (settingHour) {
            lcd.print("Hour: ");
            lcd.print(hour);
        } else {
            lcd.print("Minute: ");
            lcd.print(minute);
        }

        if (digitalRead(buttonUp) == HIGH) {
            if (settingHour) hour = (hour + 1) % 24;
            else minute = (minute + 1) % 60;
            delay(300);
        }

        if (digitalRead(buttonDown) == HIGH) {
            if (settingHour) hour = (hour - 1 + 24) % 24;
            else minute = (minute - 1 + 60) % 60;
            delay(300);
        }

        if (digitalRead(buttonEnter) == HIGH) {
            if (settingHour) settingHour = false;
            else break; // Exit loop after setting minute
            delay(300);
        }
    }

    lcd.clear();
    lcd.print("Enter Msg in Serial");
    Serial.println("Enter Reminder Message:");
    while (!Serial.available());
    String message = Serial.readString();
    message.trim();

    reminders[reminderCount].hour = hour;
    reminders[reminderCount].minute = minute;
    reminders[reminderCount].message = message;
    reminderCount++;

    lcd.clear();
    lcd.print("Reminder Set!");
    delay(2000);
}

void triggerReminder(String message) {
    lcd.clear();
    lcd.print("Reminder!");
    lcd.setCursor(0, 1);
    lcd.print(message);
    for (int i = 0; i < 5; i++) {
        digitalWrite(buzzerPin, HIGH);
        delay(500);
        digitalWrite(buzzerPin, LOW);
        delay(500);
    }
}

void viewReminders() {
    lcd.clear();
    if (reminderCount == 0) {
        lcd.print("No Reminders!");
        delay(2000);
        return;
    }

    Serial.println("Saved Reminders:");
    for (int i = 0; i < reminderCount; i++) {
        Serial.print(i + 1);
        Serial.print(". ");
        Serial.print(reminders[i].hour);
        Serial.print(":");
        Serial.print(reminders[i].minute);
        Serial.print(" - ");
        Serial.println(reminders[i].message);
    }

    lcd.print("Check Serial");
    delay(2000);
}

void deleteReminder() {
    if (reminderCount == 0) {
        lcd.clear();
        lcd.print("No Reminders!");
        delay(2000);
        return;
    }

    lcd.clear();
    lcd.print("Del Reminder:");
    lcd.setCursor(0, 1);
    lcd.print("Enter Index:");

    Serial.println("Enter the reminder index to delete (1 to " + String(reminderCount) + "):");
    while (!Serial.available());
    int index = Serial.parseInt() - 1;
    Serial.read(); // Clear buffer

    if (index < 0 || index >= reminderCount) {
        Serial.println("Invalid index!");
        lcd.clear();
        lcd.print("Invalid Index!");
        delay(2000);
        return;
    }

    for (int i = index; i < reminderCount - 1; i++) {
        reminders[i] = reminders[i + 1]; // Shift remaining reminders
    }
    reminderCount--;

    lcd.clear();
    lcd.print("Reminder Deleted");
    delay(2000);
}
