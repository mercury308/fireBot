#include <Servo.h>
#include <LiquidCrystal.h>

// Define pin numbers
const int flamePin = 2;          // Connect KY-026 flame sensor to digital pin 2
const int leftMotorPin = 3;      // Connect left motor to digital pin 3
const int rightMotorPin = 4;     // Connect right motor to digital pin 4
const int trigPin = 9; // Trigger pin of ultrasonic sensor
const int echoPin = 10; // Echo pin of ultrasonic sensor
const int rs = 12, en = 11, d4 = 5, d5 = 6, d6 = 7, d7 = 8; // Connect LCD display to digital pins 5-12

// Define wheel parameters
const float wheelDiameter = 6.5; // Diameter of the wheels in centimeters
const float wheelCircumference = wheelDiameter * PI; // Circumference of the wheels in centimeters
const int ticksPerRevolution = 20; // Number of encoder ticks per wheel revolution

Servo leftMotor;                 // Create left motor object
Servo rightMotor;                // Create right motor object
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // Create LCD object

// Initialize odometry variables
float x = 0;                     // X position of the robot in centimeters
float y = 0;                     // Y position of the robot in centimeters
float theta = 0;                 // Orientation of the robot in radians
float leftDistance = 0;          // Distance traveled by left wheel in centimeters
float rightDistance = 0;         // Distance traveled by right wheel in centimeters

void setup() {
  pinMode(flamePin, INPUT);      // Set flamePin as input
  leftMotor.attach(leftMotorPin);// Attach left motor to leftMotorPin
  rightMotor.attach(rightMotorPin); // Attach right motor to rightMotorPin
  Serial.begin(9600);            // Start serial communication
  lcd.begin(16, 2);              // Initialize LCD display
  lcd.print("FlameBot ready");   // Print initial message on the LCD display
}

void loop() {
  // Read flame sensor value
  int flameValue = digitalRead(flamePin);

  // If flame is detected, move forward, otherwise stop
  if (flameValue == HIGH) {
    Serial.println("Flame detected!");
    lcd.setCursor(0, 1);         // Set cursor to second row of LCD display
    lcd.print("Flame detected!"); // Print flame detection status on the LCD display
    moveForward();
  }
  else {
    lcd.setCursor(0, 1);         // Set cursor to second row of LCD display
    lcd.print("No flame detected"); // Print flame detection status on the LCD display
    stopMotors();
  }

  // Update odometry
  updateOdometry();

  // Print odometry information to the Serial Monitor
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  Serial.print(" Theta: ");
  Serial.println(theta);

  delay(100); // Delay for 100 milliseconds
}

// Function to move the robot forward
void moveForward() {
  leftMotor.write(180);          // Set left motor to maximum speed forward
  rightMotor.write(180);          // Set right motor to maximum speed forward
}
// Function to move the robot backward
void moveBackward() {
  leftMotor.write(0);          // Set left motor to maximum speed backward
  rightMotor.write(0);         // Set right motor to maximum speed backward
}

// Function to rotate the robot left
void rotateLeft() {
  leftMotor.write(0);          // Set left motor to maximum speed backward
  rightMotor.write(90);       // Set right motor to half speed forward
}
// Function to rotate the robot right
void rotateRight() {
  leftMotor.write(90); //Set left motor to maximum speed forward
  rightMotor.write(0); //Set right motor to half speed backward
}

// Function to stop the robot
void stopMotors() {
  leftMotor.write(0);          // Set left motor to stop
  rightMotor.write(0);         // Set right motor to stop
}
void updateOdometry() {
  // Calculate distance traveled by each wheel since the last update
  float leftTicks = leftMotor.read() / 180.0 * ticksPerRevolution;
  float rightTicks = rightMotor.read() / 180.0 * ticksPerRevolution;
  float leftDistanceDelta = leftTicks / ticksPerRevolution * wheelCircumference;
  float rightDistanceDelta = rightTicks / ticksPerRevolution * wheelCircumference;

  // Reset motor positions
  leftMotor.write(0);
  rightMotor.write(0);

  // Calculate distance traveled by the robot since the last update
  float distanceDelta = (leftDistanceDelta + rightDistanceDelta) / 2.0;
  float thetaDelta = (rightDistanceDelta - leftDistanceDelta) / 2.0;

  // Update odometry variables
  leftDistance += leftDistanceDelta;
  rightDistance += rightDistanceDelta;
  x += distanceDelta * cos(theta);
  y += distanceDelta * sin(theta);
  theta += thetaDelta;

  // Check for obstacles and adjust position accordingly
  if (distanceDelta > 0) {
    float frontDistance = readUltrasonicSensor();
    if (frontDistance < MIN_FRONT_DISTANCE) {
      // Obstacle detected - move robot back and rotate left
      moveBackward();
      delay(500);
      rotateLeft();
      delay(1000);
      stopMotors();
    }
  }
}

// Function to read the distance from the ultrasonic sensor
float readUltrasonicSensor() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse in microseconds
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance based on the duration of the echo pulse
  float distance = duration * 0.034 / 2.0; // Distance in centimeters
  return distance;
}
