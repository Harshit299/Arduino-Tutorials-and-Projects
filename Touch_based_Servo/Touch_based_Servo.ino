#include <Servo.h>

Servo myServo;

const int touchPin = 7;
const int buttonPin = 6;

int pos = 0;       // current angle
int stepVal = 20;    // movement speed
bool direction = false;   // false = increasing angle, true = decreasing angle

void setup() {
  myServo.attach(9);
  pinMode(touchPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  myServo.write(pos);
}

void loop() {

  // Check if button is pressed
  if (digitalRead(buttonPin) == LOW) {
    direction = !direction;    
    delay(200);  // debounce 
  }

  // If touch sensor is active, keep moving
  if (digitalRead(touchPin) == HIGH) {

    if (direction == false) {
      pos += stepVal;     // move forward
    } 
    else {
      pos -= stepVal;     // move backward
    }

    // Keep within 0-180 range
    if (pos > 180) pos = 180;
    if (pos < 0)   pos = 0;

    myServo.write(pos);
    delay(20);
  }
}