#include <Servo.h>
char buffer[11];
Servo motor1;
Servo motor2; 
void setup()
{
motor1.attach(5); 
motor2.attach(6); 
Serial.begin(9600);
while(Serial.available())
Serial.read();
servo1.write(90); 
servo2.write(90); 
Serial.println("INITIALIZING...");
}
void loop()
{
if (Serial.available() > 0) {
int index=0;
delay(100); 
int numChar = Serial.available(); 
if (numChar>10) {
numChar=10;
}
while (numChar--) {
buffer[index++] = Serial.read();
}
buffer[index]='\0';
splitString(buffer);
}
}
void splitString(char* data) {
Serial.print("Data entered: ");
Serial.println(data);
char* parameter;
parameter = strtok (data, " ,");
while (parameter != NULL) { 
setServo(parameter); 
parameter = strtok (NULL, " ,");
}
while(Serial.available())
Serial.read();
}
void setServo(char* data) {
if ((data[0] == 'L') || (data[0] == 'l')) {
int firstVal = strtol(data+1, NULL, 10); 
firstVal = constrain(firstVal,0,180); 
motor1.write(firstVal);
Serial.print("Servo1 is set to: ");
Serial.println(firstVal);
}
if ((data[0] == 'R') || (data[0] == 'r')) {
int secondVal = strtol(data+1, NULL, 10); 
secondVal = constrain(secondVal,0,255); 
motor2.write(secondVal);
Serial.print("Servo2 is set to: ");
Serial.println(secondVal);
}
}
