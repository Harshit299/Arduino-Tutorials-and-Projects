/* Attenuation = 0db */

void setup() {
  Serial.begin(9600);

  analogSetAttenuation(ADC_0db);
}

void loop() {
  int adc = analogRead(34);
  float voltage = adc * (1.1 / 4095.0);

  Serial.print("ADC: ");
  Serial.println(adc);
  Serial.print("  Voltage: ");
  Serial.println(voltage, 2);

  delay(100);
}



/* Attenuation = 11db */


// void setup() {
//   Serial.begin(9600);

//   analogSetAttenuation(ADC_11db);
// }

// void loop() {
//   int adc = analogRead(34);
//   float voltage = adc * (3.3 / 4095.0);

//   Serial.print("ADC: ");
//   Serial.println(adc);
//   // Serial.print("  Voltage: ");
//   // Serial.println(voltage, 2);

//   delay(100);
// }





// void setup() {
//   Serial.begin(9600);
//   analogReadResolution(10);
// }

// void loop() {
//   int adc = analogRead(34);
//   Serial.println(adc);
//   delay(200);
// }