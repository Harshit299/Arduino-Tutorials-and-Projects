#include <Wire.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Checking MPU6050 Identity...");

  Wire.begin();

  // 1. Wake up the MPU6050 (it might be in sleep mode)
  Wire.beginTransmission(0x68);
  Wire.write(0x6B); // Power Management 1 register
  Wire.write(0);    // Wake up
  Wire.endTransmission();

  // 2. Ask for the "WHO_AM_I" register value
  Wire.beginTransmission(0x68);
  Wire.write(0x75); // 0x75 is the register address
  byte error = Wire.endTransmission();

  if (error == 0) {
    Wire.requestFrom(0x68, 1);
    if (Wire.available()) {
      byte id = Wire.read(); // get value of register
      Serial.print("Return ID: 0x");
      Serial.println(id, HEX);

      if (id == 0x68) {
        Serial.println("Result: The chip is GENUINE (Official).");
      } else {
        Serial.print("Result: ID MISMATCH. Expected 0x68, but got 0x");
        Serial.println(id, HEX);
        Serial.println("Solution: The Adafruit library blocks this ID");
      }
    }
  } else {
    Serial.print("I2C Connection Error: ");
    Serial.println(error);
  }
}

void loop() {
}