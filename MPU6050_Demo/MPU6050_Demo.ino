#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire); // tells the mpu to use i2c 

void setup() {
  Serial.begin(9600);
  Wire.begin(); // setup i2c communication

  byte status = mpu.begin(); // tries to communicate with MPU6050
  Serial.print("MPU6050 status: ");
  Serial.println(status);

  while (status != 0) {
    Serial.println("MPU6050 not connected!");
    delay(1000);
  }

  Serial.println("Calibrating offsets"); // keep the sensor still
  delay(1000);
  mpu.calcOffsets();  
  Serial.println("Calibration done");
}

void loop() {
  mpu.update();

  // acceleration values in g-units
  float acc_x = mpu.getAccX();
  float acc_y = mpu.getAccY();
  float acc_z = mpu.getAccZ();

  Serial.print("Ax: "); Serial.print(acc_x);
  Serial.print("      Ay: "); Serial.print(acc_y);
  Serial.print("      Az: "); Serial.println(acc_z);

  // float ax = mpu.getAngleX();
  // float ay = mpu.getAngleY();
  // float az = mpu.getAngleZ();

  // Serial.print("Angle_x: "); Serial.print(ax);
  // Serial.print("      Angle_y: "); Serial.print(ay);
  // Serial.print("      Angle_z: "); Serial.println(az);

  delay(150);
}