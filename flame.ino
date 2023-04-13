#include <Servo.h>

// Define pin numbers
const int flamePin = 2;          // Connect KY-026 flame sensor to digital pin 2
const int leftMotorPin = 3;      // Connect left motor to digital pin 3
const int rightMotorPin = 4;     // Connect right motor to digital pin 4

Servo leftMotor;                 // Create left motor object
Servo rightMotor;                // Create right motor object

void setup() {
  pinMode(flamePin, INPUT);      // Set flamePin as input
  leftMotor.attach(leftMotorPin);// Attach left motor to leftMotorPin
  rightMotor.attach(rightMotorPin); // Attach right motor to rightMotorPin
  Serial.begin(9600);            // Start serial communication
}

void loop() {
  // Read flame sensor value
  int flameValue = digitalRead(flamePin);

  // If flame is detected, move forward, otherwise stop
  if (flameValue == HIGH) {
    Serial.println("Flame detected!");
    moveForward();
  }
  else {
    stopMotors();
  }

  delay(100); // Delay for 100 milliseconds
}

// Function to move the robot forward
void moveForward() {
  leftMotor.write(180);          // Set left motor to maximum speed forward
  rightMotor.write(180);          // Set right motor to maximum speed forward
}

// Function to stop the robot
void stopMotors() {
  leftMotor.write(0);          // Set left motor to stop
  rightMotor.write(0);         // Set right motor to stop
}
