const int ENA = 9;  // Enable Pin 
const int IN1 = 6;  // Input 1 (Direction 1)
const int IN2 = 7;  // Input 2 (Direction 2)

const int joyPin = A0;

int joyVal = 0; // Value read from joystick (0-1023)
int motorSpeed = 0; // PWM output (0-255)

void setup() {
  // Set all the motor control pins to outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // Turn off motor initially
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
  Serial.begin(9600); 
}

void loop() {
  joyVal = analogRead(joyPin);

  // If joystick is moved Forward (Value > 520)
  if (joyVal > 520) {
    motorSpeed = map(joyVal, 525, 1023, 0, 255);
    
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    
    analogWrite(ENA, motorSpeed);
  }

  // If joystick is moved Backward (Value < 505)
  else if (joyVal < 505) {
    motorSpeed = map(joyVal, 500, 0, 0, 255);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    analogWrite(ENA, motorSpeed);
  }

  // If joystick is in the middle (between 505 and 520)
  else {
    motorSpeed = 0;
    
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 0);
  }

  Serial.print("Joystick: ");
  Serial.println(joyVal);
  
  delay(10); // Small stability delay
}