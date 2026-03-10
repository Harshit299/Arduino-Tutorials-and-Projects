#include <Wire.h>

void setup(){
  Wire.begin(); // initializes arduino as master device
  Serial.begin(9600);

  Serial.println("Scanning...");
}


void loop(){
  byte error, address;
  int devices = 0;

  for(address = 1; address < 127; address++){ // 0x01 --> 0x7E (1 --> 126)
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if(error == 0){
      Serial.print("I2C device found at address: 0x");
      if(address < 16)
        Serial.print("0");
      
      Serial.println(address, HEX);
      devices++;
    }
  }

  if(devices == 0)
    Serial.println("No I2C devices found");
  else
    Serial.println("Scan complete");

  delay(2000); // scan every 2 seconds
}