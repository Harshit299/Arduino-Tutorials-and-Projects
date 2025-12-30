/* I2C Address scanning code */

#include <Wire.h>

int devices = 0;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);   // wait for serial
  Serial.println("I2C scan started");
}

void loop() {
  byte response;

  // Scanning all possible I2C addresses (0-127)
  for (byte address = 1; address <= 126; address++) {
    Wire.beginTransmission(address);
    response = Wire.endTransmission(); // sends the request and waits for a response.
    
    if (response == 0) {
      Serial.print("Found device at address: ");
      Serial.print(address);
      Serial.print(" (0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(")");
      devices++;
    }
  }

  // If nothing responded
  if (devices == 0) { 
    Serial.println("No I2C devices found");
  }

  Serial.println("Scan done\n");
  delay(3000);
}