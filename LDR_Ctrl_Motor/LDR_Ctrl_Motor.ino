const int ldrPin = A0; 
const int motorPin = 9;   // PWM pin

int ldrValue = 0;
int motorSpeed = 0;

void setup() {
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  ldrValue = analogRead(ldrPin);   // Read LDR value (0–1023)

  // Map LDR value to PWM range (0–255)
  motorSpeed = map(ldrValue, 420, 840, 0, 255);
  motorSpeed = constrain(motorSpeed, 0, 255);

  // Set motor speed
  digitalWrite(7, HIGH); // direction pin
  analogWrite(motorPin, motorSpeed);

  // Debug values
  Serial.print("LDR: ");
  Serial.print(ldrValue);
  Serial.print("  Motor Speed: ");
  Serial.println(motorSpeed);

  delay(100);
}