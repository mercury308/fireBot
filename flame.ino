// heat sensor {ky-026}
#include <LiquidCrystal.h>
// LCD display {standard}
//test.ino

int led = 13; // define the LED pin
int digitalPin = 2; // KY-026 digital interface
int analogPin = A0; // KY-026 analog interface
int digitalVal; // digital readings
int analogVal; //analog readings
void setup()
{
  pinMode(led, OUTPUT);
  pinMode(digitalPin, INPUT);
  //pinMode(analogPin, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  // Read the digital interface
  digitalVal = digitalRead(digitalPin); 
  if(digitalVal == HIGH) // if flame is detected
  {
    digitalWrite(led, HIGH); // turn ON Arduino's LED
  }
  elset
  {
    digitalWrite(led, LOW); // turn OFF Arduino's LED
  }
  // Read the analog interface
  analogVal = analogRead(analogPin); 
  Serial.println(analogVal); // print analog value to serial
  delay(100);
}
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print(analogVal);
}
void loop() {
  lcd.display();
  delay(500);
}
