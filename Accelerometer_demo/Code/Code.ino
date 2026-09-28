#include <Wire.h>

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050

int16_t rawAcX, rawAcY, rawAcZ;
float gForceX, gForceY, gForceZ;

void setup() {
  // Use a high baud rate for smooth graphing in the Serial Plotter
  Serial.begin(115200);
  Wire.begin();

  // Wake up the MPU-6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // Write 0 to wake the sensor up
  Wire.endTransmission(true);

  // Note: By default, the accelerometer is configured to a +/- 2g range.
  // We will leave it at this default setting for maximum sensitivity.
}

void loop() {
  // Point to the starting register for accelerometer data
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);  // ACCEL_XOUT_H register
  Wire.endTransmission(false);
  
  // Request 6 bytes of data (2 bytes for each axis: X, Y, Z)
  Wire.requestFrom(MPU_ADDR, 6, true);

  // Read the raw accelerometer values
  rawAcX = Wire.read() << 8 | Wire.read(); 
  rawAcY = Wire.read() << 8 | Wire.read(); 
  rawAcZ = Wire.read() << 8 | Wire.read(); 

  // Convert raw data to G-force
  // For a +/- 2g range, the scale factor is 16384 LSB/g (Least Significant Bits per g)
  gForceX = (float)rawAcX / 16384.0;
  gForceY = (float)rawAcY / 16384.0;
  gForceZ = (float)rawAcZ / 16384.0;

  // Print the data in a format the Arduino Serial Plotter can read
  Serial.print("X_Axis:");
  Serial.print(gForceX);
  Serial.print(" | ");
  
  Serial.print("Y_Axis:");
  Serial.print(gForceY);
  Serial.print(" | ");
  
  Serial.print("Z_Axis:");
  Serial.println(gForceZ);

  // 50ms delay results in a 20Hz update rate, which is ideal for plotting
  delay(50); 
}