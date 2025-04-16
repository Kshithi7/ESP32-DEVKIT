const int sensorPin = 5; // GPIO5 (or any available pin)
int value = 0;

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT_PULLUP); // Enable internal pull-up
}

void loop() {
  value = digitalRead(sensorPin);
  
  if (value == HIGH) { // LOW means object detected (NPN logic)
    Serial.println("🚨 Obstacle detected!");
  } else {
    Serial.println("✅ No obstacle.");
  }
  
  delay(500);
}
