#include <SparkFun_APDS9960.h>
#include <Wire.h>

SparkFun_APDS9960 apds = SparkFun_APDS9960();

void setup(){
  Serial.begin(9600);
  Wire.begin();

  if(apds.init()){
    Serial.print("APDS9960 initialized.");
  }else{
    Serial.print("APDS9960 Initialization failed...");
  }

  if(apds.enableGestureSensor(true)){
    Serial.print("Gesture sensor activated");
  }else{
    Serial.print("Failed to activate gesture sensor!!");
  }
}

void loop(){
  if(apds.isGestureAvailable()){
    int gesture = apds.readGesture();
    switch(gesture){
      case DIR_UP:
      Serial.println("Gesture detected : UP");
      break;
      delay(5000);
      case DIR_DOWN:
      Serial.println("Gesture detected: DOWN");
      break;
      delay(5000);
      case DIR_LEFT:
      Serial.println("Gesture detected : LEFT");
      break;
      delay(5000);
      case DIR_RIGHT:
      Serial.println("Gesture detected: RIGHT");
      break;
      delay(5000);
      default:
      Serial.println("No gesture detected!!");
      break;
      delay(5000);
    }
  }
}