#include <Servo.h>
Servo motor;
void setup() {
motor.attach(9); //9
}
void loop () {
for(int pos = 0; pos < 10; pos += 1) {
motor.write(pos);
delay(3000);
}
}
