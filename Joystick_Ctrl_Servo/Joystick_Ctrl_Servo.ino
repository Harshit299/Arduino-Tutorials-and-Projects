#include <Servo.h>

Servo servoX;
Servo servoY;

int joyX = A0;
int joyY = A2;

void setup() {
  servoX.attach(9);   // Servo for X axis (0 – 90deg)
  servoY.attach(10);  // Servo for Y axis (0 – 180deg)

  Serial.begin(9600);
}

void loop() {
  int xVal = analogRead(joyX);   // 0–1023
  int yVal = analogRead(joyY);   // 0–1023

  // Map joystick values to servo angles
  int angleX = map(xVal, 0, 1023, 0, 90);
  int angleY = map(yVal, 0, 1023, 0, 180);

  servoX.write(angleX);
  servoY.write(angleY);

  // Serial.print("X Angle: ");
  // Serial.print(angleX);
  // Serial.print(" | Y Angle: ");
  // Serial.println(angleY);

  Serial.print("X: ");
  Serial.print(xVal);
  Serial.print("  Y: ");
  Serial.println(yVal);

  delay(15);
}