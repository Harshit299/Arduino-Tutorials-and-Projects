#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

// LED pins
const byte ledPins[8] = {9,3,2,A0,A1,A2,A3};

void setup() {
  Serial.begin(9600);
  Wire.begin();

  byte status = mpu.begin();

  Serial.print("MPU6050 status: ");
  Serial.println(status);

  while (status != 0);

  Serial.println("Keep the MPU6050 horizontal...");
  delay(1000);

  mpu.calcOffsets();

  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }

  Serial.println("Calibration Complete");
}

void loop() {

  mpu.update();

  // Choose the axis you're tilting about
  float angle = abs(mpu.getAngleX());

  // Limit to 90 degrees
  if (angle > 90) angle = 90;

  // Convert angle to number of LEDs
  int ledCount = round(angle / 11.25);   // 90 deg / 8 = 11.25 deg

  if (ledCount > 8) ledCount = 8;

  // Update LEDs
  for (int i = 0; i < 8; i++) {
    if (i < ledCount)
      digitalWrite(ledPins[i], HIGH);
    else
      digitalWrite(ledPins[i], LOW);
  }

  Serial.print("Angle: ");
  Serial.print(angle);
  Serial.print("   LEDs: ");
  Serial.println(ledCount);

  delay(20);
}
