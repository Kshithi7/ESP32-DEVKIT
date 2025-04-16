#define LM35 33 // Change this to the ADC pin you connected LM35

void setup() {
  Serial.begin(115200);
  pinMode(LM35, INPUT);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
}

void loop() {
  int adcValue = analogRead(LM35);
  float temp = (adcValue * 3.3 / 4095.0) * 100; // Convert ADC to temperature

  Serial.print("Raw ADC Value: ");
  Serial.println(adcValue);  
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");

  delay(2000);
}
