#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// define all the pins
const int sensorPin = A0; 
const int ledGreen = 3;  
const int ledRed = 4;    
const int buzzerPin = 7; 

int sensorData = 0;       

String voice;          

void setup() {

  Serial.begin(9600);
  

  pinMode(sensorPin, INPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT); 
  

  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, LOW);
  digitalWrite(buzzerPin, LOW);

  lcd.clear();
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("AQI Alert System");
  delay(1000);
}

void loop() {

  while (Serial.available()) {
    delay(3);
    char c = Serial.read();
    voice += c;
  }

  if (voice.length() > 0) {
    Serial.println(voice);


    if (voice == "turn on light") {
      digitalWrite(6, HIGH);
    } 
    else if (voice == "turn off light") {
      digitalWrite(6, LOW);
    } 
    else if (voice == "turn on fan") {
      digitalWrite(5, HIGH);
    } 
    else if (voice == "turn off fan") {
      digitalWrite(5, LOW);
    } 
    else if (voice == "turn on all") {
      digitalWrite(6, HIGH);
      digitalWrite(5, HIGH);
    } 
    else if (voice == "turn off all") {
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
    }

    voice = "";  
  }


  sensorData = analogRead(sensorPin);
  

  Serial.print("Raw Sensor Value: ");
  Serial.println(sensorData);


  int AQI = map(sensorData, 0, 1023, 0, 500);

 
  Serial.print("Mapped AQI: ");
  Serial.println(AQI);


  lcd.setCursor(0, 0);
  lcd.print("Air Quality: ");
  lcd.print(AQI);

  
  if (AQI <= 50) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Air Quality: ");
    lcd.print(AQI+25);
    lcd.setCursor(0, 1);
    lcd.print("AQI Good");
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(buzzerPin, LOW); 
  } 
  else if (AQI > 300) { 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Air Quality: ");
    lcd.print(AQI);
    lcd.setCursor(0, 1);
    lcd.print("AQI Hazardous");
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    digitalWrite(buzzerPin, HIGH); 
  }

  delay(700); 
}
