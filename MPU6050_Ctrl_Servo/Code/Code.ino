#include <Wire.h>
#include <Servo.h>
#include <MPU6050_light.h>

Servo myServo;
MPU6050 mpu(Wire);

unsigned long timer = 0;

void setup() {
  Serial.begin(9600);
  delay(100);
  Wire.begin();
  
  myServo.attach(6);
  
  // 1. Initialize MPU
  byte status = mpu.begin();
  Serial.print("MPU6050 status: ");
  Serial.println(status);
  
  // 2. Calibration
  Serial.println("Calibrating... Keep sensor still!");
  delay(1000);
  mpu.calcOffsets(); // Auto-calculates offsets for Gyro and Accel
  Serial.println("Calibration done!");
}

void loop() {
  // 3. Update the MPU data (Must be called frequently)
  mpu.update();

  // 4. Get the angle
  // getAngleX returns values roughly b/w -90 and +90 when tilted
  float angleX = mpu.getAngleX();

  // 5. Map the angle to Servo values (0 to 180)
  //We assume -90 deg tilt = 0 servo, 0 deg tilt = 90 servo, +90 deg tilt = 180 servo
  int servoVal = map((int)angleX, -90, 90, 0, 180);

  servoVal = constrain(servoVal, 0, 180);

  myServo.write(servoVal);

  if((millis() - timer) > 100) { 
    Serial.print("Angle X: ");
    Serial.print(angleX);
    Serial.print("\tServo Value: ");
    Serial.println(servoVal);
    timer = millis();
  }
}