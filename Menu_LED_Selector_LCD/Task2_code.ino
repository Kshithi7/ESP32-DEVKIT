#include <LiquidCrystal.h> 

LiquidCrystal lcd(16,17,19,21,22,23); //pin number of the port connected to lcd

const int LED[8] = {0,2,4,12,13,14,15,27};//pin numbers in the port connected to LED

#define MENU 32 // pin numbers connected to buttons
#define UP 33
#define DOWN 36
#define ENTER 34

const char* patterns[6] = {"Left shift","Right shift","Blink","Fast blink","Right arrow","Left arrow"};
int Menu_index = 0;
int selected = -1;

void setup(){
  Serial.begin(9600);

  pinMode(MENU ,INPUT);
  pinMode(UP ,INPUT);
  pinMode(DOWN ,INPUT);
  pinMode(ENTER ,INPUT);

 for(int i=0;i<8;i++){
  pinMode(LED[i],OUTPUT);
  }

  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select pattern:");
  delay(1000);
  displayMenu();
}

 void loop(){
  if(digitalRead(MENU) == HIGH){
    displayMenu();
  }

   else if (digitalRead(UP) == HIGH) {
    if (Menu_index > 0) {
      Menu_index--;
      displayMenu();
    }
     delay(300);
  }

  else if (digitalRead(DOWN) == HIGH) {
    if (Menu_index < 5) {  // Prevent overflow
      Menu_index++;
      displayMenu();
    }
    delay(300);
  }
  else if (digitalRead(ENTER) == HIGH){
    selected = Menu_index;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("selected pattern : ");
    lcd.setCursor(0,1);
    lcd.print(patterns[selected]);
    delay(2000);
     
    run(selected);
  }
 }

  void run(int patternindex){
    lcd.clear();
    Serial.print("Running pattern:");
    Serial.println(patternindex);

  switch (patternindex) {
        case 0: Left_shift();
        break;
        case 1: Right_shift();
        break;
        case 2: blinkAll(500);
        break;
        case 3: blinkAll(200); 
        break;
        case 4: Left_arrow();
        break;
        case 5: Right_arrow();
         break;
        default: setAllLEDs(LOW);
    }
    delay(1000); 
}

 void displayMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-> ");
  lcd.print(patterns[Menu_index]);
  if (Menu_index < 5) {
    lcd.setCursor(3, 1);
    lcd.print(patterns[Menu_index + 1]);
  }
}
void setAllLEDs(bool state) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(LED[i], state);
    }
}

void blinkAll(int delayTime) {
  for(int j=0;j<5;j++){
    setAllLEDs(HIGH);
    delay(delayTime);
    setAllLEDs(LOW);
    delay(delayTime);}
}

void Left_shift(){
  for(int i=0 ; i<8 ; i++){
  digitalWrite(LED[i], HIGH);
  delay(100);
  digitalWrite(LED[i],LOW);
}
}
void Right_shift(){
  for(int i=7 ;i>=0; i--){
    digitalWrite(LED[i],HIGH);
    delay(100);
    digitalWrite(LED[i], LOW);
  }
}

void Left_arrow(){
  for(int i=0 ;i<40; i++){
    digitalWrite(LED[i],HIGH);
    digitalWrite(LED[7-i],HIGH);
    delay(100);
    digitalWrite(LED[i],LOW);
    digitalWrite(LED[7-i],LOW);
  }
}

void Right_arrow(){
  for(int i=3;i>=0;i--){
    digitalWrite(LED[i],HIGH);
    digitalWrite(LED[7-i],HIGH);
    delay(100);
    digitalWrite(LED[i],LOW);
    digitalWrite(LED[7-i],LOW);
  }
}
