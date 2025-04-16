#include <WiFi.h>
#include <HTTPClient.h>

#define WIFI_SSID "Martin"
#define WIFI_PASS "amulya16"
#define AIO_USERNAME "Amulya16"
#define AIO_KEY "aio_IjMI02s9hP5t4FCjNWZzs6fAKnZI"
#define RELAY_PIN 26  // Change this to the GPIO pin connected to relay

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\n✅ WiFi Connected!");
}

void loop() {
  HTTPClient http;
  String url = "https://io.adafruit.com/api/v2/" + String(AIO_USERNAME) + "/feeds/relay/data/last";
  http.begin(url);
  http.addHeader("X-AIO-Key", AIO_KEY);  // Add the Adafruit IO key header
  
  int httpCode = http.GET();
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println("Received: " + payload);

    if (payload.indexOf("ON") >= 0) {
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("Relay Turned ON");
    } else if (payload.indexOf("OFF") >= 0) {
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("Relay Turned OFF");
    }
  } else {
    Serial.println("❌ HTTP Request Failed!");
  }

  http.end();
  delay(10000);  // Adjust the delay as needed
}
