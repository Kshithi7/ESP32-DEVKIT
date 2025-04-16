#define LDR_PIN 34  // Analog input pin

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("🌤️ LDR Sensor Ready");
}

void loop() {
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  if (ldrValue < 1000) {
    Serial.println("🌙 It's Dark!");
  } else {
    Serial.println("☀️ It's Bright!");
  }

  delay(1000);
}
