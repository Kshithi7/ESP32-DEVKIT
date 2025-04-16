#include <WiFi.h>
#include <Wire.h>
#include <time.h>

#define DS1307_I2C_ADDRESS 0X68

const char* SSID = "Martin router king";
const char* Password = "amulya16";
const char* NTP = "pool.ntp.org";
const long gmtoffset_sec = 19800;
const int daylight_sec = 0;

void setup(){
 Serial.begin(9600); 
 Wire.begin();
 Wificonnect();
 synctimeNTPserver();
}

void loop(){
   displayRTC();
   delay(2000);
}

void Wificonnect(){
  Serial.print("Connecting to WiFi");
  WiFi.begin(SSID, Password);
  unsigned long startTime = millis();
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
    if(millis() - startTime > 15000){
      Serial.println("\nFailed to connect to WiFi");
      return;
    }
  }
  Serial.println("\nConnected to WiFi!"); 
}

void synctimeNTPserver(){
  configTime(gmtoffset_sec, daylight_sec, NTP );
  Serial.println("Fetching time from NTP...");
  struct tm timeinfo;

  if(!getLocalTime(&timeinfo)){
    Serial.print("Error in obtaining time ");
    return;
  } 
  Serial.print("RTC time obtained !!");

  setDS1307time(timeinfo.tm_sec, timeinfo.tm_min, timeinfo.tm_hour, timeinfo.tm_wday+1, timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year - 100);
}

byte decToBcd(byte val) {
  return ((val / 10 * 16) + (val % 10));
}

byte bcdToDec(byte val) {
  return ((val / 16) * 10 + (val % 16));
}

void setDS1307time(byte second, byte minute, byte hour, byte dayofweek, byte dayofmonth, byte month, byte year){
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0); // Start at register 0
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(dayofweek));
  Wire.write(decToBcd(dayofmonth));
  Wire.write(decToBcd(month));
  Wire.write(decToBcd(year));
  Wire.endTransmission();
  Serial.println("RTC updated from NTP!");
}

void readDS1307time(byte *second, byte *minute, byte *hour, byte *dayofweek, byte *dayofmonth, byte *month, byte *year){
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
  if(Wire.available() >= 7){
    *second   = bcdToDec(Wire.read() & 0x7F);
    *minute   = bcdToDec(Wire.read());
    *hour     = bcdToDec(Wire.read() & 0x3F);
    *dayofweek = bcdToDec(Wire.read());
    *dayofmonth = bcdToDec(Wire.read());
    *month    = bcdToDec(Wire.read());
    *year     = bcdToDec(Wire.read());
  }
}

void displayRTC(){
  byte second, minute, hour, dayofweek, dayofmonth, month, year;
  readDS1307time(&second, &minute, &hour, &dayofweek, &dayofmonth, &month, &year);

  Serial.print("RTC Time: ");
  Serial.printf("%02d:%02d:%02d\n", hour, minute, second);
  Serial.printf("RTC Date: %02d/%02d/%04d\n", dayofmonth, month, year + 2000);
}
